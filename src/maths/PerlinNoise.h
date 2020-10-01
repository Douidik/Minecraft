#ifndef MINECRAFT_PERLINNOISE_H
#define MINECRAFT_PERLINNOISE_H

#include "Maths.h"

struct PerlinParameters
{
	DoubleVector2 position;
	float factor, offset;
};

class PerlinNoise
{
public:
	PerlinNoise() = delete;
	static float GetValue(const PerlinParameters &parameters);
};

#endif //MINECRAFT_PERLINNOISE_H
