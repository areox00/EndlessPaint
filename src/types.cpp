#include "types.hpp"

GlobalPosition vec2GlobalPos(sf::Vector2f pos)
{
	pos.x -= (pos.x < 0);
	pos.y -= (pos.y < 0);

	return GlobalPosition{(int32_t)pos.x, (int32_t)pos.y};
}