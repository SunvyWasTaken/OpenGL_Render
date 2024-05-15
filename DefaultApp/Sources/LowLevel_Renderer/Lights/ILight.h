#pragma once
#include "LowLevel_Renderer/Shader/Shader.h"
#include "Math/Color.h"
#include "Math/Point.h"


struct ILight
{
	virtual ~ILight() = default;
	using Vec3 = Math::Point3D<float>;
	using Color3 = Math::Color<float>;

	virtual void getUniform(Shader* shader) = 0;
	virtual void getUniform(Shader* shader, size_t index) = 0;

	Vec3 position;
	Vec3 direction;

	Color3 ambient;
	Color3 diffuse;
	Color3 specular;
};
