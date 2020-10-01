#include "Random.h"

void Random::Initialize()
{
	std::srand(time(nullptr));
}

const int Random::GetValue(int min, int max)
{
	const int value = min + (std::rand() % (max - min + 1));
	return value;
}

std::default_random_engine UniformRandom::s_Generator;

const int UniformRandom::GetValue(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(s_Generator);
}

void UniformRandom::ReseedUniform()
{
	s_Generator.seed(time(nullptr));
}
