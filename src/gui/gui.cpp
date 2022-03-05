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

void Gui::padding(sf::Vector2f pad)
{
	boxes.back().rect.left += pad.x / 2.0;
	boxes.back().rect.width -= pad.x;
	boxes.back().rect.top += pad.y / 2.0;
	boxes.back().rect.height -= pad.y;
}

void Gui::fill(sf::RenderWindow &window, sf::Color color)
{
	sf::RectangleShape shape;
	shape.setPosition(boxes.back().rect.left, boxes.back().rect.top);
	shape.setSize({boxes.back().rect.width, boxes.back().rect.height});
	shape.setFillColor(color);

	window.draw(shape);
}