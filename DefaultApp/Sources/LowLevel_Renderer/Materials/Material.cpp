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
	if(m_texturesMap.empty())
		return;

	for (auto& [key, value] : m_texturesMap)
	{
		if (value)
			delete value;

		value = nullptr;
	}

	m_texturesMap.clear();
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

