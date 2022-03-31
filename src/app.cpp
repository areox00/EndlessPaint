#include "app.hpp"

App::App()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(sf::VideoMode(1280, 720), "EndlessPaint", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);
	sm.setState(new DrawingState(this));
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

	//printf("%f\n", 1 / dt);
	//printf("%f\n", dt);

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