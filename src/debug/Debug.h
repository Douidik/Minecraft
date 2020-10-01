#ifndef MINECRAFT_DEBUG_H
#define MINECRAFT_DEBUG_H

struct DebugConfiguration
{
	KeyCode showFpsKey, toggleWireframeKey;
};

class TriggeredKey;

class Debug
{
public:
	static Ref<Debug> Create();

	Debug();
	void Update(class InputSystem &inputSys);

private:
	DebugConfiguration m_Configuration;
	Ref<TriggeredKey> m_ToggleWireframeKey;
	bool m_IsWireframeToggled;
};

#endif //MINECRAFT_DEBUG_H
