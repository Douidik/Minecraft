
#include "InputSystem.h"
#include "core/Context.h"

InputSystem::InputSystem(GLFWwindow *pGlfwWindow)
	: m_LastCursorPosition({0.0, 0.0})
{
	/* Resizing the key and mouse map */
	m_Keys.resize((size_t)KeyCode::Count);
	m_Buttons.resize((size_t)ButtonCode::Count);

	//glfwSetInputMode(pGlfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

#define GET_THIS_THROUGH_WINDOW(pGlfwWindow) static_cast<WindowConfiguration*>(glfwGetWindowUserPointer(pGlfwWindow))->pContext->Input()

	glfwSetMouseButtonCallback(pGlfwWindow, [](GLFWwindow* pGlfwWindow, int code, int type, int modifiers)
	{
		InputSystem &_this = GET_THIS_THROUGH_WINDOW(pGlfwWindow);

		if(type == GLFW_PRESS)
		{
			_this.m_Buttons[code] = ButtonPressed(code);
		}
		else if(type == GLFW_RELEASE)
		{
			_this.m_Buttons[code] = ButtonReleased(code);
		}
		else
		{
			_this.m_Buttons[code] = ButtonInput(code, ButtonInputType::None);
		}
	});

	glfwSetKeyCallback(pGlfwWindow, [](GLFWwindow* pGlfwWindow, int code, int scancode, int type, int modifiers)
	{
		InputSystem &_this = GET_THIS_THROUGH_WINDOW(pGlfwWindow);

		if(type == GLFW_PRESS)
		{
			_this.m_Keys[code] = KeyPressed(code);
		}
		else if(type == GLFW_RELEASE)
		{
			_this.m_Keys[code] = KeyReleased(code);
		}
		else if(type == GLFW_REPEAT)
		{
			_this.m_Keys[code] = KeyRepeated(code);
		}
		else
		{
			_this.m_Keys[code] = KeyInput(code, KeyInputType::None);
		}
	});

#undef GET_THIS_THROUGH_WINDOW
}

CursorPosition InputSystem::GetCursorPosition() const
{
	// TODO: Refactor, this to be per linked window and not per bound context with window callbacks
	CursorPosition position;
	glfwGetCursorPos(glfwGetCurrentContext(), &position.x, &position.y);
	return position;
}

bool InputSystem::IsKeyPressed(KeyCode code) const
{
	return m_Keys[(size_t)code].type == KeyInputType::Pressed || m_Keys[(size_t)code].type == KeyInputType::Repeated;
}

bool InputSystem::IsKeyRepeated(KeyCode code) const
{
	return m_Keys[(size_t)code].type == KeyInputType::Repeated;
}

bool InputSystem::IsMousePressed(ButtonCode code) const
{
	return m_Buttons[(size_t)code].type == ButtonInputType::Pressed;

}

void InputSystem::Update()
{
	/* Computing cursor delta */
	m_CursorPosition = GetCursorPosition();
	m_CursorDelta = m_CursorPosition - m_LastCursorPosition;
	m_LastCursorPosition = m_CursorPosition;
}

CursorPosition InputSystem::GetCursorDelta() const
{
	return m_CursorDelta;
}