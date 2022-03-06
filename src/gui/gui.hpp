#pragma once

#include <SFML/Graphics.hpp>

enum Layout {
	FREE,
	HORIZONTAL,
	VERTICAL
};

struct Box {
	sf::FloatRect rect;
	Layout layout;
	sf::Vector2f layoutPosition;
};

class Gui {
private:
	std::vector<Box> boxes;
public:
	Gui();
	~Gui();

	sf::Vector2f getSize();
	sf::Vector2f getRemainingSize();

	void begin(sf::Vector2u windowSize, Layout layout);
	void pushBox(sf::Vector2f size, Layout layout);
	void popBox();
	bool hover(sf::Vector2f point);
	bool pressed(sf::Vector2f point);
	void resize(sf::Vector2f size);
	void offset(sf::Vector2f offset);
	void padding(sf::Vector2f pad);
	void icon(sf::RenderWindow &window, sf::Texture &texture);
	void fill(sf::RenderWindow &window, sf::Color color);
};