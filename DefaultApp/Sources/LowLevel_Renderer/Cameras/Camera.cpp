#include "Camera.h"

Math::Mat4<float> Camera::getMatrixView()
{
	return transform.getMatrix();
}
