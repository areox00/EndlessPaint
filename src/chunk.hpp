#pragma once

#include <SFML/Graphics.hpp>

struct Pixel {
	sf::Vector2u pos;
	sf::Color color; // isn't storing color in every pixel expensive? todo: reference
};

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
	constexpr bool isDirty() {return dirty;}
	constexpr sf::Vector2i &getIndex() {return index;}

	Chunk(sf::Vector2i index);
	Chunk(const Chunk &obj) = delete;
	~Chunk();
};