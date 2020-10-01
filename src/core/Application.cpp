#include "Application.h"
#include "Core.h"
#include "graphics/Graphics.h"
#include "maths/Maths.h"
#include "debug/Debug.h"

Application::Application()
	: m_DeltaTime(0.0), m_LastTime(0.0)
{
	Core::Initialize();
	m_Context.Create();
	m_Renderer = Renderer::Create();

	m_World.Create();
	m_Renderer->SetMainCamera(m_World.GetPlayer()->GetCamera());
	m_Debug = Debug::Create();
}

Application::~Application()
{
	m_Context.Destroy();
	Core::Release();
}

void Application::RunLoop()
{
	std::vector<float> framePerSecond;
	bool shouldDrawFPS = true;

	while(m_Context.IsRunning() && !m_Context.Input().IsKeyPressed(KeyCode::Escape))
	{
		float time = static_cast<float>(glfwGetTime());
		m_DeltaTime = time - m_LastTime;
		m_LastTime = time;

		/* Temporary benchmark */
#ifdef MC_DEBUG
		framePerSecond.push_back(1.0f / m_DeltaTime);
		if(static_cast<int>(std::floor(time)) % 2 == 0)
		{
			if(shouldDrawFPS)
			{
				float averageFps = std::accumulate(framePerSecond.begin(), framePerSecond.end(), 0.0) / framePerSecond.size();
				MC_LOG_DEBUG("Average FPS: {}", averageFps);
				framePerSecond.clear();
				shouldDrawFPS = false;
			}
		}
		else
		{
			shouldDrawFPS = true;
		}
#endif


		m_Context.UpdateEvents();
		m_World.Update(m_Context.Input(), static_cast<float>(m_DeltaTime));
		m_Debug->Update(m_Context.Input());

		Renderer::Clear();

		m_Renderer->Update();
		m_World.Draw(m_Renderer);

		m_Context.UpdateWindow();
	}
}
