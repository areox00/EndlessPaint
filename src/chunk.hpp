#pragma once

#include <SFML/Graphics.hpp>

#define CHUNK_SIZE 512

class Chunk : public sf::Drawable {
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Image pixels;
	sf::Vector2i index;
	bool dirty = false;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
	void setPixel(sf::Vector2u pos);
	void updateTexture();
	inline bool isDirty() const { return dirty; }
	inline sf::Vector2i getIndex() const { return index; }
	inline const sf::Uint8 *getPixelData() const { return pixels.getPixelsPtr(); }
	bool isVisible(const sf::IntRect &bounds) const;

	Chunk(sf::Vector2i index);
	Chunk(const Chunk &obj) = delete;
	~Chunk();
};