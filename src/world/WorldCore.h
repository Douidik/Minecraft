#ifndef MINECRAFT_WORLDCORE_H
#define MINECRAFT_WORLDCORE_H

#include "block/Block.h"
#include "maths/Maths.h"

class WorldCore
{
public:
	static void Initialize();
	static void Release();
private:
	static bool s_IsInitialized;
};

#endif //MINECRAFT_WORLDCORE_H
