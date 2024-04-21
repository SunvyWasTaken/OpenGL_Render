#pragma once
#include <array>
#include <glad/glad.h>

#include "Vertex.h"

template <typename ShapeType>
class Shape
{
	using vertex_type = Vertex<ShapeType>;

public:
	Shape();
	virtual ~Shape();

	virtual void load();
	virtual void render();

protected:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_shaderProgram;
	GLuint m_uniID;
};

template <typename ShapeType>
Shape<ShapeType>::Shape()
	: m_vao(0), m_vbo(0), m_shaderProgram(0), m_uniID(0)
{
}

template <typename ShapeType>
Shape<ShapeType>::~Shape()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteProgram(m_shaderProgram);
}

template <typename ShapeType>
void Shape<ShapeType>::load()
{
	
}
