#pragma once

#include <SFML/Window.hpp>

class Input {
private:
	static bool locked;
public:
	static void lock();
	static void unlock();

	static bool mousePressed(sf::Mouse::Button button);
	static bool mouseReleased(sf::Mouse::Button button);
};