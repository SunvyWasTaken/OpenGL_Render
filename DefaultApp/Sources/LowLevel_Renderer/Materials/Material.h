#pragma once
#include "LowLevel_Renderer/Texture/Texture.h"
#include "Utils/Utility.h"

#include <map>
#include <typeinfo>

class diffuse {};
class specular {};

using TexturesMap = container<diffuse, specular>;

struct Material final
{
	Material();

	~Material();

	void Bind();
	
	template <typename type>
	void LoadTexture(const std::string& specular)
	{
		if (Texture* value = m_texturesMap.at(typeid(type).name()))
		{
			delete value;
		}
		m_texturesMap.at(typeid(type).name()) = new Texture(specular);
	}

	template <typename type>
	void ApplyTexture(Texture* texture)
	{
		m_texturesMap.at(typeid(type).name()) = texture;
	}

	template <typename type>
	Texture* GetTexture()
	{
		return m_texturesMap.at(typeid(type).name());
	}

	float shininess;

private:
	std::map<std::string, Texture*> m_texturesMap;
};
