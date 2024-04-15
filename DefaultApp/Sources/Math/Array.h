#pragma once

#include <vector>

template <typename T>
using TArray = std::vector<T>;

template <typename T>
class TArray2D
{
public:
	explicit TArray2D(const unsigned int size = 0)
	: m_Tab(size, TArray<T>(size, static_cast<T>(0)))
	{
		//static_assert(std::is_arithmetic_v<T>, "A TArray2D must be a numeric type");
	}

	constexpr auto& operator()(const unsigned int x, const unsigned int y)
	{
		return m_Tab[x][y];
	}

private:
	std::vector<TArray<T>> m_Tab;
};
