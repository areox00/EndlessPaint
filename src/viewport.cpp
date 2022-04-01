#include "viewport.hpp"

#include <cmath>
#include <algorithm>

Viewport::Viewport()
{

}

Viewport::~Viewport()
{

}

void Viewport::processEvent(sf::Event &event, const sf::Window &window)
{
	switch (event.type) {
		case sf::Event::Resized:
			view.setSize((sf::Vector2f)window.getSize() * zoom);
			break;

		case sf::Event::MouseWheelScrolled:
			zoomLevel += -event.mouseWheelScroll.delta;
			zoomLevel = std::clamp(zoomLevel, -24.f, 8.f);
			zoom = powf(2.f, zoomLevel * 0.25f);
			view.setSize((sf::Vector2f)window.getSize() * zoom);
			break;

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
			deltaPos *= (float)zoom;

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
	view.setSize(size);
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