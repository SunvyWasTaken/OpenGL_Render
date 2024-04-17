#pragma once
#include "LowLevel_Renderer/Primitive/Vertex.h"
#include "LowLevel_Renderer/Shader/Shader.h"

#include <array>
#include <glad/glad.h>

template <typename T>
class Plane
{
	using vertex_type = Vertex<T>;

public:
	Plane(const std::array<vertex_type, 4>& points, const std::array<GLuint, 6>& indices)
		: m_points(points), m_vao(0), m_vbo(0), m_shaderProgram(0), m_indices(indices)
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
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(m_points), m_points.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &m_ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices.data(), GL_STATIC_DRAW);

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

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		m_uniID = glGetUniformLocation(m_shaderProgram, "scale");
	}

	void render()
	{
		glBindVertexArray(m_vao);

		glUniform1f(m_uniID, 1.f);

		/*GLuint mvpLocation = glGetUniformLocation(m_program, "MVP");
		glUniformMatrix4fv(mvpLocation, 1, 0, MVP.data());*/

		//glDrawArrays(GL_TRIANGLES, 0, (int)(m_points.size()));
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	}

private:
	std::array<vertex_type, 4> m_points;
	std::array<GLuint, 6> m_indices;
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
	GLuint m_shaderProgram;
	GLuint m_uniID;
};
