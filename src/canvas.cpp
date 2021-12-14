#include "canvas.hpp"

#include <bit>
#include <cmath>

inline int modulo(int x, int n)
{
	//return (x & n) + 1;
	return (x % n + n) % n;
}

inline sf::Vector2i globalPosToChunkIndex(sf::Vector2i pos)
{
	int x = (pos.x + (pos.x < 0)) / 512;
	int y = (pos.y + (pos.y < 0)) / 512;

	x -= pos.x < 0;
	y -= pos.y < 0;

	return {x, y};
}

inline sf::Vector2u globalPosToChunkLocalPos(sf::Vector2i pos)
{
	int x = modulo(pos.x, 512);
	int y = modulo(pos.y, 512);

	return {(unsigned int)x, (unsigned int)y};
}

inline uint64_t chunkIndexToHashmapKey(sf::Vector2i index)
{
	uint32_t ux = std::bit_cast<uint32_t>(index.x);
	uint32_t uy = std::bit_cast<uint32_t>(index.y);

	uint64_t packed = ((uint64_t)ux << 32) | ((uint64_t)uy);

	return packed;
}

inline sf::IntRect sortVertices(const sf::IntRect &rect)
{
	int left = std::min(rect.left, rect.width);
	int width = std::max(rect.left, rect.width);
	int top = std::min(rect.top, rect.height);
	int height = std::max(rect.top, rect.height);

	return {left, top, width, height};
}

Canvas::Canvas()
{

}

Canvas::~Canvas()
{

}

void Canvas::plotLineLow(sf::Vector2f start, sf::Vector2f end)
{
	int dx = end.x - start.x;
	int dy = end.y - start.y;
	int yi = 1;

	if (dy < 0) {
		yi = -1;
		dy = -dy;
	}

	int D = (2 * dy) - dx;
	int y = start.y;

	for (int x = start.x; x < end.x; x++) {
		setPointOutline({x, y});

		if (D > 0) {
			y = y + yi;
			D = D + (2 * (dy-dx));
		}
		else
			D = D + 2 * dy;
	}
	setPointFull({(int)end.x, y});
}

void Canvas::plotLineHigh(sf::Vector2f start, sf::Vector2f end)
{
	int dx = end.x - start.x;
	int dy = end.y - start.y;
	int xi = 1;

	if (dx < 0) {
		xi = -1;
		dx = -dx;
	}

	int D = (2 * dx) - dy;
	int x = start.x;

	for (int y = start.y; y < end.y; y++) {
		setPointOutline({x, y});

		if (D > 0) {
			x = x + xi;
			D = D + (2 * (dx-dy));
		}
		else
			D = D + 2 * dx;
	}
	setPointFull({x, (int)end.y});
}

void Canvas::plotLine()
{
	// Bresenham's line algorithm
	/*
		edit: I was wrong
		now instead of drawing full rectangles, I'm drawing only outlines at every point in line
		and full shape is drawn only at the end of the line
	*/

	sf::IntRect affectedChunks;

	affectedChunks.left = (int)oldPos.x;
	affectedChunks.top = (int)oldPos.y;
	affectedChunks.width = (int)newPos.x;
	affectedChunks.height = (int)newPos.y;

	affectedChunks = sortVertices(affectedChunks);

	affectedChunks.left = globalPosToChunkIndex({(int)affectedChunks.left-(int)strokeSize/2, 0}).x;
	affectedChunks.top = globalPosToChunkIndex({0, (int)affectedChunks.top-(int)strokeSize/2}).y;
	affectedChunks.width = globalPosToChunkIndex({(int)affectedChunks.width+(int)strokeSize/2, 0}).x;
	affectedChunks.height = globalPosToChunkIndex({0, (int)affectedChunks.height+(int)strokeSize/2}).y;

	// generate chunks if necessary
	for (int y = affectedChunks.top; y <= affectedChunks.height; y++)
		for (int x = affectedChunks.left; x <= affectedChunks.width; x++) {
			uint64_t key = chunkIndexToHashmapKey({x, y});
			dirtyChunks.emplace_back(key);
			if (!chunks.contains(key))
				chunks.emplace(key, sf::Vector2i{x, y});
		}

	// draw line
	setPointFull({(int)newPos.x, (int)newPos.y});
	if (std::abs(oldPos.y - newPos.y) < std::abs(oldPos.x - newPos.x)) {
		if (newPos.x > oldPos.x)
			plotLineLow(oldPos, newPos);
		else
		 	plotLineLow(newPos, oldPos);
	}
	else {
		if (newPos.y > oldPos.y)
			plotLineHigh(oldPos, newPos);
		else
			plotLineHigh(newPos, oldPos);
	}

	// check that chunk is actually dirty and update dirty chunks texture
	for (const auto &i : dirtyChunks) {
		Chunk &chunk = chunks.at(i);
		if (chunk.isDirty())
			chunk.updateTexture();
	}
}

