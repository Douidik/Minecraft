#ifndef MINECRAFT_BLOCKDATABASE_H
#define MINECRAFT_BLOCKDATABASE_H

#include "util/JsonFile.h"
enum class BlockFace : int;

/* Singleton block data-base */
class BlockDatabase
{
public:
	static void Initialize();
	static void Release();

	static int GetTextureID(int id, const BlockFace &face);

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
	static std::map<std::pair<int, const BlockFace>, int> s_TextureIdCache;
	static Ref<JsonFile> s_File;
};

#endif //MINECRAFT_BLOCKDATABASE_H
