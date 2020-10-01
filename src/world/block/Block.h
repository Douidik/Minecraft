#ifndef MINECRAFT_BLOCK_H
#define MINECRAFT_BLOCK_H

constexpr int BlockVoidID = 0;

struct Block
{
	Block(int _id = 0)
	: id(_id)
	{}

	int id;
};

#endif //MINECRAFT_BLOCK_H