void Canvas::setPointOutline(sf::Vector2i pos)
{
	// i feel like this is overcomplicated

	pos.x -= strokeSize/2;
	pos.y -= strokeSize/2;

	struct QueuedChunk {
		sf::Vector2i index;
		Chunk *chunk;
	};

	std::vector<QueuedChunk> affectedChunks;

	auto fetchCell = [&](sf::Vector2i index) -> QueuedChunk * {
		for (auto &cell : affectedChunks) {
			if (cell.index == index) {
				return &cell;
			}
		}

		return nullptr;
	};

	for (unsigned int y = 0; y < strokeSize; y++)
		for (unsigned int x = 0; x < strokeSize; x++) {
			if (x == 0 || x == strokeSize-1 || y == 0 || y == strokeSize - 1) {
				auto index = globalPosToChunkIndex({int(pos.x+x), int(pos.y+y)});
				if (fetchCell(index) == nullptr) {
					affectedChunks.emplace_back(index, &chunks.at(chunkIndexToHashmapKey(index)));
				}
			}
		}

	for (unsigned int y = 0; y < strokeSize; y++)
		for (unsigned int x = 0; x < strokeSize; x++) {
			if (x == 0 || x == strokeSize - 1 || y == 0 || y == strokeSize - 1) {
				sf::Vector2i index = globalPosToChunkIndex({int(pos.x+x), int(pos.y+y)});
				auto *cell = fetchCell(index);
				cell->chunk->setPixel(globalPosToChunkLocalPos({int(pos.x+x), int(pos.y+y)}));
			}
		}
}

void Canvas::setPointFull(sf::Vector2i pos)
{
	pos.x -= strokeSize/2;
	pos.y -= strokeSize/2;

	struct QueuedChunk {
		sf::Vector2i index;
		Chunk *chunk;
	};

	std::vector<QueuedChunk> affectedChunks;

	auto fetchCell = [&](sf::Vector2i index) -> QueuedChunk * {
		for (auto &cell : affectedChunks) {
			if (cell.index == index) {
				return &cell;
			}
		}

		return nullptr;
	};

	for (unsigned int y = 0; y < strokeSize; y++)
		for (unsigned int x = 0; x < strokeSize; x++) {
			auto index = globalPosToChunkIndex({int(pos.x+x), int(pos.y+y)});
			if (fetchCell(index) == nullptr) {
				affectedChunks.emplace_back(index, &chunks.at(chunkIndexToHashmapKey(index)));
			}
		}

	for (unsigned int y = 0; y < strokeSize; y++)
		for (unsigned int x = 0; x < strokeSize; x++) {
			sf::Vector2i index = globalPosToChunkIndex({int(pos.x+x), int(pos.y+y)});
			auto *cell = fetchCell(index);
			cell->chunk->setPixel(globalPosToChunkLocalPos({int(pos.x+x), int(pos.y+y)}));
		}
}

void Canvas::update(sf::Vector2f mpos)
{
	oldPos = newPos;
	newPos = mpos;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		plotLine();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		chunks.clear();
		dirtyChunks.clear();
	}
}

void Canvas::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (const auto &i : chunks)
		target.draw(i.second, states);
}