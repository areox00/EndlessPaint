use std::{env, sync::Arc, net::SocketAddr};

use futures_util::{StreamExt, stream::SplitSink, SinkExt};
use tokio::net::{TcpListener, TcpStream};
use tokio::sync::Mutex;
use tokio_tungstenite::WebSocketStream;
use tungstenite::{Message, Error};

type Sink = SplitSink<WebSocketStream<TcpStream>, Message>;

pub struct Sessions {
    sinks: Vec<Sink>,
    addresses: Vec<SocketAddr>,
}

impl Sessions {
    fn new() -> Self {
        Self {
            sinks: Vec::new(),
            addresses: Vec::new(),
        }
    }

    fn new_session(&mut self, sink: Sink, address: SocketAddr) {
        self.sinks.push(sink);
        self.addresses.push(address);
    }

    fn remove_session(&mut self, address: SocketAddr) {
        if let Some(index) = self.addresses.iter().position(|&addr| { addr == address }) {
            self.addresses.swap_remove(index);
            self.sinks.swap_remove(index);
        }
    }
}

async fn broadcast_message(
    sender_address: &SocketAddr,
    sessions: &mut Sessions,
    message: Result<Message, Error>
) {
    match message {
        Ok(Message::Binary(data)) => {
            for (index, address) in sessions.addresses.iter().enumerate() {
                if address != sender_address {
                    sessions.sinks.get_mut(index).unwrap().send(Message::Binary(data.to_vec())).await.unwrap();
                }
            }
        }
        _ => (),
    }
}

async fn handle_connection(
    sessions: Arc<Mutex<Sessions>>,
    stream: TcpStream,
    address: SocketAddr
) {
    let ws_stream = tokio_tungstenite::accept_async(stream)
        .await
        .expect("Error during handshake occured");

    println!("connected: {}", address);

    let (write, mut read) = ws_stream.split();

    sessions.lock().await.new_session(write, address);

    while let Some(message) = read.next().await {
        broadcast_message(&address, &mut *sessions.lock().await, message).await;
    }

    sessions.lock().await.remove_session(address);
    println!("disconnected: {}", address);
}

#[tokio::main]
async fn main() {
    let address = env::args()
        .nth(1)
        .unwrap_or_else(|| "127.0.0.1:58993".to_string());

    let try_socket = TcpListener::bind(&address).await;
    let listener = try_socket.expect("Failed to bind");
    println!("listening on: {}", address);

    let sessions = Arc::new(Mutex::new(Sessions::new()));

    while let Ok((stream, address)) = listener.accept().await {
        let sessions = sessions.clone();
        tokio::spawn(async move {
            handle_connection(sessions, stream, address).await;
        });
    }
}