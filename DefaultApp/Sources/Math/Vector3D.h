#pragma once
#include "Point.h"
#include "Window/OGLWindow.h"

namespace Math
{
	template <typename VectorType>
	struct Vector3D
	{
		Vector3D(const VectorType& x_, const VectorType& y_, const VectorType& z_);
		Vector3D(const Vector3D& vector);
		template <typename type>
		Vector3D<VectorType> operator*(const type& sensitivity) const
		{
			return Vector3D<VectorType>(x * sensitivity, y * sensitivity, z * sensitivity);
		}
		VectorType x, y, z;
	};

	template <typename VectorType>
	Vector3D<VectorType>::Vector3D(const VectorType& x_, const VectorType& y_, const VectorType& z_)
		: x(x_), y(y_), z(z_)
	{
	}

	template <typename VectorType>
	Vector3D<VectorType>::Vector3D(const Vector3D& vector)
		: x(vector.x), y(vector.y), z(vector.z)
	{
	}
	
	template <typename VectorType>
	Point3D<VectorType> operator+(const Point3D<VectorType>& point, const Vector3D<VectorType>& vector)
	{
		return Point3D<VectorType>(point.x + vector.x, point.y + vector.y, point.z + vector.z);
	}
	
	
}

using Vector3f = Math::Vector3D<float>;
