#pragma once

#include "Cube.h"
#include "LowLevel_Renderer/Lights/PointLight.h"

template <typename Type>
class CubeLight : public Cube<Type>, public PointLight
{
	using vertex_type = Vertex<Type>;
	using Transform = Math::Transform<Type>;
	using Color = Math::Color<Type>;
	using parent = Cube<Type>;

public:
	CubeLight();
	~CubeLight();

	void load() override;
	void render(ContextRenderer& contextRenderer) override;
	void setColor(const Color& color);
};

template <typename Type>
CubeLight<Type>::CubeLight()
	: parent()
{
}

template <typename Type>
CubeLight<Type>::~CubeLight()
{
}

template <typename Type>
void CubeLight<Type>::load()
{
	parent::load();
}

template <typename Type>
void CubeLight<Type>::render(ContextRenderer& contextRenderer)
{
	this->position = this->transform.position;

	parent::render(contextRenderer);

	this->m_shaders->setVec3("color", this->diffuse);
}

template <typename Type>
void CubeLight<Type>::setColor(const Color& color)
{
	this->diffuse = color;
	this->ambient = this->diffuse * 2.f;
	this->specular = 1.f;
}
