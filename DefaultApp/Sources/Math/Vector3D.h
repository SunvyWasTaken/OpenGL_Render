#pragma once

namespace Math
{
	template <typename VectorType>
	struct Vector3D
	{
		Vector3D(const VectorType& x_, const VectorType& y_, const VectorType& z_);
		Vector3D(const Vector3D& vector);

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
}

using Vector3Df = Math::Vector3D<double>;
using uint = unsigned int;