#include "drawingState.hpp"
#include "app.hpp"

DrawingState::DrawingState(App *app)
	: State(app)
{
	canvas.setBrushColor(sf::Color(0xFF, 0x83, 0x60));

	canvasViewport.setSize((sf::Vector2f)app->window.getSize());
	canvasViewport.setCenter({0, 0});

	font.loadFromFile("res/fonts/UbuntuMono-Bold.ttf");
}

DrawingState::~DrawingState()
{

}

void DrawingState::processEvent(sf::Event &event)
{
	canvasViewport.processGrabbing(event, app->window);
	switch (event.type) {
		case sf::Event::Closed:
			app->window.close();
			break;
		case sf::Event::MouseWheelScrolled:
			canvasViewport.zoom(event.mouseWheelScroll.delta);
			break;
		case sf::Event::Resized:
			canvasViewport.setSize((sf::Vector2f)app->window.getSize());
			break;
		default:
			break;
	}
}

void DrawingState::update()
{
	oldPos = newPos;
	newPos = vec2GlobalPos(canvasViewport.getMousePosition(app->window));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !lockDrawing)
		tool = Tool::BRUSH;
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		tool = Tool::NONE;

	switch (tool) {
		case Tool::BRUSH:
			canvas.plotLine(newPos, oldPos);
			break;
		case Tool::NONE:
			break;
	}
}

void DrawingState::draw(float alpha)
{
	canvasViewport.setView(app->window);
	app->window.draw(canvas);
}