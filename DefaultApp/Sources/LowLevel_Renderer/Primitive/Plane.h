#pragma once
#include <array>

#include "LowLevel_Renderer/Primitive/Vertex.h"
#include "LowLevel_Renderer/Shader/Shader.h"

#include <glad/glad.h>

#include "PrimitiveUtils.h"
#include "LowLevel_Renderer/Texture/Texture.h"

template <typename T>
class Plane
{
	using vertex_type = Vertex<T>;

public:
	Plane()
	: m_vao(0), m_vbo(0), m_shaderProgram(0)
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
		m_texture = Texture("Ressources\\r.png", GL_TEXTURE0);

		std::array<vertex_type, 4> vertices = {
			vertex_type( { -0.5f,	-0.5f,	0.f }, { 1.0f,	0.0f,	0.0f }, { -0.5f,	 -0.5f } ),
			vertex_type( { -0.5f,	0.5f,	0.f }, { 0.0f,	1.0f,	0.0f }, { -0.5f,	  0.5f } ),
			vertex_type( { 0.5f,	0.5f,	0.f }, { 0.8f,	0.3f,	1.0f }, {  0.5f,  0.5f } ),
			vertex_type( { 0.5f,	-0.5f,	0.f }, { 0.5f,	0.5f,	0.5f }, {  0.5f, -0.5f } )
		};

		std::array<GLuint, 6> indices = {
			0, 1, 2,
			2, 3, 0
		};


		LOAD_VERTEX_ARRAYS(m_vao)
		LOAD_ARRAY_BUFFER(m_vbo, vertices, vertex_type)
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

		m_uniID = glGetUniformLocation(m_shaderProgram, "scale");
		m_texture.bind();
		m_texture.textUnit(m_shaderProgram, "tex0");
	}

	void render()
	{
		glBindVertexArray(m_vao);

		glUniform1f(m_uniID, 1.f);

		/*GLuint mvpLocation = glGetUniformLocation(m_program, "MVP");
		glUniformMatrix4fv(mvpLocation, 1, 0, MVP.data());*/

		//glDrawArrays(GL_TRIANGLES, 0, (int)(m_points.size()));

		m_texture.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

private:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
	GLuint m_shaderProgram;
	GLuint m_uniID;
	Texture m_texture;
};
