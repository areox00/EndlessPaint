#include "drawingState.hpp"
#include "app.hpp"

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
	viewport.processEvent(event);

	switch (event.type) {
		case sf::Event::Closed: 
			app->window.close(); 
			break;
		case sf::Event::LostFocus: 
			canPaint = false; 
			break;
		case sf::Event::GainedFocus: 
			canPaint = true; 
			break;
		default:
			break;
	}

}

void DrawingState::update()
{
	canvas.update(app->worldPos, viewport.getBounds(), canPaint);
}

void DrawingState::draw(float alpha)
{
	app->window.setView(viewport.getView());
	canvas.draw(app->window);
}