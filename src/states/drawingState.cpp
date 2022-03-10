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

	// debug remove later
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		scale += 0.1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		scale -= 0.1;
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

	// bar
	gui.pushBox({gui.getSize().x, 32 * scale}, Layout::FREE);
	gui.fill(app->window, sf::Color::Black);
	gui.padding({20.0 * scale, 0.0});

	canPaint = !gui.hover(guiPos);

	std::vector<sf::Color> colors = {
		sf::Color::Red,
		sf::Color::Blue,
		sf::Color::Green
	};

	for (const auto &color : colors) {
		gui.pushBox({16.0 * scale, gui.getSize().y}, Layout::HORIZONTAL);

		float offset = -gui.getSize().y * 0.5;

		if (canvas.getStrokeColor() == color)
			offset = -gui.getSize().y * 0.2;
		else {
			if (gui.hover(guiPos))
				offset = -gui.getSize().y * 0.2;

			if (gui.pressed(guiPos))
				canvas.setStrokeColor(color);
		}

		gui.fill(app->window, color, {0, offset});
		gui.popBox();
	}

	app->window.setView(viewport.getView());
}