#pragma once
#include "Matrix.h"
#include "Point.h"

namespace Math
{
	template <typename Type>
	class Transform
	{
		using P3D = Point3D<Type>;
		using Mat4 = Mat4<Type>;

	public:
		explicit Transform(const P3D& position_ = P3D{}, const P3D& rotation_ = P3D{}, const P3D& scale_ = P3D{1.f, 1.f, 1.f});

		Mat4 getMatrix();
		Mat4 getMatrix() const;

		P3D position;
		P3D rotation;
		P3D scale;
	};

	template <typename Type>
	Transform<Type>::Transform(const P3D& position_, const P3D& rotation_, const P3D& scale_)
		: position(position_), rotation(rotation_), scale(scale_)
	{
	}

	template <typename Type>
	Mat4<Type> Transform<Type>::getMatrix()
	{
		Mat4 mTransform = Mat4::identity();
		Mat4 mTrans = Mat4::translate(position);
		Mat4 mRot = Mat4::rotation(rotation);
		Mat4 mScale = Mat4::scale(scale);

		mTransform = mTrans * mRot * mScale;
		return mTransform;
	}

	template <typename Type>
	Mat4<Type> Transform<Type>::getMatrix() const
	{
		Mat4 mTransform = Mat4::identity();
		Mat4 mTrans = Mat4::translate(position);
		Mat4 mRot = Mat4::rotation(rotation);
		Mat4 mScale = Mat4::scale(scale);

		mTransform = mTrans * mRot * mScale;
		return mTransform;
	}
}
