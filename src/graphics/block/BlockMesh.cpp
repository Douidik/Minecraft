#include "mc.pch"
#include "BlockMesh.h"
#include "util/Utility.h"
#include "world/block/BlockDatabase.h"

static std::map<const BlockFace, std::array<BlockFaceVertex, 4>> FaceVertices =
{
	{ BlockFace::Front,
	  { BlockFaceVertex(1, 1, 1, 0), BlockFaceVertex(0, 1, 1, 1), BlockFaceVertex(0, 0, 1, 3), BlockFaceVertex(1, 0, 1, 2) }},
	{ BlockFace::Left,
	  { BlockFaceVertex(0, 1, 1, 0), BlockFaceVertex(0, 1, 0, 1), BlockFaceVertex(0, 0, 0, 3), BlockFaceVertex(0, 0, 1, 2) }},
	{ BlockFace::Back,
	  { BlockFaceVertex(0, 1, 0, 0), BlockFaceVertex(1, 1, 0, 1), BlockFaceVertex(1, 0, 0, 3), BlockFaceVertex(0, 0, 0, 2) }},
	{ BlockFace::Right,
	  { BlockFaceVertex(1, 1, 0, 0), BlockFaceVertex(1, 1, 1, 1), BlockFaceVertex(1, 0, 1, 3), BlockFaceVertex(1, 0, 0, 2) }},
	{ BlockFace::Top,
	  { BlockFaceVertex(1, 1, 0, 0), BlockFaceVertex(0, 1, 0, 1), BlockFaceVertex(0, 1, 1, 3), BlockFaceVertex(1, 1, 1, 2) }},
	{ BlockFace::Bottom,
	  { BlockFaceVertex(0, 0, 0, 0), BlockFaceVertex(1, 0, 0, 1), BlockFaceVertex(1, 0, 1, 3), BlockFaceVertex(0, 0, 1, 2) }}
};

constexpr std::array<unsigned int, 6> FaceIndices =
{
	0, 1, 2,
	2, 3, 0
};

void AddBlockFaces(BlockData &data, Key3D position, int id, size_t &indexOffset, std::vector<BlockFace> faces)
{
	for (unsigned int faceIndex = 0; faceIndex < faces.size(); faceIndex++)
	{
		const BlockFace face = faces[faceIndex];

		/* Parsing vertices */
		auto &&faceVertices = FaceVertices[face];
		// copying vertices, apply transformation and find the texture index
		std::transform(faceVertices.begin(), faceVertices.end(), std::back_inserter(data.vertices),
		[id, position, face, faceIndex](BlockFaceVertex vertex)
		{
			vertex.position += static_cast<Vector3>(position);
			vertex.textureIndex = BlockDatabase::GetTextureID(id, face);
			return vertex;
		});

		/* Parsing Indices */
		std::array<unsigned int, 6> _indices = FaceIndices;
		for (unsigned int &_index : _indices)
		{
			_index += indexOffset;
		}
		data.indices.insert(data.indices.end(), _indices.begin(), _indices.end());

		indexOffset += 4;
	}
}