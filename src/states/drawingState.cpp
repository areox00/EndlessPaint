#include "drawingState.hpp"
#include "app.hpp"
#include "input.hpp"

DrawingState::DrawingState(App *app)
	: State(app)
{
	canvas.setBrushColor(sf::Color(0xFF, 0x83, 0x60));

	viewport.setSize((sf::Vector2f)app->window.getSize());
	viewport.setCenter({0, 0});

	font.loadFromFile("res/fonts/UbuntuMono-Bold.ttf");
}

DrawingState::~DrawingState()
{

}

void DrawingState::processGui()
{
	sf::View guiView;
	guiView.setCenter((sf::Vector2f)app->window.getSize() / 2.f);
	guiView.setSize((sf::Vector2f)app->window.getSize());
	app->window.setView(guiView);

	mouseGuiPos = app->window.mapPixelToCoords(mouseWindowPos, guiView);

	if (tool != Tool::NONE)
		Input::lock();

	gui.begin(app->window.getSize(), Layout::VERTICAL);

	// bar
	gui.pushBox({gui.getSize().x, 32}, Layout::HORIZONTAL);
	gui.fill(app->window, sf::Color(0x16, 0x20, 0x2D));

	if (gui.isAction(mouseGuiPos))
		lockDrawing = true;
	else if (Input::mouseReleased(sf::Mouse::Left))
		lockDrawing = false;

	gui.padding({32.f , 0.0});

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
	gui.pushBox({gui.getSize().y / 2 * 3, gui.getSize().y}, Layout::HORIZONTAL);
	gui.padding({6.f, 6.f});

	sf::Color fillColor;

	// upper row
	gui.pushBox({gui.getSize().x, gui.getSize().y / 2}, Layout::VERTICAL);
	for (const auto &color : upperColors) {
		fillColor = color;
		gui.pushBox({gui.getSize().y, gui.getSize().y}, Layout::HORIZONTAL);

		if (gui.hover(mouseGuiPos)) {
			fillColor.a = 150;
		}

		if (gui.pressed(mouseGuiPos)) {
			canvas.setBrushColor(color);
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

		if (gui.hover(mouseGuiPos)) {
			fillColor.a = 150;
		}

		if (gui.pressed(mouseGuiPos)) {
			canvas.setBrushColor(color);
			fillColor.a = 100;
		}

		gui.fill(app->window, fillColor);
		gui.popBox();
	}
	gui.popBox();
	// pop palette box and return to panel box
	gui.popBox();

	// color preview
	gui.pushBox({gui.getSize().y, gui.getSize().y}, Layout::HORIZONTAL);
	gui.padding(gui.getSize() / 2.f);
	gui.fill(app->window, canvas.getBrushColor());
	gui.popBox();

	gui.space(8.f);

	// text
	gui.pushBox({80, gui.getSize().y / 2.f}, Layout::VERTICAL);
	gui.padding({0, 6.f});
	gui.text(app->window, gui.getSize().y, "brush size: " + std::to_string(int(brushScale * 63) + 1), font);
	gui.popBox();

	// slider
	gui.pushBox({80, gui.getRemainingSize().y}, Layout::HORIZONTAL);
	gui.padding({0, 6.f});
	gui.slider(app->window, mouseGuiPos, brushScale);
	canvas.setBrushSize(int(brushScale * 63) + 1);

	Input::unlock();
}

void DrawingState::processEvent(sf::Event &event)
{
	viewport.processEvent(event, app->window);

	switch (event.type) {
		case sf::Event::Closed:
			app->window.close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Equal)
				gui.scale(1.1);
			if (event.key.code == sf::Keyboard::Hyphen)
				gui.scale(0.9);
			break;
		default:
			break;
	}
}

void DrawingState::update()
{
	mouseWindowPos = sf::Mouse::getPosition(app->window);
	mouseCanvasPos = app->window.mapPixelToCoords(mouseWindowPos, viewport.getView());

	oldPos = newPos;
	newPos = vec2GlobalPos(mouseCanvasPos);

	if (!app->window.hasFocus())
		Input::lock();

	if (Input::mousePressed(sf::Mouse::Left) && !lockDrawing)
		tool = Tool::BRUSH;
	else if (Input::mouseReleased(sf::Mouse::Left))
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
	app->window.setView(viewport.getView());
	app->window.draw(canvas);

	processGui();
}