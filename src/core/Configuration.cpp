
#include "Configuration.h"

Ref<JsonFile> Configuration::s_File;
constexpr const char *ConfigurationPath = "res/Configuration.json";

void Configuration::Initialize()
{
	s_File = JsonFile::Create(ConfigurationPath);
}

void Configuration::Release()
{
	s_File.reset();
}