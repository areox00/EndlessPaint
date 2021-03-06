#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <cstdint>
#include "chunk.hpp"
#include "viewport.hpp"
#include "types.hpp"

class Canvas : public sf::Drawable {
private:
	// maybe implement std::hash for MapKey?
	std::unordered_map<uint64_t, Chunk> chunks;
	std::unordered_map<uint64_t, sf::Texture> chunksTextures;
	std::unordered_map<uint64_t, sf::Sprite> chunksSprites;

	uint8_t brushSize = 2;
	sf::Color brushColor;

	void plotLineLow(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
	void plotLineHigh(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
	void setPointFull(GlobalPosition pos);
	void setPointOutline(GlobalPosition pos);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
	Canvas();
	~Canvas();

	void plotLine(GlobalPosition currentPosition, GlobalPosition previousPosition);

	void setBrushColor(sf::Color color);
	sf::Color getBrushColor();

	void setBrushSize(uint8_t size);
	uint8_t getBrushSize();
};