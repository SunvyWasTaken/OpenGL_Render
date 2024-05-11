#pragma once

#include "Vertex.h"
#include "LowLevel_Renderer/Shader/Shader.h"
#include "PrimitiveUtils.h"
#include "LowLevel_Renderer/Texture/Texture.h"
#include "Math/Matrix.h"
#include "Math/Transform.h"
#include "LowLevel_Renderer/Materials/Material.h"

#include <array>
#include <glad/glad.h>

template <typename T>
class Plane
{
	using vertex_type = Vertex<T>;

public:
	Plane()
		: transform(Math::Transform<T>()), m_vao(0), m_vbo(0), m_shaders(nullptr), m_texture(Texture{}), m_material(Material{})
	{
		load();
	}

	~Plane()
	{
		DELETE_BUFFER_WITH_ELEMENTS(m_shaders->program)

		if(m_shaders)
		{
			delete m_shaders;
			m_shaders = nullptr;
		}
	}

	void load()
	{
		m_material = Material{
			Texture("Ressources\\mat_test_diffuse.png", GL_TEXTURE0),
			Texture("Ressources\\mat_test_specular.png", GL_TEXTURE1),
			32.f
		};

		std::array<vertex_type, 4> vertices = {
			vertex_type( { -1.f,	0.0f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		0.0f }, { 0.f, 1.f, 0.f} ),
			vertex_type( { -1.f,	0.0f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		1.0f }, { 0.f, 1.f, 0.f}),
			vertex_type( { 1.f,	0.0f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		1.0f }, { 0.f, 1.f, 0.f}),
			vertex_type( { 1.f,	0.0f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		0.0f }, { 0.f, 1.f, 0.f})
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

		m_shaders = Shader::loadShader(shaders);
		glUseProgram(m_shaders->program);

		// /!\ Attention, ca marche que si t = float, -> dommage
		LOAD_BASIC_VERTEX_ATTRIB_POINTER()

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		m_material.diffuseMap.textUnit(m_shaders->program, "tex0");
		m_material.specularMap.textUnit(m_shaders->program, "tex1");
	}

	void render(ContextRenderer& contextRenderer)
	{
		glUseProgram(m_shaders->program);
		glBindVertexArray(m_vao);

		m_shaders->setMat4("projection", contextRenderer.projection);
		m_shaders->setMat4("view", contextRenderer.camera.getMatrixView());
		m_shaders->setMat4("model", transform.getMatrix());

		m_shaders->setVec3("viewPosition", contextRenderer.camera.transform.position);

		m_shaders->setFloat("material.shininess", m_material.shininess);

		contextRenderer.directionalLight.getUniform(m_shaders);
		//GLuint lightConstantLocation = glGetUniformLocation(m_shaders->program, "light.constant");
		//glUniform1f(lightConstantLocation, 1.f);
		//GLuint lightLinearLocation = glGetUniformLocation(m_shaders->program, "light.linear");
		//glUniform1f(lightLinearLocation, 0.09f);
		//GLuint lightQuadraticLocation = glGetUniformLocation (m_shaders->program, "light.quadratic");
		//glUniform1f(lightQuadraticLocation, 0.032f);

		m_material.diffuseMap.bind(GL_TEXTURE0);
		m_material.specularMap.bind(GL_TEXTURE1);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	}

	Math::Transform<T> transform;

private:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
	GLuint m_shaderProgram;
	Shader* m_shaders;
	Texture m_texture;
	Material m_material;
};
