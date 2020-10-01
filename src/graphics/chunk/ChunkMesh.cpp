#include "ChunkMesh.h"
#include "world/chunk/Chunk.h"

Ref<ChunkMesh> ChunkMesh::Create()
{
	return CreateRef<ChunkMesh>();
}

ChunkMesh::ChunkMesh()
	: Drawable(ChunkMeshVertexLayout, GL_UNSIGNED_INT, GL_STATIC_DRAW)
{ }

void ChunkMesh::Build(ChunkBlocks &chunkBlocks, std::unordered_map<ChunkSide, Ref<Chunk>> &neighbours)
{
	size_t indexOffset = 0;

	/* For each block in the chunk */
	for(int z = 0; z < ChunkDepth; z++)
		for(int y = 0; y < ChunkHeight; y++)
			for (int x = 0; x < ChunkWidth; x++)
			{
				const Block &block = chunkBlocks[x][y][z];
				// Skipping void blocks
				if (block.id == BlockVoidID) continue;

				auto renderedFaces = GetRenderedFaces(block, neighbours, chunkBlocks, x, y, z);
				AddBlockFaces(m_Data, { x, y, z }, block.id, indexOffset, renderedFaces);
			}
}

std::vector<BlockFace> ChunkMesh::GetRenderedFaces(const Block &block,
												   std::unordered_map<ChunkSide, Ref<Chunk>> &neighbours,
												   const ChunkBlocks &chunkBlocks,
												   int x, int y, int z)
{
	std::vector<BlockFace> faces;

	/* Map indicating which face is in contact with which block (in coordinates) */
	const auto GetFacesNeighbours = [x,y,z]()
	{
		return std::unordered_map<BlockFace, Key3D>
		{
			{BlockFace::Left,   {x - 1, y, z}},
			{BlockFace::Right,  {x + 1, y, z}},
			{BlockFace::Top,    {x, y + 1, z}},
			{BlockFace::Bottom, {x, y - 1, z}},
			{BlockFace::Back,   {x, y, z - 1}},
			{BlockFace::Front,  {x, y, z + 1}}
		};
	};

	const auto neighbouringFaces = GetFacesNeighbours();

	for(const auto &[face, coords] : neighbouringFaces)
	{
		bool shouldRenderFace = false;

		/* Check if the coordinates are outside the chunk */
		if(!IsInChunk(coords))
		{
			ChunkSide neighbourSide = BlockFaceToChunkSide(face);
			Ref<Chunk> neighbourChunk = neighbours[neighbourSide];
			if(neighbourChunk != nullptr) // Is neighbouring chunk loaded ?
			{
				// Get the coordinates in the neighbour space
				Coordinates3D neighbourBlockCoords = ConvertChunkCoords(coords, neighbourSide);
				MC_ASSERT(IsInChunk(neighbourBlockCoords), "Non-valid neighbour block coords");
				if(neighbourChunk->GetBlock(neighbourBlockCoords).id == BlockVoidID)
					shouldRenderFace = true;
			}
		}
		else
		{
			if(chunkBlocks[coords.x][coords.y][coords.z].id == BlockVoidID)
				shouldRenderFace = true;
		}

		if(shouldRenderFace) // The face's neighbour block is void ?
		{
			faces.push_back(face); // The face will be rendered
			continue;
		}
	}

	return faces;
}

void ChunkMesh::Submit()
{
	if(!m_Data.vertices.empty())
		Drawable::Submit(m_Data);
}
