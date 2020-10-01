#include "Chunk.h"
#include "maths/Random.h"
#include "ChunkPipeline.h"

Ref<Chunk> Chunk::Create(const Coordinates3D &coords, bool isCached)
{
	return CreateRef<Chunk>(coords, isCached);
}

Chunk::Chunk(const Coordinates3D &coords, bool isCached)
	: m_Coords(coords), m_Status(ChunkStatus::ToGenTerrain), m_IsCached(isCached)
{
	m_Mesh = ChunkMesh::Create();
}

void Chunk::GenerateTerrain(const HeightMap &heightMap, const std::list<ChunkBlockRule> &blockRules)
{
	MC_ASSERT(m_Status == ChunkStatus::ToGenTerrain, "Wrong chunk pipeline order on generate");

	m_HeightMap = heightMap;

	for(int z = 0; z < ChunkDepth; z++)
		for(int y = 0; y < ChunkDepth; y++)
			for(int x = 0; x < ChunkDepth; x++)
			{
				int height = m_HeightMap[x][z];
				// If the block is above the height map we skip it -> void block
				if(y > height) continue;

				Coordinates3D blockCoords = { x, y, z };

				/* Placing blocks */
				int id = 0;
				for(const auto &rule : blockRules)
				{
					id = rule(blockCoords, height);
					if(id != ChunkRules::UndefinedBlock) break; // If the rules defines a valid block for the coords
				}

				MC_ASSERT(id != ChunkRules::UndefinedBlock, "Block rules does not provides a value for block at coordinates: {}x, {}y, {}z", x, y, z);
				m_Blocks[x][y][z] = Block(id);
			}

	m_Status = ChunkStatus::ToGenStructures;
}

void Chunk::GenerateStructures(const std::list<ChunkStructureRule> &structureRules, ChunkQueue &queue)
{
	MC_ASSERT(m_Status == ChunkStatus::ToGenStructures, "Wrong chunk pipeline order on build");

	std::unordered_map<Key3D, Block> structures;

	for (int z = 0; z < ChunkDepth; z++)
		for (int x = 0; x < ChunkWidth; x++)
		{
			int height = m_HeightMap[x][z];

			for(const auto &rule : structureRules)
			{
				std::unordered_map<Key3D, Block> structure = rule({x, height, z});
				structures.merge(structure);
			}
		}

	for(const auto &[coords, block] : structures)
	{
		if(IsInChunk(coords))
		{
			m_Blocks[coords.x][coords.y][coords.z] = block;
		}
		else
		{
			Coordinates3D absoluteCoords = (m_Coords*ChunkWidth) + coords;
			queue.SetBlock(absoluteCoords, block);
		}
	}

	m_Status = ChunkStatus::ToBuild;
}


void Chunk::Build(std::unordered_map<ChunkSide, Ref<Chunk>> &neighbours)
{
	MC_ASSERT(m_Status == ChunkStatus::ToBuild, "Wrong chunk pipeline order on build");

	m_Mesh->GetTransform()->position.x = m_Coords.x * ChunkWidth;
	m_Mesh->GetTransform()->position.y = m_Coords.y * ChunkHeight;
	m_Mesh->GetTransform()->position.z = m_Coords.z * ChunkDepth;

	m_Mesh->Build(m_Blocks, neighbours);

	m_Status = ChunkStatus::ToSubmit;
}

void Chunk::Submit()
{
	MC_ASSERT(m_Status == ChunkStatus::ToSubmit, "Wrong chunk pipeline order on submit");

	m_Mesh->Submit();

	m_Status = ChunkStatus::ToDraw;
}

void Chunk::Draw(Ref<Renderer> renderer)
{
	MC_ASSERT(m_Status == ChunkStatus::ToDraw, "Wrong chunk pipeline order on draw");

	renderer->Draw(m_Mesh->GetRenderRequest());
}


const Block &Chunk::GetBlock(const Coordinates3D &coords) const
{
	return m_Blocks[coords.x][coords.y][coords.z];
}

void Chunk::SetBlock(const Coordinates3D &coords, const Block &block)
{
	m_Blocks[coords.x][coords.y][coords.z] = block;
}

const Coordinates3D &Chunk::GetCoords() const
{
	return m_Coords;
}

ChunkStatus &Chunk::GetStatus()
{
	return m_Status;
}


void Chunk::ReCache()
{
	MC_ASSERT(!m_IsCached, "Chunk is already cached");
	m_IsCached = true;
	/* Resetting the chunk mesh */
	m_Mesh.reset();
	m_Mesh = ChunkMesh::Create();
	m_Status = ChunkStatus::ToBuild;
}

void Chunk::UnCache()
{
	MC_ASSERT(m_IsCached, "Chunk is not cached");
	m_IsCached = false;
}
