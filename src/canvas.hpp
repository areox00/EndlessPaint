#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <cstdint>
#include "chunk.hpp"
#include "viewport.hpp"

class Canvas : public sf::Drawable {
private:
	std::unordered_map<uint64_t, Chunk> chunks;
	std::vector<uint64_t> dirtyChunks;

	sf::Vector2f oldPos, newPos = {0, 0};
	unsigned int strokeSize = 32;

	void plotLineLow(sf::Vector2f start, sf::Vector2f end);
	void plotLineHigh(sf::Vector2f start, sf::Vector2f end);
	void plotLine();
	void setPointFull(sf::Vector2i pos);
	void setPointOutline(sf::Vector2i pos);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
	Canvas();
	~Canvas();

	void update(sf::Vector2f mpos);
};