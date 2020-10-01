#include "ChunkPipeline.h"
#include "Chunk.h"
#include "ChunkGenerator.h"
#include "util/Utility.h"

Ref<Chunk> ChunkQueue::operator[](const Key3D &coords)
{
	return Get(coords);
}

Ref<Chunk> ChunkQueue::Get(const Key3D &coords)
{
	std::unordered_map<Key3D, Ref<Chunk>>::iterator chunkFinder;

	/* Searching thought all queues */
	chunkFinder = processing.find(coords);
	if (chunkFinder != processing.end())
		return chunkFinder->second;

	chunkFinder = drawing.find(coords);
	if (chunkFinder != drawing.end())
		return chunkFinder->second;

	chunkFinder = validating.find(coords);
	if (chunkFinder != validating.end())
		return chunkFinder->second;

	// Chunk has not been found
	return nullptr;
}

std::unordered_map<ChunkSide, Ref<Chunk>> ChunkQueue::GetNeighbours(const Key3D &coords)
{
	const std::unordered_map<ChunkSide, Coordinates3D> neighbourCoords =
	{
		{ ChunkSide::Front, {coords.x, coords.y, coords.z+1} },
		{ ChunkSide::Back,  {coords.x, coords.y, coords.z-1} },
		{ ChunkSide::Right, {coords.x+1, coords.y, coords.z} },
		{ ChunkSide::Left,  {coords.x-1, coords.y, coords.z} }
	};

	std::unordered_map<ChunkSide, Ref<Chunk>> neighbourChunks;

	for(const auto &[side, coords] : neighbourCoords)
	{
		auto chunk = Get(coords);

		if(chunk != nullptr)
			neighbourChunks[side] = chunk;
	}

	return neighbourChunks;
}

std::unordered_map<Key3D, Ref<Chunk>> &ChunkQueue::GetQueueFromType(const ChunkQueueType &type)
{
	switch(type)
	{
	case ChunkQueueType::Processing: return processing;
	case ChunkQueueType::Drawing:    return drawing;
	case ChunkQueueType::Validating: return validating;
	}
}

void ChunkQueue::SetBlock(const Coordinates3D &absoluteCoords, Block block)
{
	/* Extracting the chunk and the block coords from the abs coords,
	 * The euclidean division returns a quotient and a reminder,
	 * the quotient will be the block coords, and the reminder will
	 * gives us the coordinates of the chunk.
	 */
	std::div_t divX = std::div(absoluteCoords.x, ChunkWidth),
			   divY = std::div(absoluteCoords.y, ChunkHeight),
			   divZ = std::div(absoluteCoords.z, ChunkDepth);

	Key3D chunkCoords { divX.quot, divY.quot, divZ.quot };

	Ref<Chunk> chunk = Get(chunkCoords);

	//if(chunk != nullptr)
	//{
	//	Key3D blockCoords { divX.rem, divY.rem, divZ.rem };
	//	MC_ASSERT(IsInChunk(blockCoords), "Block is not in chunk");

	//	chunk->SetBlock(blockCoords, block);
	//}
}

void ChunkPipeline::Draw(Ref<Renderer> renderer)
{
	for (const auto &[coords, chunk] : m_Queue.drawing)
	{
		chunk->Draw(renderer);
	}
}

void ChunkPipeline::Invalidate()
{
	m_Queue.validating.merge(m_Queue.drawing);
	m_Queue.drawing.clear();
}

