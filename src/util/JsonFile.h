#ifndef MINECRAFT_JSONFILE_H
#define MINECRAFT_JSONFILE_H

class JsonFile
{
public:
	friend class Configuration;
	friend class BlockDatabase;

	static Ref<JsonFile> Create(const fs::path &path);

	JsonFile() = default;
	JsonFile(const fs::path &path);
	~JsonFile();

	/* Read and Write functions */
	template<typename T>
	T Read(const std::string &name)
	{
		nlohmann::json *pValue = Find(name);
		return pValue->get<T>();
	}

	template<typename T>
	void Write(const std::string &name, T& newValue)
	{
		nlohmann::json *pValue = Find(name);
		*pValue = newValue;
	}

private:
	nlohmann::json *Find(const std::string &name);

	std::unordered_map<std::string, nlohmann::json*> m_Cache;
	std::ifstream m_Ifs;
	nlohmann::json m_File;
	fs::path m_FilePath;
};

#endif //MINECRAFT_JSONFILE_H
