#include "Viewport.h"

Viewport::Viewport(const float& aspectRatio, const float& fov, const float& nearPlane, const float& farPlane)
	: m_apsectRatio(aspectRatio), m_fov(fov), m_nearPlane(nearPlane), m_farPlane(farPlane), m_matrixProjection(Math::Mat4<float>::identity())
{
	m_matrixProjection = Math::Mat4<float>::projection(m_apsectRatio, fov, nearPlane, farPlane);
}

Viewport::~Viewport()
{
}

Math::Mat4<float> Viewport::getMatrixProjection()
{
	return m_matrixProjection;
}
