#include "chunk.hpp"

Chunk::Chunk(sf::Vector2i index)
	: index(index)
{
	texture.create(256, 256);
	pixels.create(256, 256);

	for (size_t y = 0; y < 256; y++)
		for (size_t x = 0; x < 256; x++) {
			pixels.setPixel(x, y, sf::Color::Black);
		}	

	texture.update(pixels);

	sprite.setPosition({index.x*256.f, index.y*256.f});
	sprite.setTexture(texture);
}

Chunk::~Chunk()
{

}

void Chunk::setPixel(sf::Vector2u pos)
{
	pixels.setPixel(pos.x, pos.y, sf::Color::Red);
	dirty = true;
}

void Chunk::updateTexture()
{	
	texture.update(pixels);
	dirty = false;
}

void Chunk::draw(sf::RenderTarget &target, sf::RenderStates states) const
{	
	target.draw(sprite, states);
}