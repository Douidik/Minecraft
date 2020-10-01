#ifndef MINECRAFT_PLAYER_H
#define MINECRAFT_PLAYER_H

#include "maths/Maths.h"
#include "graphics/Camera.h"
#include "events/InputSystem.h"

struct PlayerConfiguration
{
	KeyCode forwardKey, backwardKey, leftKey, rightKey, jumpKey, crouchKey;
	float sensitivity, speed;
};

class Player
{
public:
	static Ref<Player> Create();
	Player();
	void Update(InputSystem &inputSys, float dt);

	inline Ref<Camera> GetCamera() const
	{
		return m_Camera;
	}

	inline Ref<Transform> GetTransform() const
	{
		return m_Transform;
	}

private:
	void Move(InputSystem &inputSys, float dt);
	void Look(InputSystem &inputSys, float dt);

	Ref<Camera> m_Camera;
	Ref<Transform> m_Transform;
	PlayerConfiguration m_Configuration;
};

#endif //MINECRAFT_PLAYER_H
