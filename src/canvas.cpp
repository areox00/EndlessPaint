#include "canvas.hpp"
#include "input.hpp"

Canvas::Canvas()
{

}

Canvas::~Canvas()
{

}

void Canvas::plotLineLow(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int yi = 1;

	if (dy < 0) {
		yi = -1;
		dy = -dy;
	}

	int D = (2 * dy) - dx;
	int y = y1;

	for (int x = x1; x < x2; x++) {
		setPointOutline({x, y});

		if (D > 0) {
			y = y + yi;
			D = D + (2 * (dy-dx));
		}
		else
			D = D + 2 * dy;
	}
	setPointFull({x2, y});
}

void Canvas::plotLineHigh(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int xi = 1;

	if (dx < 0) {
		xi = -1;
		dx = -dx;
	}

	int D = (2 * dx) - dy;
	int x = x1;

	for (int y = y1; y < y2; y++) {
		setPointOutline({x, y});

		if (D > 0) {
			x = x + xi;
			D = D + (2 * (dx-dy));
		}
		else
			D = D + 2 * dx;
	}
	setPointFull({x, y2});
}

void Canvas::plotLine(GlobalPosition currentPosition, GlobalPosition previousPosition)
{
	/* Bresenham's line algorithm
	 * edit: I was wrong
	 * now instead of drawing full rectangles, I'm drawing only outlines at every point in line
	 * and full shape is drawn only at the end of the line
	 */

	sf::IntRect affectedChunks;

	affectedChunks.left = previousPosition.x;
	affectedChunks.top = previousPosition.y;
	affectedChunks.width = currentPosition.x;
	affectedChunks.height = currentPosition.y;

	affectedChunks = sortVertices(affectedChunks);

	GlobalPosition leftUp = {affectedChunks.left - (int)brushSize, affectedChunks.top - (int)brushSize};
	GlobalPosition rightDown = {affectedChunks.width + (int)brushSize, affectedChunks.height + (int)brushSize};

	for (int32_t y = leftUp.chunkIndex().y; y <= rightDown.chunkIndex().y; y++)
		for (int32_t x = leftUp.chunkIndex().x; x <= rightDown.chunkIndex().x; x++) {
			auto key = ChunkIndex{x, y}.mapKey().key;

			chunks.try_emplace(key);
			chunksTextures[key].create(CHUNK_SIZE, CHUNK_SIZE);
			chunksSprites[key].setTexture(chunksTextures[key]);
			chunksSprites[key].setPosition(x * CHUNK_SIZE, y * CHUNK_SIZE);
		}

	setPointFull(currentPosition);
	if (std::abs(previousPosition.y - currentPosition.y) < std::abs(previousPosition.x - currentPosition.x)) {
		if (currentPosition.x > previousPosition.x)
			plotLineLow(previousPosition.x, previousPosition.y, currentPosition.x, currentPosition.y);
		else
		 	plotLineLow(currentPosition.x, currentPosition.y, previousPosition.x, previousPosition.y);
	}
	else {
		if (currentPosition.y > previousPosition.y)
			plotLineHigh(previousPosition.x, previousPosition.y, currentPosition.x, currentPosition.y);
		else
			plotLineHigh(currentPosition.x, currentPosition.y, previousPosition.x, previousPosition.y);
	}

	for (int32_t y = leftUp.chunkIndex().y; y <= rightDown.chunkIndex().y; y++)
		for (int32_t x = leftUp.chunkIndex().x; x <= rightDown.chunkIndex().x; x++) {
			auto key = ChunkIndex{x, y}.mapKey().key;
			chunksTextures[key].update(chunks[key].getPixels());
			chunksTextures[key].generateMipmap();
		}
}

void Canvas::setPointOutline(GlobalPosition pos)
{
	pos.x -= brushSize / 2;
	pos.y -= brushSize / 2;

	for (uint8_t y = 0; y < brushSize; y++)
		for (uint8_t x = 0; x < brushSize; x++) {
			if (x == 0 || x == brushSize - 1 || y == 0 || y == brushSize - 1) {
				auto finalPos = GlobalPosition{pos.x + x, pos.y + y};
				chunks.at(finalPos.chunkIndex().mapKey().key).setPixel(finalPos.positionInChunk(), brushColor);
			}
		}
}

void Canvas::setPointFull(GlobalPosition pos)
{
	pos.x -= brushSize / 2;
	pos.y -= brushSize / 2;

	for (uint8_t y = 0; y < brushSize; y++)
		for (uint8_t x = 0; x < brushSize; x++) {
			auto finalPos = GlobalPosition{pos.x + x, pos.y + y};
			chunks.at(finalPos.chunkIndex().mapKey().key).setPixel(finalPos.positionInChunk(), brushColor);
		}
}

void Canvas::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto &i : chunksSprites) {
		target.draw(i.second, states);
	}
}

void Canvas::setBrushColor(sf::Color color)
{
	brushColor = color;
}

sf::Color Canvas::getBrushColor()
{
	return brushColor;
}

void Canvas::setBrushSize(uint8_t size)
{
	brushSize = size;
}

uint8_t Canvas::getBrushSize()
{
	return brushSize;
}