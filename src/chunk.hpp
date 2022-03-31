#pragma once

#include <SFML/Graphics.hpp>
#include "types.hpp"

class Chunk {
private:
	sf::Uint8 pixels[CHUNK_SIZE * CHUNK_SIZE * 4];
public:
	// force inline this later
	sf::Uint8 *getPixels();
	void setPixel(PositionInChunk pos, sf::Color color);
};