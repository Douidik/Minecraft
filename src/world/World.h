#ifndef MINECRAFT_WORLD_H
#define MINECRAFT_WORLD_H

#include "player/Player.h"

class Renderer;
class ChunkSystem;

class World
{
public:
	void Create();

	void Update(class InputSystem &inputSystem, float dt);
	void Draw(Ref<Renderer> renderer);

	inline Ref<Player> GetPlayer()
	{
		return m_Player;
	}

private:

	Ref<Player> m_Player;
	Ref<ChunkSystem> m_ChunkSystem;
};

#endif //MINECRAFT_WORLD_H
