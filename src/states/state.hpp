#pragma once

#include <SFML/Graphics.hpp>

class App;

class State {
protected:
	App *app;
public:
	State(App *app) : app(app) {}
	virtual ~State() {}

	virtual void processEvent(sf::Event &event) = 0;
	virtual void update() = 0;
	virtual void draw(float alpha) = 0;
};