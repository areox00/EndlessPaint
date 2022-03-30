#pragma once

#include "state.hpp"
#include "canvas.hpp"
#include "viewport.hpp"
#include "gui/gui.hpp"

enum Tool {
	BRUSH,
	NONE,
};

class DrawingState : public State {
private:
	Canvas canvas;
	Viewport viewport;

	Tool tool = Tool::NONE;

	Gui gui;
	bool block;
	float strokeScale = 0.0f;

	GlobalPosition oldPos, newPos = {0, 0};

	void processGui();
public:
	DrawingState(App *app);
	~DrawingState();

	void processEvent(sf::Event &event);
	void update();
	void draw(float alpha);
};
