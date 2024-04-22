#pragma once
#include <array>
#include <cmath>

namespace Math
{
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
}
