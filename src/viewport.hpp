#pragma once

#include <SFML/Graphics.hpp>

class Viewport {
private:
	sf::View view;
	sf::Vector2f cachedSize;
	float zoomValue = 1.f;
	float zoomLevel = 1.f;
	bool moving = false;
	sf::Vector2f oldPos = {0, 0}, newPos;
public:
	Viewport();
	~Viewport();

	sf::Vector2f getMousePosition(sf::RenderWindow &window);
	void zoom(float level);
	void processGrabbing(sf::Event &event, sf::Window &window);
	void setSize(sf::Vector2f size);
	void setCenter(sf::Vector2f center);

	sf::IntRect getBounds();
	void setView(sf::RenderWindow &window);
};