#include "ChunkRule.h"
#include "maths/Random.h"
#include "core/Configuration.h"
#include "world/structures/Tree.h"

namespace ChunkRules
{
	/* TODO: serialize rule constants and find blocks id based by name */

	int PlaceGrass(const Coordinates3D &coords, int height)
	{
		if(coords.y == height) // Is the block in top ?
			return 1;
		else
			return UndefinedBlock;
	}

	int PlaceDirt(const Coordinates3D &coords, int height)
	{
		// Is the height value between top - 1 and top - 4
		if(coords.y >= height - 4 && coords.y <= height - 1)
			return 2;
		else
			return UndefinedBlock;
	}

	int PlaceStone(const Coordinates3D &coords, int height)
	{
		int randomHeight = -(Random::GetValue(5, 7));

		if(coords.y <= height - randomHeight)
			return 3;
		else
			return UndefinedBlock;
	}

	std::unordered_map<Key3D, Block> PlaceTree(const Coordinates3D& coords)
	{
		int random = UniformRandom::GetValue(0, pow(Configuration::Read<int>("Chunk.TreeDensity"), 2));

		if(random == 1) // 1 tree every (density) blocks
		{
			Tree tree;
			int treeHeight = Random::GetValue(4, 7);
			return tree.Create(coords, treeHeight + 1, std::max(4, ((treeHeight + 1) / 2) & ~1));
		}
		else
			return {};
	}

}
