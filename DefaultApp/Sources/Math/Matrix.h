#pragma once
#include <array>
#include <cmath>
#include "Vector3D.h"

namespace Math
{
	struct RightAxis // X axis
	{
		static constexpr int r1 = 1;
		static constexpr int r2 = 2;
	};

	struct UpAxis // Y axis
	{
		static constexpr int r1 = 0;
		static constexpr int r2 = 2;
	};

	struct ForwardAxis // Z axis
	{
		static constexpr int r1 = 0;
		static constexpr int r2 = 1;
	};

	template <typename MatType>
	class Mat4
	{
	public:
		Mat4();

		MatType& operator()(int row, int col);
		const MatType& operator()(int row, int col) const;

		const MatType* data() const;


		static Mat4 identity();

		static Mat4 projection(const MatType& aspectRation, const MatType& fov, const MatType& nearPlane, const MatType& farPlane);

		static Mat4 translate(const Point3D<MatType>& points);

		template <typename Axis>
		static Mat4 rotationFromAxis(const MatType& angle);
		static Mat4 rotation(const Point3D<MatType>& rotations);

		static Mat4 scale(const Point3D<MatType>& scale);

		static Mat4 inverse(const Mat4& mat);

	private:
		std::array<MatType, 16> m_coefs;
	};

	template <typename MatType>
	Mat4<MatType>::Mat4()
	{
		m_coefs.fill(0);
	}

	template <typename MatType>
	MatType& Mat4<MatType>::operator()(int row, int col)
	{
		return m_coefs[row + col * 4];
	}

	template <typename MatType>
	const MatType& Mat4<MatType>::operator()(int row, int col) const
	{
		return m_coefs[row + col * 4];
	}

	template <typename MatType>
	const MatType* Mat4<MatType>::data() const
	{
		return m_coefs.data();
	}

	template <typename MatType>
	Mat4<MatType> Mat4<MatType>::identity()
	{
		Mat4 matIdentity;
		matIdentity(0, 0) = matIdentity(1, 1) = matIdentity(2, 2) = matIdentity(3, 3) = 1;
		return matIdentity;
	}

	template <typename MatType>
	Mat4<MatType> Mat4<MatType>::projection(const MatType& aspectRation, const MatType& fov, const MatType& nearPlane,
		const MatType& farPlane)
	{
		Mat4 matrixProjection;
		matrixProjection(0, 0) = 1.f / (aspectRation * std::tan(fov / 2));
		matrixProjection(1, 1) = 1.f / std::tan(fov / 2);
		matrixProjection(2, 2) = (nearPlane + farPlane) / (nearPlane - farPlane);
		matrixProjection(2, 3) = (2.f * nearPlane * farPlane) / (nearPlane - farPlane);
		matrixProjection(3, 2) = -1.f;
		return matrixProjection;
	}

	template <typename MatType>
	Mat4<MatType> Mat4<MatType>::translate(const Point3D<MatType>& points)
	{
		Mat4 trans = identity();
		trans(0, 3) = points.x;
		trans(1, 3) = points.y;
		trans(2, 3) = points.z;

		return trans;
	}

	template <typename MatType>
	template <typename Axis>
	Mat4<MatType> Mat4<MatType>::rotationFromAxis(const MatType& angle)
	{
		static_assert(std::is_same_v<Axis, RightAxis> || std::is_same_v<Axis, UpAxis> || std::is_same_v<Axis, ForwardAxis>, "Axis type not good!");

		Mat4 rot = identity();
		rot(Axis::r1, Axis::r1) = std::cos(angle);
		rot(Axis::r1, Axis::r2) = -std::sin(angle);
		rot(Axis::r2, Axis::r1) = std::sin(angle);
		rot(Axis::r2, Axis::r2) = std::cos(angle);

		return rot;
	}

	template <typename MatType>
	Mat4<MatType> Mat4<MatType>::rotation(const Point3D<MatType>& rotations)
	{
		return rotationFromAxis<RightAxis>(rotations.x) * rotationFromAxis<UpAxis>(rotations.y) * rotationFromAxis<ForwardAxis>(rotations.z);
	}

	template <typename MatType>
	Mat4<MatType> Mat4<MatType>::scale(const Point3D<MatType>& scale)
	{
		Mat4 matScale = identity();
		matScale(0, 0) = scale.x;
		matScale(1, 1) = scale.y;
		matScale(2, 2) = scale.z;

		return matScale;
	}
	

	template <typename MatType>
	Mat4<MatType> operator*(const Mat4<MatType>& op1, const Mat4<MatType>& op2)
	{
		Mat4<MatType> result;
		for (int row = 0; row < 4; ++row)
		{
			for (int col = 0; col < 4; ++col)
			{
				result(row, col) = 0;
				for (int k = 0; k < 4; ++k)
				{
					result(row, col) += op1(row, k) * op2(k, col);
				}
			}
		}

		return result;
	}
	
	template <typename MatType>
	Vector3D<MatType> operator*(const Mat4<MatType>& matrix, const Vector3D<MatType>& vec)
	{
		Vector3D<MatType> result = {0.f,0.f,0.f};
		result.x = vec.x * matrix(0, 0) + vec.y * matrix(1, 0) + vec.z * matrix(2, 0) + matrix(3, 0);
		result.y = vec.x * matrix(0, 1) + vec.y * matrix(1, 1) + vec.z * matrix(2, 1) + matrix(3, 1);
		result.z = vec.x * matrix(0, 2) + vec.y * matrix(1, 2) + vec.z * matrix(2, 2) + matrix(3, 2);
		return result;
	}
}
