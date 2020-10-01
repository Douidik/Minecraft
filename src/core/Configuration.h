#ifndef MINECRAFT_CONFIGURATION_H
#define MINECRAFT_CONFIGURATION_H

#include "util/JsonFile.h"

/* Singleton configuration class */
class Configuration
{
public:
	static void Initialize();
	static void Release();

	/* Read and Write functions */
	template<typename T>
	static T Read(const std::string &name)
	{
		return s_File->Read<T>(name);
	}

	template<typename T>
	static void Write(const std::string &name, T& newValue)
	{
		s_File->Write(name, newValue);
	}

private:
	static Ref<JsonFile> s_File;
};

#endif //MINECRAFT_CONFIGURATION_H
