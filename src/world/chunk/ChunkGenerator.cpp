#include "ChunkGenerator.h"
#include "core/Configuration.h"

Ref<ChunkGenerator> ChunkGenerator::Create()
{
	return CreateRef<ChunkGenerator>();
}

ChunkGenerator::ChunkGenerator()
{
	m_Configuration.perlinOffset  = Configuration::Read<float>("Chunk.Generation.PerlinOffset");
	m_Configuration.perlinFactor  = Configuration::Read<float>("Chunk.Generation.PerlinFactor");
}

const HeightMap &&ChunkGenerator::CreatePerlinMap(const Coordinates3D &chunkCoords)
{
	HeightMap perlinMap;

	PerlinParameters perlinParameters = {
		{0.0, 0.0},
		m_Configuration.perlinFactor,
		m_Configuration.perlinOffset
	};

	/* To avoid avoidable repeated type casting, the coordinates axis are not integers anymore */
	DoubleVector3 absoluteChunkCoords = AbsChunkCoords(chunkCoords);

	for(double z = 0; z < ChunkDepth; z++)
		for(double  x = 0; x < ChunkWidth; x++)
		{
			/* Generating perlin noise */
			perlinParameters.position.x = (absoluteChunkCoords.x + x) / ChunkWidth;
			perlinParameters.position.y = (absoluteChunkCoords.z + z) / ChunkDepth;

			float height = std::clamp<int>(PerlinNoise::GetValue(perlinParameters), 0, ChunkHeight);
			perlinMap[x][z] = height;
		}

	return std::move(perlinMap);
}