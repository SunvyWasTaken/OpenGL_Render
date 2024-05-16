#pragma once

#include "Math/Matrix.h"

class Viewport final
{
public:
	Viewport();
	Viewport(const float& aspectRatio, const float& fov, const float& nearPlane, const float& farPlane);
	~Viewport() = default;

	Math::Mat4<float> getMatrixProjection();

	float m_apsectRatio;
	float m_fov;
	float m_nearPlane;
	float m_farPlane;

protected:
	Math::Mat4<float> m_matrixProjection;
};
