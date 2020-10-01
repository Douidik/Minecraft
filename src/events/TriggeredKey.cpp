#include "TriggeredKey.h"
#include "InputSystem.h"

Ref<TriggeredKey> TriggeredKey::Create(KeyCode code)
{
	return CreateRef<TriggeredKey>(code);
}

TriggeredKey::TriggeredKey(KeyCode code)
	: m_IsAvailable(false), m_Code(code)
{ }

bool TriggeredKey::IsTriggered(const InputSystem &inputSys)
{
	if(m_IsAvailable && inputSys.IsKeyPressed(m_Code))
	{
		m_IsAvailable = false;
		return true;
	}

	if(!m_IsAvailable && !inputSys.IsKeyPressed(m_Code))
	{
		m_IsAvailable = true;
	}

	return false;
}
