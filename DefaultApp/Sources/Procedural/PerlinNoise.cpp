#include "PerlinNoise.h"

#if DEBUG
#include <iostream>
#endif // DEBUG

#include <ctime>
#include <random>

SimplePerlinNoise::SimplePerlinNoise()
	: height(25)
	, width(50)
	, NoiseMap(height, MapRow(width, 0))
	, bUseRandomSeed(true)
	, RandomSeed(0)
{
}

void SimplePerlinNoise::GenerateNoise()
{
	if (bUseRandomSeed)
	{
		RandomSeed = static_cast<unsigned int>(std::time(nullptr));
	}
	std::mt19937 gen(RandomSeed);
	std::bernoulli_distribution dist(0.8);
	std::uniform_int_distribution<> dis(0, 1);

	for (unsigned int h = 0; h < height; ++h)
	{
		for (unsigned int w = 0; w < width; ++w)
		{
			NoiseMap[h][w] = dist(gen);
		}
	}
	
}

#if DEBUG

void SimplePerlinNoise::DebugPrintResult()
{
	for (unsigned int h = 0; h < height; ++h)
	{
		for (unsigned int w = 0; w < width; ++w)
		{
			std::cout << (NoiseMap[h][w] ? " " : "0");
		}
		std::cout << std::endl;
	}
}

#endif // DEBUG
