#include "Viewport.h"

Viewport::Viewport(const float& aspectRation, const float& fov, const float& nearPlane, const float& farPlane)
	: m_apsectRation(aspectRation), m_fov(fov), m_nearPlane(nearPlane), m_farPlane(farPlane), m_matrixProjection(Math::Mat4<float>::identity())
{
	m_matrixProjection = Math::Mat4<float>::projection(m_apsectRation, fov, nearPlane, farPlane);
}

Viewport::~Viewport()
{
}

Math::Mat4<float> Viewport::getMatrixProjection()
{
	return m_matrixProjection;
}
