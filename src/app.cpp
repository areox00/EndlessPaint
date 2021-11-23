#include "app.hpp"

App::App()
{
	sm.setState(new DrawingState(this));
	window.create(sf::VideoMode(1280, 720), "asunapixel");
	window.setFramerateLimit(0);
}

App::~App()
{
	window.close();
}

void App::processEvent()
{
	sf::Event event;
	while (window.pollEvent(event)) {
		sm.getState()->processEvent(event);
	}
}

void App::update()
{
	dt = clock.restart().asSeconds();
	printf("%f\n", 1/dt);
	pixelPos = sf::Mouse::getPosition(window);
	worldPos = window.mapPixelToCoords(pixelPos);

	sm.getState()->update();
}

void App::draw()
{
	window.clear(sf::Color::White);
	sm.getState()->draw(0.f);
	window.display();
}

void App::run()
{
	while (window.isOpen()) {
		processEvent();
		update();
		draw();
	}
}
