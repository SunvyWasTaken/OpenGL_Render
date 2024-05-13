#pragma once
#include "LowLevel_Renderer/Texture/Texture.h"

struct Material
{
	Texture diffuseMap;
	Texture specularMap;
	float shininess;
};
