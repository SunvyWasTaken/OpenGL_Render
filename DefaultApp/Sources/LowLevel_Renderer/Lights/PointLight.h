#pragma once
#include "ILight.h"

template <typename LightType>
struct PointLight : public ILight<LightType>
{
	float constant;
	float linear;
	float quadratic;
};
