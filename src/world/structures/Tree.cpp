#include "Tree.h"

std::unordered_map<Key3D, Block> Tree::Create(const Coordinates3D &coords, int height, int leavesRadius)
{
	std::unordered_map<Key3D, Block> blocks;

	/* Generating the tree trunk */
	for(int h = 0; h < height; h++)
	{
		Key3D blockPosition = { coords.x, coords.y + h, coords.z };
		blocks[blockPosition] = 4;
	}

	/* Generating the tree leaves */
	int halfLeavesRadius = floor(leavesRadius / 2);
	for(int z = -halfLeavesRadius; z < halfLeavesRadius; z++)
		for(int y = -halfLeavesRadius; y < halfLeavesRadius; y++)
			for(int x = -halfLeavesRadius; x < halfLeavesRadius; x++)
			{
				blocks[{ coords.x + x, coords.y + height + y, coords.z + z }] = 5;
			}

	return blocks;
}
