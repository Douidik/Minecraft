#ifndef MINECRAFT_TREE_H
#define MINECRAFT_TREE_H

#include "world/chunk/ChunkBase.h"

class Tree
{
public:
	std::unordered_map<Key3D, Block> Create(const Coordinates3D &coords, int height, int leavesRadius);
};

#endif //MINECRAFT_TREE_H
