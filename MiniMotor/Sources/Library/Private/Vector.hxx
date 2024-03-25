
#pragma once

#include "Vector.h"
#include <stdexcept>

namespace Lite
{
	template<typename T>
	inline Vector<T>::Vector(T num) : X(num), Y(num), Z(num)
	{
		if constexpr (!std::is_arithmetic_v<T>)
		{
			throw std::invalid_argument("Creation of a non-numerical vector");
		}
	}

	template<typename T>
	inline Vector<T>::Vector(T x, T y, T z) : X(x), Y(y), Z(z)
	{
		if constexpr (!std::is_arithmetic_v<T>)
		{
			throw std::invalid_argument("Creation of a non-numerical vector");
		}
	}
}
