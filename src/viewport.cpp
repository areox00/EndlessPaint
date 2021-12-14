#include "viewport.hpp"

#include <cmath>

Viewport::Viewport(const sf::RenderWindow *window)
	: window(window)
{
	view.setSize(window->getSize().x, window->getSize().y);
	view.setCenter(0, 0);
}

Viewport::~Viewport()
{

}

void Viewport::init(sf::RenderWindow *window)
{
	view.setSize(window->getSize().x, window->getSize().y);
	view.setCenter(0, 0);
	this->window = window;
}

void Viewport::processEvent(sf::Event &event)
{
	switch (event.type) {
		case sf::Event::Resized:
			view.setSize(event.size.width*zoom, event.size.height*zoom);
			break;

		case sf::Event::MouseWheelScrolled:
			if(event.mouseWheelScroll.delta > 0) {
				zoom *= 0.9;
				view.zoom(0.9);
			}
			else if(event.mouseWheelScroll.delta < 0) {
				if (zoom < 4.f) {
					zoom *= 1.1;
					view.zoom(1.1);
				}
			}
			break;

		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Right) {
				moving = true;
				oldPos = (sf::Vector2f)sf::Mouse::getPosition(*window);
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
			deltaPos *= zoom;

			view.move(deltaPos);
			oldPos = newPos;
			break;
		}
		default:
			break;
	}
}

sf::IntRect Viewport::getBounds()
{
	int left = view.getCenter().x - view.getSize().x / 2.f;
	int right = view.getCenter().x + view.getSize().x / 2.f;
	int top = view.getCenter().y + view.getSize().y / 2.f;
	int down = view.getCenter().y - view.getSize().y / 2.f;
	printf("%d %d %d %d\n", left, right, top, down);
}