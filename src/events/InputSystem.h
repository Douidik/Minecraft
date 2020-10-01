#ifndef MINECRAFT_INPUTSYSTEM_H
#define MINECRAFT_INPUTSYSTEM_H

#include "ButtonInput.h"
#include "KeyInput.h"

struct CursorPosition
{
	double x, y;

	friend CursorPosition operator-(const CursorPosition &lhs, const CursorPosition &rhs)
	{
		return {lhs.x - rhs.x, lhs.y - rhs.y};
	}
	friend CursorPosition operator+(const CursorPosition &lhs, const CursorPosition &rhs)
	{
		return {lhs.x + rhs.x, lhs.y + rhs.y};
	}
};

class InputSystem
{
public:
	InputSystem() = default;
	InputSystem(GLFWwindow *pGlfwWindow);

	void Update();

	bool IsKeyPressed(KeyCode code) const;
	bool IsKeyRepeated(KeyCode code) const;
	bool IsMousePressed(ButtonCode code) const;
	CursorPosition GetCursorPosition() const;
	// Position differential of the current and the last cursor between the frames
	CursorPosition GetCursorDelta() const;

private:
	std::vector<KeyInput> m_Keys;
	std::vector<ButtonInput> m_Buttons;

	// TODO: check position by window and not by GLFW global context, this will be unused
	CursorPosition m_CursorPosition, m_LastCursorPosition, m_CursorDelta;
};

#endif //MINECRAFT_INPUTSYSTEM_H
