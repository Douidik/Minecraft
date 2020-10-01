#include "World.h"
#include "WorldCore.h"
#include "chunk/ChunkSystem.h"

void World::Create()
{
	WorldCore::Initialize();
	m_Player = Player::Create();
	m_ChunkSystem = ChunkSystem::Create();
}

void World::Update(class InputSystem &inputSystem, float dt)
{
	m_ChunkSystem->Update(m_Player);
	m_Player->Update(inputSystem, dt);
}

void World::Draw(Ref<Renderer> renderer)
{
	m_ChunkSystem->Draw(renderer);
}
