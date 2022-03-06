#include "gui.hpp"

Gui::Gui()
{

}

Gui::~Gui()
{

}

sf::Vector2f Gui::getSize()
{
	return {boxes.back().rect.width, boxes.back().rect.height};
}

sf::Vector2f Gui::getRemainingSize()
{
	return {
		getSize().x - boxes.back().layoutPosition.x,
		getSize().y - boxes.back().layoutPosition.y
	};
}

void Gui::begin(sf::Vector2u windowSize, Layout layout)
{
	boxes.clear();

	Box box = {
		sf::FloatRect{
			0,
			0,
			windowSize.x,
			windowSize.y
		},
		layout,
		sf::Vector2f{0, 0}
	};

	boxes.emplace_back(box);
}

void Gui::pushBox(sf::Vector2f size, Layout layout)
{
	sf::Vector2f topPosition = {boxes.back().rect.left, boxes.back().rect.top};

	Box box = {
		sf::FloatRect{
			topPosition.x + boxes.back().layoutPosition.x,
			topPosition.y + boxes.back().layoutPosition.y,
			size.x,
			size.y
		},
		layout,
		sf::Vector2f{0, 0}
	};

	switch (layout) {
		case Layout::FREE:
			break;
		case Layout::HORIZONTAL:
			boxes.back().layoutPosition.x += box.rect.width;
			break;
		case Layout::VERTICAL:
			boxes.back().layoutPosition.y += box.rect.height;
			break;
	}

	boxes.emplace_back(box);
}

void Gui::popBox()
{
	boxes.pop_back();
}

bool Gui::hover(sf::Vector2f point)
{
	return boxes.back().rect.contains(point);
}

bool Gui::pressed(sf::Vector2f point)
{
	return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && hover(point);
}

void Gui::resize(sf::Vector2f size)
{
	boxes.back().rect.width = size.x;
	boxes.back().rect.height = size.y;
}

void Gui::offset(sf::Vector2f offset)
{
	boxes.back().rect.left += offset.x;
	boxes.back().rect.top += offset.y;
}

void Gui::padding(sf::Vector2f pad)
{
	boxes.back().rect.left += pad.x / 2.0;
	boxes.back().rect.width += pad.x;
	boxes.back().rect.top += pad.y / 2.0;
	boxes.back().rect.height += pad.y;
}

void Gui::icon(sf::RenderWindow &window, sf::Texture &texture)
{

}

void Gui::fill(sf::RenderWindow &window, sf::Color color)
{
	sf::RectangleShape shape;
	shape.setPosition(boxes.back().rect.left, boxes.back().rect.top);
	shape.setSize({boxes.back().rect.width, boxes.back().rect.height});
	shape.setFillColor(color);

	window.draw(shape);
}