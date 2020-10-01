#include "JsonFile.h"

Ref<JsonFile> JsonFile::Create(const fs::path &path)
{
	return CreateRef<JsonFile>(path);
}

JsonFile::JsonFile(const fs::path &path)
	: m_FilePath(path)
{
	m_Ifs.open(path);
	MC_ASSERT(m_Ifs, "Failed to open json file from: {}", m_FilePath.string());
	m_Ifs >> m_File;
}

JsonFile::~JsonFile()
{
	/* Dumping to json config file */
	std::ofstream ofs(m_FilePath);
	MC_ASSERT(ofs, "Failed to open json file from: {}", m_FilePath.string());
	ofs << std::setw(5) << m_File << std::endl;
}

nlohmann::json *JsonFile::Find(const std::string &name)
{
	if(m_Cache.find(name) != m_Cache.end())
	{
		return m_Cache[name];
	}

	/* From name to hashed key */
	std::vector<std::string> keys;
	std::string key;
	std::istringstream iss(name);

	while(std::getline(iss, key, '.'))
	{
		keys.push_back(key);
	}

	/* Loading the value */
	try
	{
		nlohmann::json *pTarget = &m_File;

		for(const std::string &k : keys)
		{
			pTarget = &(*pTarget)[k];
		}

		m_Cache[name] = pTarget;
		return pTarget;
	}
	catch(const std::out_of_range &error)
	{
		MC_ERROR(error.what());
	}

	return nullptr;
}