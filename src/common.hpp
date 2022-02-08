#pragma once

#include <stdint.h>
#include <SFML/Graphics.hpp>

inline int32_t modulo(int32_t x, int32_t n)
{
	return (x % n + n) % n;
}

inline sf::IntRect sortVertices(const sf::IntRect &rect)
{
	int left = std::min(rect.left, rect.width);
	int width = std::max(rect.left, rect.width);
	int top = std::min(rect.top, rect.height);
	int height = std::max(rect.top, rect.height);

	return {left, top, width, height};
}