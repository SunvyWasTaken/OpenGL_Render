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
	void render(const ContextRenderer& contextRenderer);

	Transform transform;
	Math::Color<Type> color{1.0f,1.0f,1.0f,1.0f};
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

	std::array<vertex_type, 24> vertices = {
		vertex_type({ -1.f,	-1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		0.0f }),
		vertex_type({ -1.f,	1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		1.0f }),
		vertex_type({  1.f,	1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		1.0f }),
		vertex_type({  1.f,	-1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		0.0f }),

		vertex_type({ 1.f,		-1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		0.0f }),
		vertex_type({ 1.f,		1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		1.0f }),
		vertex_type({ 1.f,		1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		1.0f }),
		vertex_type({ 1.f,		-1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		0.0f }),

		vertex_type({ -1.f,	-1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		0.0f }),
		vertex_type({ -1.f,	1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		1.0f }),
		vertex_type({  1.f,	1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		1.0f }),
		vertex_type({  1.f,	-1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		0.0f }),

		vertex_type({ -1.f,	-1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		0.0f }),
		vertex_type({ -1.f,	1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		1.0f }),
		vertex_type({ -1.f,	1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		1.0f }),
		vertex_type({ -1.f,	-1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		0.0f }),

		vertex_type({ -1.f,	1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		0.0f }),
		vertex_type({ -1.f,	1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		1.0f }),
		vertex_type({  1.f,	1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		1.0f }),
		vertex_type({  1.f,	1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		0.0f }),

		vertex_type({ -1.f,	-1.f,	1.f },	{ 1.0f,	1.0f,	1.0f }, {  0.0f,		0.0f }),
		vertex_type({ -1.f,	-1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		1.0f }),
		vertex_type({  1.f,	-1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		1.0f }),
		vertex_type({  1.f,	-1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		0.0f })
	};

	std::array<GLuint, 36> indices = {
		0, 1, 2, //Front
		2, 3, 0,

		4, 5, 6, //Right
		6, 7, 4,

		8, 9, 10, //Back
		10, 11, 8,

		12, 13, 14, //Left
		14, 15, 12,

		16, 17, 18, //Top
		18, 19, 16,

		20, 21, 22, //Bottom
		22, 23, 20
	};

	LOAD_VERTEX_ARRAYS(m_vao)
	LOAD_ARRAY_BUFFER(m_vbo, vertices)
	LOAD_ELEMENT_ARRAY_BUFFER(m_ebo, indices)

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER,  "light.vert"},
		{GL_FRAGMENT_SHADER, "light.frag"},
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
void Cube<Type>::render(const ContextRenderer& contextRenderer)
{
	glUseProgram(m_shaderProgram);
	glBindVertexArray(m_vao);

	const GLuint projectionLocation = glGetUniformLocation(m_shaderProgram, "projection");
	glUniformMatrix4fv(projectionLocation, 1, 0, contextRenderer.projection.data());
	const GLuint viewLocation = glGetUniformLocation(m_shaderProgram, "view");
	glUniformMatrix4fv(viewLocation, 1, 0, contextRenderer.view.data());

	const GLuint modelLocation = glGetUniformLocation(m_shaderProgram, "model");
	glUniformMatrix4fv(modelLocation, 1, 0, transform.getMatrix().data());

	m_texture.bind();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
