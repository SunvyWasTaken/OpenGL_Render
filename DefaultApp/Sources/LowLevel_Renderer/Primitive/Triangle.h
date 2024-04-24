#pragma once

#include "Triangle.h"

#include "Vertex.h"
#include "LowLevel_Renderer/Shader/Shader.h"
#include "LowLevel_Renderer/Primitive/PrimitiveUtils.h"

#include <array>
#include <glad/glad.h>

#include "Shape.h"

template <typename T>
class Triangle : public Shape<T>
{
public:
	using vertex_type = Vertex<T>;

	Triangle()
		: Shape<T>()
	{
		Triangle::load();
	}

	~Triangle() override
	{
		
	}

	void load() override
	{
		m_texture = Texture("Ressources\\sc.png", GL_TEXTURE0);

		std::array<vertex_type, 3> vertices = {
			vertex_type( { -0.5f,	-0.5f,	0.f }, { 1.f,	0.f,	0.f }, { 0.0f, 0.0f } ),
			vertex_type( {	0.0f,	0.5f,	0.f }, { 0.f,	1.f,	0.f }, { 0.5f, 1.0f } ),
			vertex_type( {	0.5f,	-0.5f,	0.f }, { 0.f,	0.f,	1.f }, { 1.0f, 0.0f } ),
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
		/*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_type), 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_type), reinterpret_cast<char*>(nullptr) + sizeof(vertex_type::m_point));
		glEnableVertexAttribArray(1)*/;
		LOAD_BASIC_VERTEX_ATTRIB_POINTER()

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		m_texture.bind();
		m_texture.textUnit(m_shaderProgram, "tex0");
	}

	void render(const Math::Mat4<T>& vp) override
	{
		GLuint mvpLocation = glGetUniformLocation(m_shaderProgram, "MVP");

		glBindVertexArray(m_vao);

		auto mvp = vp * transform.getMatrix();
		glUniformMatrix4fv(mvpLocation, 1, 0, mvp.data());

		m_texture.bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	Math::Transform<T> transform;

private:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_shaderProgram;
	Texture m_texture;
};
