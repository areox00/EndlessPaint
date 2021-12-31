#pragma once

#include <SFML/Graphics.hpp>

class Viewport {
private:
	const sf::RenderWindow *window;

	sf::View view;
	float zoom = 1.0;
	bool moving = false;
	sf::Vector2f oldPos = {0, 0}, newPos;
public:
	Viewport() = default;
	Viewport(const sf::RenderWindow *window);
	~Viewport();

	void init(sf::RenderWindow *window);
	void processEvent(sf::Event &event);
	const sf::IntRect getBounds();
	inline const sf::View &getView() {return view;}
};