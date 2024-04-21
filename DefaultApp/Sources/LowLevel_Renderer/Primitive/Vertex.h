#pragma once
#include "Math/Color.h"
#include "Math/Point.h"
#include "Math/Vector3D.h"

template <typename VertexType>
struct Vertex
{
	Vertex(const Math::Point3D<VertexType>& point, const Math::Color<VertexType>& color)
		: m_point(point), m_color(color), m_textureCoords(Math::Point2D<VertexType>())
	{
	}

	Vertex(const Math::Point3D<VertexType>& point, const Math::Color<VertexType>& color, const Math::Point2D<VertexType>& textureCoords)
		: m_point(point), m_color(color), m_textureCoords(textureCoords)
	{
	}

private:
	Math::Point3D<VertexType> m_point;
	Math::Color<VertexType> m_color;
	Math::Point2D<VertexType> m_textureCoords;
};
