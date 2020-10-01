#ifndef MINECRAFT_CHUNKMESH_H
#define MINECRAFT_CHUNKMESH_H

#include "graphics/Drawable.h"
#include "graphics/block/BlockMesh.h"
#include "world/chunk/ChunkBase.h"

static Layout ChunkMeshVertexLayout = {{ 0, 3, GL_FLOAT }, { 1, 1, GL_INT }, { 2, 1, GL_INT }};

class Chunk;

class ChunkMesh : public Drawable
{
public:
	static Ref<ChunkMesh> Create();
	ChunkMesh();
	void Build(ChunkBlocks &chunkBlocks, std::unordered_map<ChunkSide, Ref<Chunk>> &neighbours);
	void Submit();

private:
	std::vector<BlockFace> GetRenderedFaces(const Block &block,
											std::unordered_map<ChunkSide, Ref<Chunk>> &neighbours,
											const ChunkBlocks &chunkBlocks,
											int x, int y, int z);

	BlockData m_Data;
};

#endif //MINECRAFT_CHUNKMESH_H
