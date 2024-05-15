#pragma once

#include "LowLevel_Renderer/Lights/DirectionalLight.h"
#include "LowLevel_Renderer/Lights/PointLight.h"
#include "LowLevel_Renderer/Cameras/Camera.h"
#include "Math/Matrix.h"

#include <vector>

using mat4 = Math::Mat4<float>;

struct ContextRenderer
{
	mat4 projection = mat4::identity();
	Camera camera;
	DirectionalLight directionalLight;
	std::vector<PointLight> pointLights;
};
