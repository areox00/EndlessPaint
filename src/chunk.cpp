#include "chunk.hpp"

sf::Uint8 *Chunk::getPixels()
{
	return pixels;
}

void Chunk::setPixel(PositionInChunk pos, sf::Color color)
{
	pixels[(pos.x + pos.y * CHUNK_SIZE) * 4] = color.r;
	pixels[(pos.x + pos.y * CHUNK_SIZE) * 4 + 1] = color.g;
	pixels[(pos.x + pos.y * CHUNK_SIZE) * 4 + 2] = color.b;
	pixels[(pos.x + pos.y * CHUNK_SIZE) * 4 + 3] = 255;
}
