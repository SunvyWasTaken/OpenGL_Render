#pragma once
#include "Math/Transform.h"

class Camera
{
public:
	Camera() = default;
	~Camera() = default;

	Math::Mat4<float> getMatrixView();

	Math::Transform<float> transform;
protected:
};
