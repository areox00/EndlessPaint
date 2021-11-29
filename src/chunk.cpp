#include "chunk.hpp"

Chunk::Chunk(sf::Vector2i index)
	: index(index)
{
	texture.create(512, 512);
	pixels.create(512, 512);

	for (unsigned int y = 0; y < 512; y++)
		for (unsigned int x = 0; x < 512; x++) {
			pixels.setPixel(x, y, sf::Color::Black);
		}

	texture.update(pixels);

	sprite.setPosition({index.x*512.f, index.y*512.f});
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