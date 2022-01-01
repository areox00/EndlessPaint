#include "chunk.hpp"

Chunk::Chunk(sf::Vector2i index)
	: index(index)
{
	pixels.create(CHUNK_SIZE, CHUNK_SIZE, sf::Color::White);
	texture.create(CHUNK_SIZE, CHUNK_SIZE);

	texture.update(pixels);

	sprite.setPosition({index.x*float(CHUNK_SIZE), index.y*float(CHUNK_SIZE)});
	sprite.setTexture(texture);
}

Chunk::~Chunk()
{

}

bool Chunk::isVisible(const sf::IntRect &bounds) const
{
	if (sprite.getPosition().x <= bounds.width &&
	    sprite.getPosition().x >= bounds.left - CHUNK_SIZE &&
		sprite.getPosition().y <= bounds.top &&
		sprite.getPosition().y >= bounds.height - CHUNK_SIZE) {
			return true;
		}
	return false;
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
