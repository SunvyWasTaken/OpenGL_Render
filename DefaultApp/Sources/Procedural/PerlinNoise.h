#pragma once

#include <vector>

class SimplePerlinNoise
{
	using MapRow = std::vector<bool>;
	using Map2D = std::vector<MapRow>;

public:

	SimplePerlinNoise();

	void GenerateNoise();

#if DEBUG
	void DebugPrintResult();
#endif // DEBUG


protected:

	unsigned int height;

	unsigned int width;

	Map2D NoiseMap;

	bool bUseRandomSeed;

	unsigned int RandomSeed;
};