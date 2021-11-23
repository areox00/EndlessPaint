#pragma once

#include <SFML/Graphics.hpp>

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
	inline bool isDirty() {return dirty;}
	inline sf::Vector2i getIndex() {return index;}

	Chunk(sf::Vector2i index);
	Chunk(const Chunk &obj) = delete;
	~Chunk();
};