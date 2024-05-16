#pragma once

#include "LowLevel_Renderer/Lights/DirectionalLight.h"
#include "LowLevel_Renderer/Lights/PointLight.h"
#include "LowLevel_Renderer/Cameras/Camera.h"
#include "Math/Matrix.h"
#include "Math/Point.h"

#include <vector>

using mat4 = Math::Mat4<float>;
using vec3 = Math::Point3D<float>;

struct Plane {
	vec3 Normal;
	float YCoord;
};

struct ContextRenderer
{
	mat4 projection = mat4::identity();
	Camera camera;
	DirectionalLight directionalLight;
	std::vector<PointLight> pointLights;
	Plane waterPlane;
};
