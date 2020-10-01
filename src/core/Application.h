#ifndef MINECRAFT_APPLICATION_H
#define MINECRAFT_APPLICATION_H

#include "Context.h"
#include "world/World.h"

class Debug;
class Renderer;

class Application
{
public:
	Application();
	~Application();

	void RunLoop();

private:
	Ref<Renderer> m_Renderer;
	World m_World;
	Context m_Context;
	Ref<Debug> m_Debug;
	double m_DeltaTime, m_LastTime;
};

#endif //MINECRAFT_APPLICATION_H
