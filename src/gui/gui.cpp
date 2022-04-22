#include "gui.hpp"

#include <algorithm>
#include "input.hpp"

Gui::Gui()
{

}

Gui::~Gui()
{

}

sf::Vector2f Gui::getSize()
{
	return {
		boxes.back().rect.width / scaleFactor,
		boxes.back().rect.height / scaleFactor
	};
}

sf::Vector2f Gui::getRemainingSize()
{
	return {
		getSize().x - boxes.back().layoutPosition.x / scaleFactor,
		getSize().y - boxes.back().layoutPosition.y / scaleFactor
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
	size *= scaleFactor;
	sf::Vector2f topPosition = { boxes.back().rect.left, boxes.back().rect.top };

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

bool Gui::isAction(sf::Vector2f point)
{
	return hover(point) || action;
}

bool Gui::hover(sf::Vector2f point)
{
	return boxes.back().rect.contains(point) && !action;
}

bool Gui::pressed(sf::Vector2f point)
{
	return hover(point) && Input::mousePressed(sf::Mouse::Left);
}

void Gui::padding(sf::Vector2f value)
{
	value *= scaleFactor;
	boxes.back().rect.left += value.x / 2.f;
	boxes.back().rect.width -= value.x;
	boxes.back().rect.top += value.y / 2.f;
	boxes.back().rect.height -= value.y;
}

void Gui::space(float value)
{
	value *= scaleFactor;
	switch (boxes.back().layout) {
		case Layout::FREE:
			throw std::logic_error("Cannot use spacing with free layout");
			break;
		case Layout::HORIZONTAL:
			boxes.back().layoutPosition.x += value;
			break;
		case Layout::VERTICAL:
			boxes.back().layoutPosition.y += value;
			break;
	}
}

void Gui::fill(sf::RenderWindow &window, sf::Color color, sf::Vector2f offset)
{
	sf::RectangleShape shape;
	shape.setPosition(boxes.back().rect.left + offset.x, boxes.back().rect.top + offset.y);
	shape.setSize({boxes.back().rect.width, boxes.back().rect.height});
	shape.setFillColor(color);

	window.draw(shape);
}

void Gui::slider(sf::RenderWindow &window, sf::Vector2f mouse, float &value)
{
	sf::RectangleShape bar;
	bar.setPosition(boxes.back().rect.left, boxes.back().rect.top);
	bar.setSize({boxes.back().rect.width, boxes.back().rect.height / 2.f});
	bar.setFillColor(sf::Color(0xB0, 0xC5, 0xE1));

	if (hover(mouse) && Input::mousePressed(sf::Mouse::Left))
		action = true;
	else if (Input::mouseReleased(sf::Mouse::Left))
		action = false;

	if (action) {
		value = (mouse.x - boxes.back().rect.left) / boxes.back().rect.width;
		value = std::clamp(value, 0.f, 1.f);
	}

	sf::RectangleShape progress;
	progress.setPosition(boxes.back().rect.left, boxes.back().rect.top);
	progress.setSize({boxes.back().rect.width * value, boxes.back().rect.height / 2.f});
	progress.setFillColor(sf::Color(0x37, 0x72, 0xFF));

	sf::CircleShape handle;
	handle.setRadius(boxes.back().rect.height / 2.f);
	handle.setOrigin({handle.getRadius() / 2.f, handle.getRadius() / 2.f});
	handle.setPosition(boxes.back().rect.left + boxes.back().rect.width * value, boxes.back().rect.top);

	window.draw(bar);
	window.draw(progress);
	window.draw(handle);
}

void Gui::text(sf::RenderWindow &window, unsigned int characterSize, const std::string &string, const sf::Font &font, AlignH alignH, AlignV alignV)
{
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(characterSize * scaleFactor);
	text.setString(string);
	text.setPosition((int)boxes.back().rect.left, (int)boxes.back().rect.top);

	switch (alignH) {
		case AlignH::LEFT:
			break;
		case AlignH::CENTER:
			text.move(int(boxes.back().rect.width / 2.f - text.getGlobalBounds().width / 2.f), 0);
			break;
		case AlignH::RIGHT:
			text.move(int(boxes.back().rect.width - text.getGlobalBounds().width), 0);
			break;
	}

	switch (alignV) {
		case AlignV::TOP:
			break;
		case AlignV::CENTER:
			text.move(0, int(boxes.back().rect.height / 2.f - font.getLineSpacing(characterSize * scaleFactor) / 2.f));
			break;
		case AlignV::BOTTOM:
			text.move(0, int(boxes.back().rect.height - text.getGlobalBounds().height));
			break;
	}

	window.draw(text);
}