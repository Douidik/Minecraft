#ifndef MINECRAFT_CHUNKBASE_H
#define MINECRAFT_CHUNKBASE_H

#include "world/block/Block.h"
#include "maths/Maths.h"
#include "graphics/block/BlockMesh.h"

/* Globals */
constexpr int ChunkWidth = 32, ChunkHeight = 32, ChunkDepth = 32;

/* Defined Types */
using ChunkBlocks = Array3D<Block, ChunkWidth, ChunkHeight, ChunkDepth>;
using HeightMap = std::array<std::array<int, ChunkWidth>, ChunkDepth>;

enum ChunkSide { Front, Back, Right, Left, None };

/* Utility functions */
// Get absolute chunk coordinates in blocks

constexpr Coordinates3D AbsChunkCoords(const Coordinates3D &chunkCoords)
{
	Coordinates3D absCoords;
	absCoords.x = chunkCoords.x * ChunkWidth;
	absCoords.y = chunkCoords.y * ChunkHeight;
	absCoords.z = chunkCoords.z * ChunkDepth;

	return absCoords;
}

constexpr Coordinates3D AbsToLocalCoords(const Coordinates3D &absCoords)
{
	Coordinates3D localCoords;
	localCoords.x = absCoords.x % ChunkWidth;
	localCoords.y = absCoords.y % ChunkHeight;
	localCoords.z = absCoords.z % ChunkDepth;

	return localCoords;
}

constexpr Coordinates3D ConvertChunkCoords(const Coordinates3D &coords, const ChunkSide &neighbourSide)
{
	switch (neighbourSide)
	{
	case Front: return { coords.x, coords.y, coords.z - ChunkDepth};
	case Back:  return { coords.x, coords.y, ChunkDepth + coords.z };
	case Right: return { coords.x - ChunkWidth, coords.y, coords.z };
	case Left:  return { ChunkWidth + coords.x, coords.y, coords.z };
	case None:  MC_ERROR("Illegal chunk side used"); return { 0, 0, 0 };
	}
}

/* Returns what is the block facing chunk (relative to the parent chunk) */
constexpr ChunkSide BlockFaceToChunkSide(const BlockFace &face)
{
	switch(face)
	{
	case BlockFace::Front: return ChunkSide::Front;
	case BlockFace::Back:  return ChunkSide::Back;
	case BlockFace::Left:  return ChunkSide::Left;
	case BlockFace::Right: return ChunkSide::Right;
	default:               return ChunkSide::None; // chunks in the Y dimension are not currently supported
	}
}

/* Returns if coordinates are outside from the chunk */
constexpr bool IsInChunk(const Coordinates3D &coords)
{
	return (coords.x >= 0 && coords.x < ChunkWidth  &&
	        coords.y >= 0 && coords.y < ChunkHeight &&
	        coords.z >= 0 && coords.z < ChunkDepth);
}

static Coordinates3D GetChunkOfCoords(const Coordinates3D &absCoords)
{
	Coordinates3D chunkCoords;
	chunkCoords.x = std::trunc(absCoords.x / ChunkWidth);
	chunkCoords.y = 0;
	chunkCoords.z = std::trunc(absCoords.z / ChunkDepth);

	return chunkCoords;
}

#endif //MINECRAFT_CHUNKBASE_H
