#ifndef MINECRAFT_RANDOM_H
#define MINECRAFT_RANDOM_H

class Random
{
public:
	static void Initialize();
	static const int GetValue(int min, int max);

};

class UniformRandom
{
public:
	static const int GetValue(int min, int max);
	static void ReseedUniform();

private:
	static std::default_random_engine s_Generator;
};

#endif //MINECRAFT_RANDOM_H
