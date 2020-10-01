#include "mc.pch"
#include "WorldCore.h"
#include "block/BlockDatabase.h"

bool WorldCore::s_IsInitialized = false;

void WorldCore::Initialize()
{
	if(s_IsInitialized)
		return;

	BlockDatabase::Initialize();
	s_IsInitialized = true;
}

void WorldCore::Release()
{
	BlockDatabase::Release();
	s_IsInitialized = false;
}
