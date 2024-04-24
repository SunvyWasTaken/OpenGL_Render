#pragma once

#include "PrimitiveUtils.h"
#include "Vertex.h"
#include "LowLevel_Renderer/Texture/Texture.h"
#include "Math/Transform.h"
#include "LowLevel_Renderer/Shader/Shader.h"
#include "Math/Matrix.h"

#include <glad/glad.h>
#include <array>

template <typename Type>
class Cube
{
	using vertex_type = Vertex<Type>;
	using Transform = Math::Transform<Type>;

public:
	Cube();
	~Cube();

	void load();
	void update();
	void render(const Math::Mat4<Type>& vp);

	Transform transform;
private:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
	GLuint m_shaderProgram;
	Texture m_texture;
};

template <typename Type>
Cube<Type>::Cube()
	: transform(Transform{}), m_vao(0), m_vbo(0), m_ebo(0), m_shaderProgram(0), m_texture(Texture{})
{
	load();
}

template <typename Type>
Cube<Type>::~Cube()
{
	DELETE_BUFFER_WITH_ELEMENTS()
}

template <typename Type>
void Cube<Type>::load()
{
	m_texture = Texture("Ressources\\sc.png", GL_TEXTURE0);

	std::array<vertex_type, 8> vertices = {
		vertex_type({ -1.f,	-1.f,	 1.f }, { 1.0f,	0.0f,	0.0f }, {  0.0f,		0.0f }),
		vertex_type({ -1.f,	1.f,	 1.f }, { 0.0f,	1.0f,	0.0f }, {  0.0f,		1.0f }),
		vertex_type({  1.f,	1.f,	 1.f }, { 0.0f,	1.0f,	0.0f }, {  1.0f,		1.0f }),
		vertex_type({  1.f,	-1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		0.0f }),

		vertex_type({ -1.f,	-1.f,	-1.f }, { 1.0f,	0.0f,	0.0f }, {  0.0f,		0.0f }),
		vertex_type({ -1.f,	1.f,	-1.f }, { 0.0f,	1.0f,	1.0f }, {  0.0f,		1.0f }),
		vertex_type({  1.f,	1.f,	-1.f }, { 0.0f,	0.0f,	1.0f }, {  1.0f,		1.0f }),
		vertex_type({  1.f,	-1.f,	-1.f }, { 0.0f,	0.0f,	1.0f }, {  1.0f,		0.0f })

	};

	std::array<GLuint, 36> indices = {
		0, 1, 2, //Front
		2, 3, 0,

		4, 5, 1, //Left
		1, 0, 4,

		7, 6, 5, //Back
		5, 4, 7,

		3, 2, 6, //Right
		6, 7, 3,

		1, 5, 6, //Top
		6, 2, 1,

		4, 0, 3, //Bottom
		3, 7, 4
	};

	LOAD_VERTEX_ARRAYS(m_vao)
	LOAD_ARRAY_BUFFER(m_vbo, vertices)
	LOAD_ELEMENT_ARRAY_BUFFER(m_ebo, indices)

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER,  "default.vert"},
		{GL_FRAGMENT_SHADER, "default.frag"},
		{GL_NONE, nullptr}
	};

	m_shaderProgram = Shader::loadShader(shaders);
	glUseProgram(m_shaderProgram);

	// /!\ Attention, ca marche que si t = float, -> dommage
	LOAD_BASIC_VERTEX_ATTRIB_POINTER()

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_texture.bind();
	m_texture.textUnit(m_shaderProgram, "tex0");
}

template <typename Type>
void Cube<Type>::update()
{
}

template <typename Type>
void Cube<Type>::render(const Math::Mat4<Type>& vp)
{
	GLuint mvpLocation = glGetUniformLocation(m_shaderProgram, "MVP");

	glBindVertexArray(m_vao);

	auto mvp = vp * transform.getMatrix();
	glUniformMatrix4fv(mvpLocation, 1, 0, mvp.data());

	m_texture.bind();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
