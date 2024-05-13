#pragma once

#include "Math/Matrix.h"

class Viewport
{
public:
	explicit Viewport(const float& aspectRatio, const float& fov, const float& nearPlane, const float& farPlane);
	~Viewport();

	Math::Mat4<float> getMatrixProjection();

protected:
	float m_apsectRatio;
	float m_fov;
	float m_nearPlane;
	float m_farPlane;

	Math::Mat4<float> m_matrixProjection;
};
