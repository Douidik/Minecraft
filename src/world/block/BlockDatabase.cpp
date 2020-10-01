#include "BlockDatabase.h"
#include "graphics/block/BlockMesh.h"

Ref<JsonFile> BlockDatabase::s_File;
std::map<std::pair<int, const BlockFace>, int> BlockDatabase::s_TextureIdCache;
constexpr const char *BlockDatabasePath = "res/BlockDatabase.json";

void BlockDatabase::Initialize()
{
	s_File = JsonFile::Create(BlockDatabasePath);
}

void BlockDatabase::Release()
{
	s_File.reset();
}

int BlockDatabase::GetTextureID(int id, const BlockFace &face)
{
	int textureID = 0;

	if(s_TextureIdCache.find({id, face}) != s_TextureIdCache.end()) // texture is already cached
	{
		textureID = s_TextureIdCache[{id, face}];
	}
	else
	{
		/* Parsing the key texture id name */
		constexpr auto fromFaceToPart = [](const BlockFace &face) -> std::string
		{
			switch (face)
			{
			case BlockFace::Front:
			case BlockFace::Right:
			case BlockFace::Back:
			case BlockFace::Left:
				return "Side";
			case BlockFace::Top:
				return "Top";
			case BlockFace::Bottom:
				return "Bottom";
			}
		};

		std::string keyName = std::to_string(id) + ".TextureID."s + fromFaceToPart(face);
		textureID = Read<int>(keyName);
		s_TextureIdCache[{id, face}] = textureID;
	}

	return textureID;
}
