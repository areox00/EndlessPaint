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
	//guiView.zoom(1.1);
	app->window.setView(guiView);

	sf::Vector2f guiPos = app->window.mapPixelToCoords(app->pixelPos);

	gui.begin(app->window.getSize(), Layout::VERTICAL);

	// empty space
	gui.pushBox({gui.getSize().x, gui.getSize().y - 32}, Layout::VERTICAL);
	gui.popBox();

	// bottom bar
	gui.pushBox({gui.getSize().x, gui.getRemainingSize().y}, Layout::FREE);
	gui.fill(app->window, sf::Color::Black);
	gui.padding({20.0, 0.0});

	canPaint = !gui.hover(guiPos);

	std::vector<sf::Color> colors = {
		sf::Color::Red,
		sf::Color::Blue,
		sf::Color::Green
	};

	for (const auto &color : colors) {
		gui.pushBox({16.0, gui.getSize().y}, Layout::HORIZONTAL);
		gui.offset({0, gui.getSize().y / 2.f});

		if (canvas.getStrokeColor() == color)
			gui.offset({0, -6});
		else {
			if (gui.hover(guiPos))
				gui.offset({0, -6});

			if (gui.pressed(guiPos))
				canvas.setStrokeColor(color);
		}

		gui.fill(app->window, color);
		gui.popBox();
	}

	app->window.setView(viewport.getView());
}