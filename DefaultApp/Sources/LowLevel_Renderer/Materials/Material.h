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
	void LoadTexture(const std::string& path)
	{
		const char* key = typeid(type).name();
		DeleteTexture(key);
		m_texturesMap.at(key) = new Texture(path);
	}

	//template <typename ...types>
	//void LoadTextures(types... args)
	//{
	//	std::invoke([this, args...](...) mutable {
	//		this->LoadTexture<types::type>(args::path)...;
	//		}, std::forward<Args>(args)...);
	//}

	template <typename type>
	void ApplyTexture(Texture* texture)
	{
		const char* key = typeid(type).name();
		DeleteTexture(key);
		m_texturesMap.at(key) = texture;
	}

	template <typename type>
	Texture* GetTexture()
	{
		return m_texturesMap.at(typeid(type).name());
	}

private:

	void DeleteTexture(const std::string& key)
	{
		if (Texture* value = m_texturesMap.at(key))
		{
			delete value;
		}
	}

public:

	float shininess;

private:

	std::map<std::string, Texture*> m_texturesMap;
};
