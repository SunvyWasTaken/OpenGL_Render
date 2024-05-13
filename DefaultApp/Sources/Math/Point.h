#pragma once

namespace Math
{
	template <typename T>
	struct Point3D
	{
		Point3D(const T& x_ = 0, const T& y_ = 0, const T& z_ = 0)
			: x(x_), y(y_), z(z_)
		{
		}

		Point3D(const Point3D& point)
			: x(point.x), y(point.y), z(point.z)
		{
		}

		T x, y, z;
	};

	template <typename T>
	struct Point2D
	{
		Point2D(const T& x_ = 0, const T& y_ = 0)
			: x(x_), y(y_)
		{
		}

		Point2D(const Point2D& point)
			: x(point.x), y(point.y)
		{
		}

		T x, y;
	};
}
