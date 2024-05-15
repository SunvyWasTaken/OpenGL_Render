#pragma once
#include "Math/Color.h"
#include "Math/Point.h"
#include "Math/Vector3D.h"

template <typename VertexType>
struct Vertex
{
	using P3D = Math::Point3D<VertexType>;
	using P2D = Math::Point2D<VertexType>;
	using Color = Math::Color<VertexType>;

	Vertex(const Math::Point3D<VertexType>& point, const Math::Color<VertexType>& color)
		: m_point(point), m_color(color), m_textureCoords(Math::Point2D<VertexType>())
	{
	}

	Vertex(const Math::Point3D<VertexType>& point, const Math::Color<VertexType>& color, const Math::Point2D<VertexType>& textureCoords)
		: m_point(point), m_color(color), m_textureCoords(textureCoords)
	{
	}

	Vertex(const P3D& point, const Color& color, const P2D& textureCoords, const P3D& normal)
		: m_point(point), m_color(color), m_textureCoords(textureCoords), m_normal(normal)
	{
	}

	P3D m_point;
	Color m_color;
	P2D m_textureCoords;
	P3D m_normal;
};
