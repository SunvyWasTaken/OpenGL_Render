#pragma once

namespace Math
{
	template <typename T>
	struct Color
	{
		Color(const T& r_ = 0, const T& g_ = 0, const T& b_ = 0, const T& a_ = 1) 
			: r(r_), g(g_), b(b_), a(a_)
		{
		}

		Color(const Color& color)
			: r(color.r), g(color.g), b(color.b), a(color.a)
		{
		}

		T r, g, b, a;
	};
}