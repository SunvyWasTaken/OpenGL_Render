#pragma once

#include "LowLevel_Renderer/Primitive/Vertex.h"
#include "LowLevel_Renderer/Shader/Shader.h"
#include "PrimitiveUtils.h"
#include "LowLevel_Renderer/Texture/Texture.h"
#include "Math/Matrix.h"
#include "Math/Transform.h"

#include <array>
#include <glad/glad.h>

template <typename T>
class Plane
{
	using vertex_type = Vertex<T>;

public:
	Plane()
		: transform(Math::Transform<T>()), m_vao(0), m_vbo(0), m_shaderProgram(0), m_texture(Texture{})
	{
		load();
	}

	~Plane()
	{
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
		glDeleteBuffers(1, &m_ebo);
		glDeleteProgram(m_shaderProgram);
	}

	void load()
	{
		m_texture = Texture("Ressources\\sc.png", GL_TEXTURE0);

		std::array<vertex_type, 4> vertices = {
			vertex_type( { -0.9f,	-0.9f,	0.0f }, { 1.0f,	0.0f,	0.0f }, {  0.0f,		0.0f } ),
			vertex_type( { -0.9f,	0.9f,	0.0f }, { 0.0f,	1.0f,	0.0f }, {  0.0f,		1.0f } ),
			vertex_type( { 0.9f,	0.9f,	0.0f }, { 0.8f,	0.3f,	1.0f }, {  1.0f,		1.0f } ),
			vertex_type( { 0.9f,	-0.9f,	0.0f }, { 0.5f,	0.5f,	0.5f }, {  1.0f,		0.0f } )
		};

		std::array<GLuint, 6> indices = {
			0, 1, 2,
			2, 3, 0
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

	void render(const Math::Mat4<T>& vp)
	{
		GLuint mvpLocation = glGetUniformLocation(m_shaderProgram, "MVP");

		glUseProgram(m_shaderProgram);
		glBindVertexArray(m_vao);

		auto mvp = vp * transform.getMatrix();
		glUniformMatrix4fv(mvpLocation, 1, 0, mvp.data());

		m_texture.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void update()
	{
		angle = 0.0025f;
	}

	float angle = 0.f;

	Math::Transform<T> transform;

private:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
	GLuint m_shaderProgram;
	Texture m_texture;
};
