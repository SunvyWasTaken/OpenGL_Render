#pragma once

#include "Triangle.h"

#include "Vertex.h"
#include "LowLevel_Renderer/Shader/Shader.h"
#include "LowLevel_Renderer/Primitive/PrimitiveUtils.h"

#include <array>
#include <glad/glad.h>

template <typename T>
class Triangle
{
public:
	using vertex_type = Vertex<T>;

	Triangle()
		: m_vao(0), m_vbo(0), m_shaderProgram(0)
	{
		load();
	}

	~Triangle()
	{
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
		glDeleteProgram(m_shaderProgram);
	}

	void load()
	{
		std::array<vertex_type, 3> vertices = {
			vertex_type{ { -0.5f,	-0.5f,	0.f }, { 1.f,	0.f,	0.f } },
			vertex_type{ {	0.0f,	0.5f,	0.f }, { 0.f,	1.f,	0.f } },
			vertex_type{ {	0.5f,	-0.5f,	0.f }, { 0.f,	0.f,	1.f } },
		};

		LOAD_VERTEX_ARRAYS(m_vao)
		LOAD_ARRAY_BUFFER(m_vbo, vertices, vertex_type)

		ShaderInfo shaders[] = {
			{GL_VERTEX_SHADER,  "default.vert"},
			{GL_FRAGMENT_SHADER, "default.frag"},
			{GL_NONE, nullptr}
		};

		m_shaderProgram = Shader::loadShader(shaders);
		glUseProgram(m_shaderProgram);

		// /!\ Attention, ca marche que si t = float, -> dommage
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_type), 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_type), reinterpret_cast<char*>(nullptr) + sizeof(vertex_type::m_point));
		glEnableVertexAttribArray(1);

		m_uniID = glGetUniformLocation(m_shaderProgram, "scale");
	}

	void render()
	{
		glBindVertexArray(m_vao);

		glUniform1f(m_uniID, 1.f);

		/*GLuint mvpLocation = glGetUniformLocation(m_program, "MVP");
		glUniformMatrix4fv(mvpLocation, 1, 0, MVP.data());*/

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

private:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_shaderProgram;
	GLuint m_uniID;
};
