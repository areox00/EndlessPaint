#pragma once

#include <SFML/Graphics.hpp>

class Viewport {
private:
	sf::View view;
	float zoom = 1.f;
	float zoomLevel = 1.f;
	bool moving = false;
	sf::Vector2f oldPos = {0, 0}, newPos;
public:
	Viewport();
	~Viewport();

	void processEvent(sf::Event &event, const sf::Window &window);
	void setSize(sf::Vector2f size);
	void setCenter(sf::Vector2f center);

	sf::IntRect getBounds();
	sf::View &getView() {return view;}
};