#ifndef MINECRAFT_CHUNKRULE_H
#define MINECRAFT_CHUNKRULE_H

#include "ChunkBase.h"

/*
 * Chunk block rules are boolean functions returning what block or structure should be placed in the chunk
 * based on his position and his height.
 * A chunk block rule should fit to this type std::function<bool(const Coordinates3D&, const int&)>
 * A chunk block rule returns -1 if the the assertion fails
 * A rule overrides the previous rule in the array

 * Chunk Structure rules are functions executing after the block rules
 */

using ChunkBlockRule = std::function<int(const Coordinates3D&, int)>;
using ChunkStructureRule = std::function<std::unordered_map<Key3D, Block>(const Coordinates3D&)>;

namespace ChunkRules
{
	constexpr int UndefinedBlock = -1;

	int PlaceGrass(const Coordinates3D &coords, int height);
	int PlaceDirt(const Coordinates3D &coords, int height);
	int PlaceStone(const Coordinates3D &coords, int height);

	std::unordered_map<Key3D, Block> PlaceTree(const Coordinates3D& coords);
}

#endif //MINECRAFT_CHUNKRULE_H
