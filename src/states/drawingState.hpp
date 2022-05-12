#pragma once

#include "state.hpp"
#include "canvas.hpp"
#include "viewport.hpp"

enum Tool {
	BRUSH,
	NONE,
};

class DrawingState : public State {
private:
	Canvas canvas;
	Viewport canvasViewport;

	Tool tool = Tool::NONE;

	bool lockDrawing;
	float brushScale = 0.0f;

	sf::Font font;

	GlobalPosition oldPos, newPos = {0, 0};
public:
	DrawingState(App *app);
	~DrawingState();

	void processEvent(sf::Event &event);
	void update();
	void draw(float alpha);
};
