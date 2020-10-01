#include "Core.h"

#include "Context.h"
#include "Configuration.h"
#include "maths/Random.h"

bool Core::s_IsInitialized = false;

void Core::Initialize()
{
	/* Preventing from initializing the core twice */
	if(s_IsInitialized)
		return;

	Logger::Initialize();
	Configuration::Initialize();
	Context::Initialize();
	Random::Initialize();

	s_IsInitialized = true;
}

void Core::Release()
{
	Context::Release();
	Configuration::Release();
	s_IsInitialized = false;
}
