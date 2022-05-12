#include "viewport.hpp"

#include <cmath>
#include <algorithm>

Viewport::Viewport()
{

}

Viewport::~Viewport()
{

}

sf::Vector2f Viewport::getMousePosition(sf::RenderWindow &window)
{
	return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

void Viewport::zoom(float level)
{
	zoomLevel -= level;
	zoomLevel = std::clamp(zoomLevel, -24.f, 8.f);
	zoomValue = powf(2.f, zoomLevel * 0.25f);
	view.setSize(cachedSize * zoomValue);
}

void Viewport::processGrabbing(sf::Event &event, sf::Window &window)
{
	switch (event.type) {
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Right) {
				moving = true;
				oldPos = (sf::Vector2f)sf::Mouse::getPosition(window);
			}
			break;

		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Right) {
				moving = false;
			}
			break;

		case sf::Event::MouseMoved: {
			if (!moving)
				break;

			newPos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);

			sf::Vector2f deltaPos = oldPos - newPos;
			deltaPos *= zoomValue;

			view.move(deltaPos);
			oldPos = newPos;
			break;
		}
		default:
			break;
	}
}

void Viewport::setSize(sf::Vector2f size)
{
	cachedSize = size;
	view.setSize(size * zoomValue);
}
void Viewport::setCenter(sf::Vector2f center)
{
	view.setCenter(center);
}

sf::IntRect Viewport::getBounds()
{
	int left = view.getCenter().x - view.getSize().x / 2.f;
	int right = view.getCenter().x + view.getSize().x / 2.f;
	int top = view.getCenter().y + view.getSize().y / 2.f;
	int down = view.getCenter().y - view.getSize().y / 2.f;

	return {left, right, top, down};
}

void Viewport::setView(sf::RenderWindow &window)
{
	window.setView(view);
}