#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <cstdint>
#include "chunk.hpp"
#include "viewport.hpp"
#include "types.hpp"

class Canvas {
private:
	// maybe implement std::hash for MapKey?
	std::unordered_map<uint64_t, Chunk> chunks;
	std::unordered_map<uint64_t, sf::Texture> chunksTextures;
	std::unordered_map<uint64_t, sf::Sprite> chunksSprites;

	GlobalPosition oldPos, newPos;
	uint8_t strokeSize = 1;
	sf::Color strokeColor = sf::Color::Black;

	void plotLineLow(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
	void plotLineHigh(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
	void plotLine();
	void setPointFull(GlobalPosition pos);
	void setPointOutline(GlobalPosition pos);
public:
	Canvas();
	~Canvas();

	void draw(sf::RenderTarget &target);
	void update(sf::Vector2f mpos, sf::IntRect bounds, bool canPaint);

	void setStrokeColor(sf::Color color);
	sf::Color getStrokeColor();
};