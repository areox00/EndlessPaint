#pragma once

#include "states/stateManager.hpp"
#include "states/drawingState.hpp"

class App {
private:
	StateManager sm;

	float dt;
	sf::Clock clock;

	void processEvent();
	void draw();
	void update();
public:
	sf::RenderWindow window;

	App();
	~App();

	void run();
};
