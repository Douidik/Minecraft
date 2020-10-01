#ifndef MINECRAFT_CONTEXT_H
#define MINECRAFT_CONTEXT_H

#include "events/InputSystem.h"

struct WindowConfiguration
{
	int width, height;
	std::string name;
	class Context *pContext;
	int msaa;
	bool vSync;
};

class Context
{
public:
	static void Initialize();
	static void Release();
	/* Returns if a context is running */
	static bool IsAvailable();

	void Create();
	void Destroy();

	void UpdateEvents();
	void UpdateWindow();
	bool IsRunning();

	inline InputSystem &Input()
	{
		return m_InputSys;
	}

private:
	void OpenWindow();
	void CloseWindow();

	void SetupEvents();

	WindowConfiguration m_WindowConfig;
	GLFWwindow *m_pGlfwWindow;
	InputSystem m_InputSys;
};

#endif //MINECRAFT_CONTEXT_H
