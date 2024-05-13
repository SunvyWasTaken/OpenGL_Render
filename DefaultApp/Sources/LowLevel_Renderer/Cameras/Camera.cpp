#include "Camera.h"

Math::Mat4<float> Camera::getMatrixView() const
{
	return transform.getMatrix();
}
