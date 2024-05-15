#pragma once
#include <vector>

#include "LowLevel_Renderer/Lights/DirectionalLight.h"
#include "LowLevel_Renderer/Lights/PointLight.h"
#include "Math/Matrix.h"

using mat4 = Math::Mat4<float>;

struct ContextRenderer
{
	mat4 projection = mat4::identity();
	Camera camera;
	DirectionalLight directionalLight;
	std::vector<PointLight> pointLights;
};
