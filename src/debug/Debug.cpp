#include "mc.pch"
#include "Debug.h"
#include "core/Configuration.h"
#include "events/InputSystem.h"
#include "events/TriggeredKey.h"

Ref<Debug> Debug::Create()
{
	return CreateRef<Debug>();
}

Debug::Debug()
	: m_IsWireframeToggled(false)
{
	m_Configuration.showFpsKey = Configuration::Read<KeyCode>("Controls.Debug.ShowFpsKey");
	m_Configuration.toggleWireframeKey = Configuration::Read<KeyCode>("Controls.Debug.ToggleWireframeKey");
	m_ToggleWireframeKey = TriggeredKey::Create(m_Configuration.toggleWireframeKey);
}

void Debug::Update(class InputSystem &inputSys)
{
#ifdef MC_DEBUG
	if(m_ToggleWireframeKey->IsTriggered(inputSys)) // We set the wireframe mode once
	{
		if(!m_IsWireframeToggled)
		{
			m_IsWireframeToggled = true;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			m_IsWireframeToggled = false;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

#endif
}