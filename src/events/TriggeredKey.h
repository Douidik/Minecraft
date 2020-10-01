#ifndef MINECRAFT_TRIGGEREDKEY_H
#define MINECRAFT_TRIGGEREDKEY_H

class InputSystem;

class TriggeredKey
{
public:
	static Ref<TriggeredKey> Create(KeyCode code);

	TriggeredKey() = default;
	TriggeredKey(KeyCode code);
	bool IsTriggered(const InputSystem &inputSys);

private:
	bool m_IsAvailable;
	KeyCode m_Code;
};

#endif //MINECRAFT_TRIGGEREDKEY_H
