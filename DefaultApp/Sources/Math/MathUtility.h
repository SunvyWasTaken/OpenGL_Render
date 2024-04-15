#pragma once

#include <ctime>
#include <random>

namespace Utility
{
	// Function template that is gonna give a value with 
	template <typename T>
	T TRandomInRange(const T min, const T max)
	{
		static_assert(std::is_arithmetic_v<T>, "Value give into the randomInRange should be numerical");

		unsigned int CurrSeed = static_cast<unsigned int>(std::time(nullptr));
		std::mt19937_64 gen(CurrSeed);
		std::uniform_real_distribution<T> dis(min, max);

		return dis(gen);
	}

	int NextPowerTwo(const int nbr);
}

