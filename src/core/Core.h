#ifndef MINECRAFT_CORE_H
#define MINECRAFT_CORE_H

class Core
{
public:
	static void Initialize();
	static void Release();

private:
	static bool s_IsInitialized;

};

#endif //MINECRAFT_CORE_H
