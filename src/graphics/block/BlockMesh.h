#ifndef MINECRAFT_BLOCKMESH_H
#define MINECRAFT_BLOCKMESH_H

#include "maths/Maths.h"
#include "graphics/Drawable.h"

enum class BlockFace : int
{
	Front = 0,
	Right = 1,
	Back = 2,
	Left = 3,
	Bottom = 4,
	Top = 5
};

struct BlockFaceVertex
{
	BlockFaceVertex(float _x, float _y, float _z, int _index, int _textureIndex = 0)
		: position({ _x, _y, _z }), index(_index), textureIndex(_textureIndex)
	{}

	BlockFaceVertex() = default;

	Vector3 position;
	int index, textureIndex;
};

struct BlockData : DrawableData<BlockFaceVertex, unsigned int>
{ };

void AddBlockFaces(BlockData &data, Key3D position, int id, size_t &indexOffset, std::vector<BlockFace> faces);


#endif //MINECRAFT_BLOCKMESH_H
