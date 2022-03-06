#include "canvas.hpp"

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

void Canvas::plotLine()
{
	/* Bresenham's line algorithm
	 * edit: I was wrong
	 * now instead of drawing full rectangles, I'm drawing only outlines at every point in line
	 * and full shape is drawn only at the end of the line
	 */

	sf::IntRect affectedChunks;

	affectedChunks.left = oldPos.x;
	affectedChunks.top =  oldPos.y;
	affectedChunks.width = newPos.x;
	affectedChunks.height = newPos.y;

	affectedChunks = sortVertices(affectedChunks);

	GlobalPosition leftUp = {affectedChunks.left - (int)strokeSize, affectedChunks.top - (int)strokeSize};
	GlobalPosition rightDown = {affectedChunks.width + (int)strokeSize, affectedChunks.height + (int)strokeSize};

	for (int32_t y = leftUp.chunkIndex().y; y <= rightDown.chunkIndex().y; y++)
		for (int32_t x = leftUp.chunkIndex().x; x <= rightDown.chunkIndex().x; x++) {
			auto key = ChunkIndex{x, y}.mapKey().key;

			chunks.try_emplace(key);
			chunksTextures[key].create(CHUNK_SIZE, CHUNK_SIZE);
			chunksSprites[key].setTexture(chunksTextures[key]);

			chunksSprites[key].setPosition(x * CHUNK_SIZE, y * CHUNK_SIZE);
		}

	setPointFull(newPos);
	if (std::abs(oldPos.y - newPos.y) < std::abs(oldPos.x - newPos.x)) {
		if (newPos.x > oldPos.x)
			plotLineLow(oldPos.x, oldPos.y, newPos.x, newPos.y);
		else
		 	plotLineLow(newPos.x, newPos.y, oldPos.x, oldPos.y);
	}
	else {
		if (newPos.y > oldPos.y)
			plotLineHigh(oldPos.x, oldPos.y, newPos.x, newPos.y);
		else
			plotLineHigh(newPos.x, newPos.y, oldPos.x, oldPos.y);
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
	for (uint8_t y = 0; y < strokeSize; y++)
		for (uint8_t x = 0; x < strokeSize; x++) {
			if (x == 0 || x == strokeSize - 1 || y == 0 || y == strokeSize - 1) {
				auto finalPos = GlobalPosition{pos.x + x, pos.y + y};
				chunks.at(finalPos.chunkIndex().mapKey().key).setPixel(finalPos.positionInChunk(), strokeColor);
			}
		}
}

void Canvas::setPointFull(GlobalPosition pos)
{
	for (uint8_t y = 0; y < strokeSize; y++)
		for (uint8_t x = 0; x < strokeSize; x++) {
			auto finalPos = GlobalPosition{pos.x + x, pos.y + y};
			chunks.at(finalPos.chunkIndex().mapKey().key).setPixel(finalPos.positionInChunk(), strokeColor);
		}
}

void Canvas::update(sf::Vector2f mpos, sf::IntRect bounds, bool canPaint)
{
	mpos.x -= (mpos.x < 0);
	mpos.y -= (mpos.y < 0);

	oldPos = newPos;
	newPos = GlobalPosition{(int32_t)mpos.x, (int32_t)mpos.y};

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && canPaint) {
		plotLine();
	}
}

void Canvas::draw(sf::RenderTarget &target)
{
	for (const auto &i : chunksSprites) {
		target.draw(i.second);
	}
}

void Canvas::setStrokeColor(sf::Color color)
{
	strokeColor = color;
}

sf::Color Canvas::getStrokeColor()
{
	return strokeColor;
}