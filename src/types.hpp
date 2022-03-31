#pragma once

#include <bit>
#include "common.hpp"

#define CHUNK_SIZE 512

struct MapKey {
	uint64_t key;
};

struct ChunkIndex {
	int32_t x, y;
	MapKey mapKey()
	{
		uint32_t ux = std::bit_cast<uint32_t>(x);
		uint32_t uy = std::bit_cast<uint32_t>(y);

		uint64_t packed = ((uint64_t)ux << 32) | ((uint64_t)uy);

		return MapKey(packed);
	}
};

struct PositionInChunk {
	uint16_t x, y;
};

struct GlobalPosition {
	int32_t x, y;
	PositionInChunk positionInChunk()
	{
		uint16_t x2 = modulo(x, CHUNK_SIZE);
		uint16_t y2 = modulo(y, CHUNK_SIZE);

		return PositionInChunk(x2, y2);
	}
	ChunkIndex chunkIndex()
	{
		int32_t x2 = (x + (x < 0)) / CHUNK_SIZE;
		int32_t y2 = (y + (y < 0)) / CHUNK_SIZE;

		x2 -= x < 0;
		y2 -= y < 0;

		return ChunkIndex(x2, y2);
	}
};

GlobalPosition vec2GlobalPos(sf::Vector2f pos);