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

	sf::View guiView;
	guiView.setCenter((sf::Vector2f)app->window.getSize() / 2.f);
	guiView.setSize((sf::Vector2f)app->window.getSize());

	app->window.setView(guiView);

	gui.begin(app->window.getSize(), Layout::VERTICAL);
	gui.padding({32, 32});
	gui.fill(app->window, sf::Color::Black);

	gui.pushBox({300, 100},Layout::HORIZONTAL);
	gui.fill(app->window, sf::Color::Red);

	gui.popBox();

	gui.pushBox({200, 100}, Layout::VERTICAL);
	gui.fill(app->window, sf::Color::Blue);

	gui.popBox();

	gui.pushBox({100, 100}, Layout::VERTICAL);
	gui.fill(app->window, sf::Color::Green);

	app->window.setView(viewport.getView());
}