void ChunkPipeline::Load(int renderDistance, int cachedDistance, const Coordinates3D &relativeTo)
{
	const auto shouldCacheChunk = [renderDistance](const Coordinates3D &coords) -> bool
	{
		return !(coords.x >= -renderDistance && coords.x <= renderDistance &&
		         coords.y >= -renderDistance && coords.y <= renderDistance &&
		         coords.z >= -renderDistance && coords.z <= renderDistance  );
	};


	Invalidate();
	int generationDistance = renderDistance + cachedDistance;
	Coordinates3D coords(0,0,0);

	for(coords.z = relativeTo.z - generationDistance; coords.z < relativeTo.z + generationDistance; coords.z++)
		for(coords.x = relativeTo.x - generationDistance; coords.x < relativeTo.x + generationDistance; coords.x++)
		{
			bool shouldCache = shouldCacheChunk(relativeTo - coords);

			Ref<Chunk> chunk = m_Queue[coords];

			if (!chunk)
			{
				m_Queue.processing[coords] = Chunk::Create(coords, shouldCache);
			}
			else if (chunk->IsCached() != shouldCache)
			{
				if (chunk->IsCached()) chunk->UnCache();
				else chunk->ReCache();
			}
			else
			{
				/* Moving all the chunks waiting for validation to the drawing queue */
				auto validatingChunkIterator = m_Queue.validating.find(coords);
				if (validatingChunkIterator != m_Queue.validating.end())
				{
					m_Queue.drawing.insert(m_Queue.validating.extract(validatingChunkIterator));
				}
			}
		}
}

void ChunkPipeline::Unload()
{
	m_Queue.validating.clear();
}

void ChunkPipeline::Submit()
{
	for (const auto &[coords, chunk] : m_Queue.processing)
	{
		if(chunk->IsCached()) continue;
		chunk->Submit();
	}

	/* Move processed chunks to the drawing queue */
	std::vector<std::unordered_map<Key3D, Ref<Chunk>>::iterator> movedChunks;
	for (auto it = m_Queue.processing.begin(); it != m_Queue.processing.end(); it++)
	{
		if (it->second->GetStatus() == ChunkStatus::ToDraw)
		{
			movedChunks.push_back(it);
			m_Queue.drawing.insert(*it);
		}
	}

	for (auto it : movedChunks)
		m_Queue.processing.erase(it);
}

/* Pipeline processing */

void ChunkPipeline::Process(const std::list<ChunkBlockRule> &blockRules,
							const std::list<ChunkStructureRule> &structureRules,
							Ref<ChunkGenerator> chunkGenerator)
{
	/* Generating */
	std::vector<std::future<void>> generatingFutures;

	for (const auto &[coords, chunk] : m_Queue.processing)
	{
		 generatingFutures.push_back(std::async(std::launch::async,
							         &ChunkPipeline::GenerateTerrain,
							         this,
							         chunk, blockRules, chunkGenerator));
	}

	// Joining generating threads
	for(auto &future : generatingFutures) future.get();

	/* Generating structures */
	for(const auto &[coords, chunk] : m_Queue.processing)
	{
		GenerateStructures(chunk, structureRules);
	}

	/* Building */
	std::vector<std::future<void>> buildingFutures;

	for (const auto &[coords, chunk] : m_Queue.processing)
	{
		 buildingFutures.push_back(std::async(std::launch::async,
							       &ChunkPipeline::Build,
							       this,
							       chunk));
	}

	// Joining building threads
	for (auto &future : buildingFutures) future.get();
}

void ChunkPipeline::GenerateTerrain(Ref<Chunk> chunk, const std::list<ChunkBlockRule> &blockRules, Ref<ChunkGenerator> chunkGenerator)
{
	if(chunk->GetStatus() != ChunkStatus::ToGenTerrain) return;

	auto perlinMap = chunkGenerator->CreatePerlinMap(chunk->GetCoords());
	chunk->GenerateTerrain(perlinMap, blockRules);
}

void ChunkPipeline::GenerateStructures(Ref<Chunk> chunk, const std::list<ChunkStructureRule> &structureRules)
{
	if (chunk->GetStatus() != ChunkStatus::ToGenStructures) return;

	chunk->GenerateStructures(structureRules, m_Queue);
}

void ChunkPipeline::Build(Ref<Chunk> chunk)
{
	if (chunk->IsCached()) return;

	auto neighbours = m_Queue.GetNeighbours(chunk->GetCoords());
	chunk->Build(neighbours);
}