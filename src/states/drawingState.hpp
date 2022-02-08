#pragma once

#include "state.hpp"
#include "canvas.hpp"
#include "viewport.hpp"

class DrawingState : public State {
private:
	Canvas canvas;
	Viewport viewport;
	bool canPaint = true;
public:
	DrawingState(App *app);
	~DrawingState();

	void processEvent(sf::Event &event);
	void update();
	void draw(float alpha);
};
