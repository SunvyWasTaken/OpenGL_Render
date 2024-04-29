#pragma once
#include "Math/Matrix.h"

using mat4 = Math::Mat4<float>;

struct ContextRenderer
{
	mat4 projection = mat4::identity();
	mat4 view = mat4::identity();
};
