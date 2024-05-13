#pragma once

#include "Vertex.h"
#include "LowLevel_Renderer/Texture/Texture.h"
#include <glad/glad.h>

#include "Math/Transform.h"

template <typename ShapeType>
class Shape
{
	using vertex_type = Vertex<ShapeType>;
	using Transform = Math::Transform<ShapeType>;

public:
	Shape();
	virtual ~Shape();

	virtual void load() {};
	virtual void update() {};
	virtual void render(const Math::Mat4<ShapeType>& vp) {};

	Transform transform;

protected:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
	GLuint m_shaderProgram;
	Texture m_texture;
};

template <typename ShapeType>
Shape<ShapeType>::Shape()
	: transform(Transform{}), m_vao(0), m_vbo(0), m_ebo(0), m_shaderProgram(0), m_texture(Texture{})
{
}

template <typename ShapeType>
Shape<ShapeType>::~Shape()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
	glDeleteProgram(m_shaderProgram);
}