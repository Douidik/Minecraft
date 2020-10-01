#include "PerlinNoise.h"
#include "maths/Random.h"

float PerlinNoise::GetValue(const PerlinParameters &parameters)
{
	return parameters.offset + glm::perlin(parameters.position) * parameters.factor;
}