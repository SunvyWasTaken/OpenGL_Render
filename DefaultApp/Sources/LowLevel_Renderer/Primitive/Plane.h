#pragma once

#include "LowLevel_Renderer/Primitive/Vertex.h"
#include "PrimitiveUtils.h"
#include "Math/Matrix.h"
#include "Math/Transform.h"

#include <array>
#include <glad/glad.h>

#include "PrimitiveMesh.h"

template <typename T>
class Plane : public PrimitiveMesh<T>
{
	using vertex_type = Vertex<T>;
	using Transform = Math::Transform<T>;
	using parent = PrimitiveMesh<T>;

public:
	Plane()
		: parent()
	{
		this->triCount = 2;
	}

	~Plane()
	{
	}

	void load() override
	{
		std::array<vertex_type, 4> vertices = {
			vertex_type( { -1.f,	0.0f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		0.0f }, { 0.f, 1.f, 0.f}),
			vertex_type( { -1.f,	0.0f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		1.0f }, { 0.f, 1.f, 0.f}),
			vertex_type( { 1.f,	0.0f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		1.0f }, { 0.f, 1.f, 0.f}),
			vertex_type( { 1.f,	0.0f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		0.0f }, { 0.f, 1.f, 0.f})
		};

		std::array<GLuint, 6> indices = {
			0, 1, 2,
			2, 3, 0
		};

		LOAD_ARRAY_BUFFER(this->m_vbo, vertices)
		LOAD_ELEMENT_ARRAY_BUFFER(this->m_ebo, indices)

		parent::load();
	}

	void render(ContextRenderer& contextRenderer) override
	{
		parent::render(contextRenderer);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
};
