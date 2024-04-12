#pragma once

#include "Vertex.h"
#include "LowLevel_Renderer/Shader/Shader.h"

#include <array>
#include <fstream>
#include <glad/glad.h>

#include "Triangle.h"

template <typename T>
class Triangle
{
public:
	using vertex_type = Vertex<T>;

	Triangle(const vertex_type& p0, const vertex_type& p1, const vertex_type& p2)
		: m_points{ p0, p1, p2 }, m_vao(0), m_vbo(0), m_shaderProgram(0)
	{
		load();
	}

	~Triangle()
	{
	}

	void load()
	{
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(m_points), m_points.data(), GL_STATIC_DRAW);

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
	}

	void render()
	{
		glBindVertexArray(m_vao);

		/*GLuint mvpLocation = glGetUniformLocation(m_program, "MVP");
		glUniformMatrix4fv(mvpLocation, 1, 0, MVP.data());*/

		glDrawArrays(GL_TRIANGLES, 0, (int)(m_points.size()));
	}

private:
	std::array<vertex_type, 3> m_points;
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_shaderProgram;
};
