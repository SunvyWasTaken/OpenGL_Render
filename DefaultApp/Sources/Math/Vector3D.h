#pragma once

namespace Math
{
	template <typename VectorType>
	struct Vector3D
	{
		Vector3D(const VectorType& x_, const VectorType& y_);
		Vector3D(const Vector3D& vector);

		VectorType x, y;
	};

	template <typename VectorType>
	Vector3D<VectorType>::Vector3D(const VectorType& x_, const VectorType& y_)
		: x(x_), y(y_)
	{
	}

	template <typename VectorType>
	Vector3D<VectorType>::Vector3D(const Vector3D& vector)
		: x(vector.x), y(vector.y)
	{
	}
}