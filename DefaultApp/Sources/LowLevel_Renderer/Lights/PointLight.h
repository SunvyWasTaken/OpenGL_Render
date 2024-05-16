#pragma once
#include "ILight.h"

struct Shader;

struct PointLight : ILight
{
	void getUniform(Shader* shader) override;
	void getUniform(Shader* shader, size_t index) override;

	float constant = 1.f;
	float linear = 0.09f;
	float quadratic = 0.032f;
};
