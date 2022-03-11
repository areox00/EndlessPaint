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
	gui.pushBox({gui.getSize().x, 32 * scale}, Layout::HORIZONTAL);
	gui.fill(app->window, sf::Color(0x16, 0x20, 0x2D));
	gui.padding({32.f * scale, 0.0});

	// block drawing when mouse enters the bar
	canPaint = !gui.hover(guiPos);

	// basic colors for testing gui
	std::vector<sf::Color> upperColors = {
		sf::Color(0xFF, 0x83, 0x60),
		sf::Color(0xE8, 0xE2, 0x88),
		sf::Color(0x7D, 0xCE, 0x82)
	};

	std::vector<sf::Color> bottomColors = {
		sf::Color(0x3C, 0xDB, 0xD3),
		sf::Color(0x42, 0xB8, 0xF6),
		sf::Color(0xA6, 0xA2, 0xF9)
	};

	// palette
	gui.pushBox({gui.getSize().y, gui.getSize().y}, Layout::HORIZONTAL);
	gui.padding({0, 6 * scale});

	sf::Color fillColor;

	// upper row
	gui.pushBox({gui.getSize().x, gui.getSize().y / 2}, Layout::VERTICAL);
	for (const auto &color : upperColors) {
		fillColor = color;
		gui.pushBox({gui.getSize().y, gui.getSize().y}, Layout::HORIZONTAL);

		if (gui.hover(guiPos)) {
			fillColor.a = 150;
		}

		if (gui.pressed(guiPos)) {
			canvas.setStrokeColor(color);
			fillColor.a = 100;
		}

		gui.fill(app->window, fillColor);
		gui.popBox();
	}
	gui.popBox();

	// bottom row
	gui.pushBox({gui.getSize().x, gui.getRemainingSize().y}, Layout::VERTICAL);
	for (const auto &color : bottomColors) {
		fillColor = color;
		gui.pushBox({gui.getSize().y, gui.getSize().y}, Layout::HORIZONTAL);

		if (gui.hover(guiPos)) {
			fillColor.a = 150;
		}

		if (gui.pressed(guiPos)) {
			canvas.setStrokeColor(color);
			fillColor.a = 100;
		}

		gui.fill(app->window, fillColor);
		gui.popBox();
	}
	gui.popBox();
	// pop palette box and return to panel box
	gui.popBox();

	gui.space(8 * scale);

	// color preview
	gui.pushBox({gui.getSize().y, gui.getSize().y}, Layout::HORIZONTAL);
	gui.padding({16.f * scale, 16.f * scale});
	gui.fill(app->window, canvas.getStrokeColor());

	// return back to world view
	app->window.setView(viewport.getView());
}