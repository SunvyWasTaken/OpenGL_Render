#pragma once

#include "PrimitiveUtils.h"
#include "Vertex.h"
#include "LowLevel_Renderer/Texture/Texture.h"
#include "Math/Transform.h"
#include "LowLevel_Renderer/Shader/Shader.h"

#include <glad/glad.h>
#include <array>

#include "LowLevel_Renderer/Materials/Material.h"

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
	void render(ContextRenderer& contextRenderer);

	Transform transform;

private:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
	GLuint m_shaderProgram;
	Shader* m_shaders;

	Material m_material;
};

template <typename Type>
Cube<Type>::Cube()
	: transform(Transform{}), m_vao(0), m_vbo(0), m_ebo(0), m_shaderProgram(0), m_shaders(nullptr), m_material(Material{})
{
	load();
}

template <typename Type>
Cube<Type>::~Cube()
{
	DELETE_BUFFER_WITH_ELEMENTS(m_shaders->program)

	if(m_shaders)
	{
		delete m_shaders;
		m_shaders = nullptr;
	}
}

template <typename Type>
void Cube<Type>::load()
{
	m_material = Material{
		Texture("Ressources\\mat_test_diffuse.png", GL_TEXTURE0),
		Texture("Ressources\\mat_test_specular.png", GL_TEXTURE1),
		32.f
	};

	std::array<vertex_type, 24> vertices = {
		//Front
		vertex_type({ -1.f,	-1.f,	 1.f }, { 1.0f,	0.0f,	0.0f }, {  0.0f,		0.0f }, { 0.f, 0.f, 1.f} ),
		vertex_type({ -1.f,	1.f,	 1.f }, { 1.0f,	0.0f,	0.0f }, {  0.0f,		1.0f }, { 0.f, 0.f, 1.f} ),
		vertex_type({  1.f,	1.f,	 1.f }, { 1.0f,	0.0f,	0.0f }, {  1.0f,		1.0f }, { 0.f, 0.f, 1.f} ),
		vertex_type({  1.f,	-1.f,	 1.f }, { 1.0f,	0.0f,	0.0f }, {  1.0f,		0.0f }, { 0.f, 0.f, 1.f} ),

		//Right
		vertex_type({ 1.f,		-1.f,	 1.f }, { 1.0f,	0.0f,	0.0f }, {  0.0f,		0.0f }, { 1.f, 0.f, 0.f} ),
		vertex_type({ 1.f,		1.f,	 1.f }, { 1.0f,	0.0f,	0.0f }, {  0.0f,		1.0f }, { 1.f, 0.f, 0.f} ),
		vertex_type({ 1.f,		1.f,	-1.f }, { 1.0f,	0.0f,	0.0f }, {  1.0f,		1.0f }, { 1.f, 0.f, 0.f} ),
		vertex_type({ 1.f,		-1.f,	-1.f }, { 1.0f,	0.0f,	0.0f }, {  1.0f,		0.0f }, { 1.f, 0.f, 0.f} ),

		//Back
		vertex_type({ -1.f,	-1.f,	-1.f }, { 1.0f,	0.0f,	0.0f }, {  0.0f,		0.0f }, { 0.f, 0.f, -1.f} ),
		vertex_type({ -1.f,	1.f,	-1.f }, { 1.0f,	0.0f,	0.0f }, {  0.0f,		1.0f }, { 0.f, 0.f, -1.f} ),
		vertex_type({  1.f,	1.f,	-1.f }, { 1.0f,	0.0f,	0.0f }, {  1.0f,		1.0f }, { 0.f, 0.f, -1.f} ),
		vertex_type({  1.f,	-1.f,	-1.f }, { 1.0f,	0.0f,	0.0f }, {  1.0f,		0.0f }, { 0.f, 0.f, -1.f} ),

		//Left
		vertex_type({ -1.f,	-1.f,	-1.f }, { 1.0f,	0.0f,	0.0f }, {  0.0f,		0.0f }, { -1.f, 0.f, 0.f} ),
		vertex_type({ -1.f,	1.f,	-1.f }, { 1.0f,	0.0f,	0.0f }, {  0.0f,		1.0f }, { -1.f, 0.f, 0.f} ),
		vertex_type({ -1.f,	1.f,	 1.f }, { 1.0f,	0.0f,	0.0f }, {  1.0f,		1.0f }, { -1.f, 0.f, 0.f} ),
		vertex_type({ -1.f,	-1.f,	 1.f }, { 1.0f,	0.0f,	0.0f }, {  1.0f,		0.0f }, { -1.f, 0.f, 0.f} ),

		//Top
		vertex_type({ -1.f,	1.f,	 1.f }, { 1.0f,	0.0f,	0.0f }, {  0.0f,		0.0f }, { 0.f, 1.f, 0.f} ),
		vertex_type({ -1.f,	1.f,	-1.f }, { 1.0f,	0.0f,	0.0f }, {  0.0f,		1.0f }, { 0.f, 1.f, 0.f} ),
		vertex_type({  1.f,	1.f,	-1.f }, { 1.0f,	0.0f,	0.0f }, {  1.0f,		1.0f }, { 0.f, 1.f, 0.f} ),
		vertex_type({  1.f,	1.f,	 1.f }, { 1.0f,	0.0f,	0.0f }, {  1.0f,		0.0f }, { 0.f, 1.f, 0.f} ),
																	
		vertex_type({ -1.f,	-1.f,	1.f },	{ 1.0f,	0.0f,	0.0f }, {  0.0f,		0.0f }, { 0.f, -1.f, 0.f} ),
		vertex_type({ -1.f,	-1.f,	-1.f }, { 1.0f,	0.0f,	0.0f }, {  0.0f,		1.0f }, { 0.f, -1.f, 0.f} ),
		vertex_type({  1.f,	-1.f,	-1.f }, { 1.0f,	0.0f,	0.0f }, {  1.0f,		1.0f }, { 0.f, -1.f, 0.f} ),
		vertex_type({  1.f,	-1.f,	 1.f }, { 1.0f,	0.0f,	0.0f }, {  1.0f,		0.0f }, { 0.f, -1.f, 0.f} )
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

template <typename Type>
void Cube<Type>::update()
{
}

template <typename Type>
void Cube<Type>::render(ContextRenderer& contextRenderer)
{
	glUseProgram(m_shaders->program);
	glBindVertexArray(m_vao);

	m_shaders->setMat4("projection", contextRenderer.projection);
	m_shaders->setMat4("view", contextRenderer.camera.getMatrixView());
	m_shaders->setMat4("model", transform.getMatrix());

	m_shaders->setVec3("viewPostion", contextRenderer.camera.transform.position);

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

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
