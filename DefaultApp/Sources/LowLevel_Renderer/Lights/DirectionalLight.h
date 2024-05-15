#pragma once
#include "ILight.h"


struct DirectionalLight : ILight
{
	void getUniform(Shader* shader) override;
	void getUniform(Shader* shader, size_t index) override;
};