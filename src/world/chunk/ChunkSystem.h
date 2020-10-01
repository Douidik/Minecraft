#ifndef MINECRAFT_CHUNKSYSTEM_H
#define MINECRAFT_CHUNKSYSTEM_H

#include "ChunkBase.h"
#include "ChunkRule.h"
#include "Chunk.h"
#include "ChunkPipeline.h"

class Player;
class ChunkGenerator;
class Renderer;

struct ChunkSystemConfiguration
{
	int renderDistance, cachedDistance;
};

class ChunkSystem
{
public:
	static Ref<ChunkSystem> Create();
	ChunkSystem();
	~ChunkSystem();
	void Update(Ref<Player> player);
	void Draw(Ref<Renderer> renderer);

private:
	/* Todo: refactor this to have rules per biome, for now it's just default rules */
	std::list<ChunkBlockRule> m_BlockRules;
	std::list<ChunkStructureRule> m_StructureRules;

	Coordinates3D m_PlayerChunk;
	ChunkPipeline m_Pipeline;
	Ref<ChunkGenerator> m_Generator;

	Ref<std::thread> m_ProcessingThread;
	std::atomic<bool> m_IsProcessingDone;

	Ref<class Texture> m_TextureAtlas;
	ChunkSystemConfiguration m_Configuration;

private:
	std::function<void()> m_ProcessingFunction;
};

#endif //MINECRAFT_CHUNKSYSTEM_H
