#pragma once
#include "ILight.h"


struct DirectionalLight : ILight
{
	void getUniform(Shader* shader) override;
};