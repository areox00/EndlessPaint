#pragma once

#include <SFML/Graphics.hpp>

enum class AlignH {
	LEFT,
	CENTER,
	RIGHT
};

enum class AlignV {
	TOP,
	CENTER,
	BOTTOM
};

enum class Layout {
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
	float scaleFactor = 1.f;
	bool action = false;
public:
	Gui();
	~Gui();

	sf::Vector2f getSize();
	sf::Vector2f getRemainingSize();

	void begin(sf::Vector2u windowSize, Layout layout);
	void pushBox(sf::Vector2f size, Layout layout);
	void popBox();
	bool isAction(sf::Vector2f point);
	bool hover(sf::Vector2f point);
	bool pressed(sf::Vector2f point);
	void padding(sf::Vector2f value);
	void space(float value);
	void fill(sf::RenderWindow &window, sf::Color color, sf::Vector2f offset = {0, 0});
	void slider(sf::RenderWindow &window, sf::Vector2f mouse, float &value);
	void text(sf::RenderWindow &window, unsigned int characterSize, const std::string &string, const sf::Font &font, AlignH alignH, AlignV alignV);

	void setScale(float value) { scaleFactor = value; }
	void scale(float value) { scaleFactor *= value; }
};