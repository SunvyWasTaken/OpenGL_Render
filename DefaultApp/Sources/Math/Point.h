#pragma once

namespace Math
{
	template <typename T>
	struct Point3D
	{
		T x, y, z;
		
		Point3D(const T& x_ = 0, const T& y_ = 0, const T& z_ = 0)
			: x(x_), y(y_), z(z_)
		{
		}

		Point3D(const Point3D& point)
			: x(point.x), y(point.y), z(point.z)
		{
		}

		template <typename type>
		Point3D<T> operator*(const type& entrant)
		{
			//assert(std::is_arithmetic_v<type>);
			return { x * entrant, y * entrant, z * entrant};
		}

		template <typename Type>
		Point3D<T> operator+(const Point3D<Type> other)
		{
			return { x + other.x, y + other.y, z + other.z };
		}
		
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

using Point2i = Math::Point2D<int>;

using Point3f = Math::Point3D<float>;
