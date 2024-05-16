#include "Material.h"

Material::Material() : shininess(0.f)
{
	for (const char* textureName : TexturesMap::Names)
	{
		m_texturesMap.emplace(textureName, nullptr);
	}
}

Material::~Material()
{
	for (auto& [key, value] : m_texturesMap)
	{
		if (value)
			delete value;
	}
}

void Material::Bind()
{
	int i = 0;
	for (auto& [key, value] : m_texturesMap)
	{
		if (value)
		{
			value->bind(GL_TEXTURE0 + i);
		}
		++i;
	}
}

