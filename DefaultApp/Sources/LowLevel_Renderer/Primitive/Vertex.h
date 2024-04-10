#pragma once
#include "Math/Color.h"
#include "Math/Point.h"

template <typename T>
struct Vertex
{
	Vertex(const Math::Point3D<T>& point, const Math::Color<T>& color)
		: m_point(point), m_color(color)
	{
	}

private:
	Math::Point3D<T> m_point;
	Math::Color<T> m_color;
};
