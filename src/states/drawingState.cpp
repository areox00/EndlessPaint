#include "drawingState.hpp"
#include "../app.hpp"

DrawingState::DrawingState(App *app)
	: State(app)
{
	viewport.init(&app->window);
}

DrawingState::~DrawingState()
{

}

void DrawingState::processEvent(sf::Event &event)
{
	if (event.type == sf::Event::Closed)
		app->window.close();

	viewport.processEvent(event);
}

void DrawingState::update()
{
	canvas.update(app->worldPos, viewport.getBounds());
}

void DrawingState::draw(float alpha)
{
	app->window.setView(viewport.getView());
	app->window.draw(canvas);
}