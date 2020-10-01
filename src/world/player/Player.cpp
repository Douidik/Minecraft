#include "Player.h"
#include "core/Configuration.h"

Ref<Player> Player::Create()
{
	return CreateRef<Player>();
}

Player::Player()
{
	/* Loading configuration */
	m_Configuration.forwardKey  = Configuration::Read<KeyCode>("Controls.ForwardKey");
	m_Configuration.backwardKey = Configuration::Read<KeyCode>("Controls.BackwardKey");
	m_Configuration.rightKey	= Configuration::Read<KeyCode>("Controls.RightKey");
	m_Configuration.leftKey		= Configuration::Read<KeyCode>("Controls.LeftKey");
	m_Configuration.jumpKey	 	= Configuration::Read<KeyCode>("Controls.JumpKey");
	m_Configuration.crouchKey	= Configuration::Read<KeyCode>("Controls.CrouchKey");

	m_Configuration.speed = Configuration::Read<float>("Controls.Speed");
	m_Configuration.sensitivity = Configuration::Read<float>("Controls.Sensitivity");

	/* Creating the player camera */
	m_Camera = Camera::Create();
	// The camera transformation will be set to the player transformation (basically the camera follows the player)
	m_Transform = Transform::Create();
	m_Camera->SetTransform(m_Transform);
}

void Player::Update(InputSystem &inputSys, float dt)
{
	Move(inputSys, dt);
	Look(inputSys, dt);
}

void Player::Move(InputSystem &inputSys, float dt)
{
	glm::vec3 _delta(0.0f);

	/* Polling the keys and calculating the delta movement */
	if(inputSys.IsKeyPressed(m_Configuration.forwardKey))
	{
		_delta.x -= glm::cos(glm::radians( m_Transform->rotation.y + 90 ));
		_delta.z -= glm::sin(glm::radians( m_Transform->rotation.y + 90 ));
	}
	if(inputSys.IsKeyPressed(m_Configuration.backwardKey))
	{
		_delta.x += glm::cos(glm::radians( m_Transform->rotation.y + 90 ));
		_delta.z += glm::sin(glm::radians( m_Transform->rotation.y + 90 ));
	}
	if(inputSys.IsKeyPressed(m_Configuration.rightKey))
	{
		_delta.x += glm::cos(glm::radians( m_Transform->rotation.y ));
		_delta.z += glm::sin(glm::radians( m_Transform->rotation.y ));
	}
	if(inputSys.IsKeyPressed(m_Configuration.leftKey))
	{
		_delta.x -= glm::cos(glm::radians( m_Transform->rotation.y ));
		_delta.z -= glm::sin(glm::radians( m_Transform->rotation.y ));
	}

	if(inputSys.IsKeyPressed(m_Configuration.jumpKey))
	{
		_delta.y += 1;
	}
	if(inputSys.IsKeyPressed(m_Configuration.crouchKey))
	{
		_delta.y -= 1;
	}

	Vector3 delta = _delta;
	/* Normalizing the delta movement if the movement is not null */
	if(delta != Vector3(0.0))
	{
		float length = glm::sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
		delta /= length;
	}

	m_Transform->position += delta * m_Configuration.speed * dt;
}

void Player::Look(InputSystem &inputSys, float dt)
{
	CursorPosition _delta = inputSys.GetCursorDelta();
	glm::vec3 delta = { _delta.y, _delta.x, 0.0f };

	m_Transform->rotation += delta * m_Configuration.sensitivity * dt;

	/* Clamping rotation values, TODO: serialize values */
	// We block the X rotation values between -80 and 80 degrees
	m_Transform->rotation.x = std::clamp(m_Transform->rotation.x, -80.0f, 80.0f);
	// We clamp the Y rotation values between 0 and 360  degrees and if the values are exits the boundaries
	// we reset the values to the highest or the lowest value
	if(m_Transform->rotation.y > 360.0f)
	{
		m_Transform->rotation.y = 0.0f;
	}
	else if(m_Transform->rotation.y < 0.0f)
	{
		m_Transform->rotation.y = 360.0f;
	}
}
