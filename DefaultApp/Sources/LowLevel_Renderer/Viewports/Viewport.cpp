#include "Viewport.h"

Viewport::Viewport() : m_apsectRatio(0), m_fov(0), m_nearPlane(0), m_farPlane(0), m_matrixProjection(Math::Mat4<float>::identity())
{
}

Viewport::Viewport(const float& aspectRatio, const float& fov, const float& nearPlane, const float& farPlane)
	: m_apsectRatio(aspectRatio), m_fov(fov), m_nearPlane(nearPlane), m_farPlane(farPlane), m_matrixProjection(Math::Mat4<float>::identity())
{
	m_matrixProjection = Math::Mat4<float>::projection(m_apsectRatio, fov, nearPlane, farPlane);
}

Math::Mat4<float> Viewport::getMatrixProjection()
{
	return m_matrixProjection;
}