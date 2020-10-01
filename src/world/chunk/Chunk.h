#ifndef MINECRAFT_CHUNK_H
#define MINECRAFT_CHUNK_H

#include "ChunkBase.h"
#include "graphics/chunk/ChunkMesh.h"
#include "ChunkRule.h"

class ChunkQueue;

enum ChunkStatus
{
	ToGenTerrain,
	ToGenStructures,
	ToBuild,
	ToSubmit,
	ToDraw
};

class Chunk
{
public:
	static Ref<Chunk> Create(const Coordinates3D &coords, bool isCached);
	Chunk(const Coordinates3D &coords, bool isCached);

	/* Creation Pipeline */
	// Generate the chunk from the perlin and using the defined rules, this functions returns block generated outside from the chunk
	void GenerateTerrain(const HeightMap &heightMap, const std::list<ChunkBlockRule> &blockRules);
	void GenerateStructures(const std::list<ChunkStructureRule> &structureRules, ChunkQueue &queue);
	void Build(std::unordered_map<ChunkSide, Ref<Chunk>> &neighbours);
	void Submit();
	void Draw(Ref<Renderer> renderer);

	const Block &GetBlock(const Coordinates3D &coords) const;
	void SetBlock(const Coordinates3D &coords, const Block& block);
	const Coordinates3D &GetCoords() const;
	ChunkStatus &GetStatus();

	inline bool IsCached() const { return m_IsCached; }
	/* Re-cache a processed chunk */
	void ReCache();
	/* Continue the processing of a cached chunk */
	void UnCache();

private:
	bool m_IsCached;
	Ref<ChunkMesh> m_Mesh;
	ChunkBlocks m_Blocks;
	Coordinates3D m_Coords;
	ChunkStatus m_Status;
	HeightMap m_HeightMap;
};

#endif //MINECRAFT_CHUNK_H
