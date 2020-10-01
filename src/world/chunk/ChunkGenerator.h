#ifndef MINECRAFT_CHUNKGENERATOR_H
#define MINECRAFT_CHUNKGENERATOR_H

#include "ChunkBase.h"
#include "maths/PerlinNoise.h"
#include "ChunkRule.h"

struct ChunkGeneratorConfiguration
{
	float perlinFactor, perlinOffset;
};

class ChunkGenerator
{
public:
	static Ref<ChunkGenerator> Create();
	ChunkGenerator();
	const HeightMap &&CreatePerlinMap(const Coordinates3D &chunkCoords);

private:
	ChunkGeneratorConfiguration m_Configuration;
};

#endif //MINECRAFT_CHUNKGENERATOR_H
