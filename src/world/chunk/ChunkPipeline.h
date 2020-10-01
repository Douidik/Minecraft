#ifndef MINECRAFT_CHUNKPIPELINE_H
#define MINECRAFT_CHUNKPIPELINE_H

#include "ChunkBase.h"
#include "ChunkRule.h"

class Chunk;
class ChunkGenerator;

enum class ChunkQueueType
{
	Processing, Drawing, Validating
};

struct ChunkQueue
{
	Ref<Chunk> operator[](const Key3D &coords);
	Ref<Chunk> Get(const Key3D &coords);

	std::unordered_map<Key3D, Ref<Chunk>> processing, drawing, validating;
	std::unordered_map<ChunkSide, Ref<Chunk>> GetNeighbours(const Key3D &coords);
	std::unordered_map<Key3D, Ref<Chunk>> &GetQueueFromType(const ChunkQueueType &type);

	void SetBlock(const Coordinates3D &absoluteCoords, Block block);
};

class ChunkPipeline
{
public:
	void Draw(Ref<Renderer> renderer);
	void Load(int renderDistance, int cachedDistance, const Coordinates3D &relativeTo);
	void Unload();
	void Process(const std::list<ChunkBlockRule> &blockRules,
				 const std::list<ChunkStructureRule> &structureRules,
				 Ref<ChunkGenerator> chunkGenerator);
	void Submit();

private:
	/* Pipeline processing */
	void GenerateTerrain(Ref<Chunk> chunk, const std::list<ChunkBlockRule> &blockRules, Ref<ChunkGenerator> chunkGenerator);
	void GenerateStructures(Ref<Chunk> chunk, const std::list<ChunkStructureRule> &structureRules);
	void Build(Ref<Chunk> chunk);

	void Invalidate();

	ChunkQueue m_Queue;
};

#endif //MINECRAFT_CHUNKPIPELINE_H
