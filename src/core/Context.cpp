#include "Context.h"
#include "Configuration.h"

void Context::Initialize()
{
	MC_ASSERT(glfwInit(), "Failed to initialize GLFW");
}

void Context::Release()
{
	glfwTerminate();
}

bool Context::IsAvailable()
{
	return (glfwGetCurrentContext() != nullptr);
}

void Context::Create()
{
	OpenWindow();
	SetupEvents();
}

void Context::Destroy()
{
	CloseWindow();
}

void Context::OpenWindow()
{
	/* Configuring the window */
	m_WindowConfig.name = Configuration::Read<std::string>("Window.Name");
	m_WindowConfig.width = Configuration::Read<int>("Window.Width");
	m_WindowConfig.height = Configuration::Read<int>("Window.Height");
	m_WindowConfig.msaa = Configuration::Read<int>("Renderer.MSAA");
	m_WindowConfig.vSync = Configuration::Read<bool>("Renderer.VSync");
	m_WindowConfig.pContext = this;

	// Enabling msaa
	glfwWindowHint(GLFW_SAMPLES, m_WindowConfig.msaa);
	// Enabling vsync
	glfwWindowHint(GLFW_DOUBLEBUFFER, m_WindowConfig.vSync);

	/* Opening the window */
	m_pGlfwWindow = glfwCreateWindow(m_WindowConfig.width,
									 m_WindowConfig.height,
									 m_WindowConfig.name.c_str(),
									 nullptr,
									 nullptr);

	MC_ASSERT(m_pGlfwWindow, "Failed to create the GLFW Window");

	/* Setting application main context to this window */
	glfwMakeContextCurrent(m_pGlfwWindow);
	/* Setting the configuration of the windows as GLFW's window user pointer */
	glfwSetWindowUserPointer(m_pGlfwWindow, static_cast<void*>(&m_WindowConfig));
}

void Context::CloseWindow()
{
	glfwDestroyWindow(m_pGlfwWindow);
}

void Context::SetupEvents()
{
	glfwSetWindowSizeCallback(m_pGlfwWindow, [](GLFWwindow *pGlfwWindow, int w, int h)
	{
		Configuration::Write("Window.Width", w);
		Configuration::Write("Window.Height", h);
	});

	glfwSetFramebufferSizeCallback(m_pGlfwWindow, [](GLFWwindow *pGlfwWindow, int w, int h)
	{
		glViewport(0, 0, w, h);
	});

	m_InputSys = InputSystem(m_pGlfwWindow);

}

bool Context::IsRunning()
{
	return !glfwWindowShouldClose(m_pGlfwWindow);
}

void Context::UpdateEvents()
{
	glfwPollEvents();
	m_InputSys.Update();
}

void Context::UpdateWindow()
{
	glfwSwapBuffers(m_pGlfwWindow);
}
