#include "input.hpp"

bool Input::locked = false;

void Input::lock()
{
	locked = true;
}

void Input::unlock()
{
	locked = false;
}

bool Input::mousePressed(sf::Mouse::Button button)
{
	return sf::Mouse::isButtonPressed(button) && !locked;
}

bool Input::mouseReleased(sf::Mouse::Button button)
{
	return !sf::Mouse::isButtonPressed(button) && !locked;
}