#include "ChunkSystem.h"

#include "ChunkGenerator.h"
#include "graphics/Renderer.h"
#include "core/Configuration.h"
#include "graphics/Texture.h"
#include "graphics/ShaderProgram.h"
#include "world/player/Player.h"
#include "maths/Random.h"

Ref<ChunkSystem> ChunkSystem::Create()
{
	return CreateRef<ChunkSystem>();
}

ChunkSystem::ChunkSystem()
	:m_PlayerChunk(0, 0, 0)
{
	// Reseeding the uniform number generator
	UniformRandom::ReseedUniform();

	m_Configuration.renderDistance = Configuration::Read<int>("Chunk.RenderDistance");
	m_Configuration.cachedDistance = Configuration::Read<int>("Chunk.CachedDistance");

	m_Generator = ChunkGenerator::Create();
	m_BlockRules = { ChunkRules::PlaceDirt, ChunkRules::PlaceGrass, ChunkRules::PlaceStone };
	m_StructureRules = { ChunkRules::PlaceTree };

	//temporary
	auto textureImage = Image::Create("res/textures/tilemap.png");
	m_TextureAtlas = Texture::Create(textureImage);

	m_ProcessingFunction = [this]()
	{
		m_Pipeline.Process(m_BlockRules, m_StructureRules, m_Generator);
		m_IsProcessingDone = true;
	};

	m_Pipeline.Load(m_Configuration.renderDistance, m_Configuration.cachedDistance, m_PlayerChunk);
	m_ProcessingThread = CreateRef<std::thread>(m_ProcessingFunction);
}

ChunkSystem::~ChunkSystem()
{
	if(m_ProcessingThread)
		m_ProcessingThread->join();
}

void ChunkSystem::Update(Ref<Player> player)
{
	/*
	 * We reload the chunks only when the player go out from his current chunk,
	 * To avoid non-necessary computing we allow the pipeline to be reloaded
	 * only if the current processing thread is not busy
	 */
	Coordinates3D currentPlayerChunk = GetChunkOfCoords(player->GetTransform()->position);

	if(m_PlayerChunk != currentPlayerChunk && !m_ProcessingThread)
	{
		m_PlayerChunk = currentPlayerChunk;
		m_Pipeline.Load(m_Configuration.renderDistance, m_Configuration.cachedDistance, m_PlayerChunk);
		m_Pipeline.Unload();
		m_ProcessingThread = CreateRef<std::thread>(m_ProcessingFunction);
	}

	if (m_IsProcessingDone)
	{
		m_ProcessingThread->join();
		m_Pipeline.Submit();
		m_ProcessingThread.reset();
		m_IsProcessingDone = false;
	}
}

void ChunkSystem::Draw(Ref<Renderer> renderer)
{
	//glEnable(GL_FOG);
	//GLfloat fogcolor[4] = { 0.5, 0.5, 0.5, 1 };
	//GLint fogmode = GL_EXP;
	//glFogi(GL_FOG_MODE, fogmode);
	//glFogfv(GL_FOG_COLOR, fogcolor);
	//glFogf(GL_FOG_DENSITY, 0.35);
	//glFogf(GL_FOG_START, 1.0);
	//glFogf(GL_FOG_END, 10.0);

	m_TextureAtlas->Bind();
	renderer->GetShader()->SetInteger("u_TextureAtlas", 0);
	m_Pipeline.Draw(renderer);

	//glDisable(GL_FOG);
}