use std::env;
use tokio::net::TcpListener;

#[tokio::main]
async fn main() {
    let addr = env::args().nth(1).unwrap_or_else(|| "127.0.0.1:58993".to_string());

    let listener = TcpListener::bind(&addr)
        .await
        .expect("Cannot bind TcpListener");

    while let Ok((stream, addr)) = listener.accept().await {
        tokio::spawn(async move {
            let ws_stream = tokio_tungstenite::accept_async(stream)
                .await
                .expect("Error during the websocket handshake occurred");
            println!("WebSocket connection established: {}", addr);
        });
    }
}