#pragma once

#include "state.hpp"
#include "canvas.hpp"
#include "viewport.hpp"
#include "gui/gui.hpp"

class DrawingState : public State {
private:
	Canvas canvas;
	Viewport viewport;
	bool canPaint = true;

	Gui gui;
	float strokeSize = 0.0f;

	void processGui();
public:
	DrawingState(App *app);
	~DrawingState();

	void processEvent(sf::Event &event);
	void update();
	void draw(float alpha);
};
