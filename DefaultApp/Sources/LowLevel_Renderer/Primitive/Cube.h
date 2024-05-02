#pragma once

#include "PrimitiveUtils.h"
#include "Vertex.h"
#include "LowLevel_Renderer/Texture/Texture.h"
#include "Math/Transform.h"
#include "LowLevel_Renderer/Shader/Shader.h"
#include "Math/Matrix.h"

#include <glad/glad.h>
#include <array>
#include <cmath>

template <typename Type>
class Cube
{
	using vertex_type = Vertex<Type>;
	using Transform = Math::Transform<Type>;

public:
	Cube(const std::string& st);
	~Cube();

	void load();
	void update();
	void render(const ContextRenderer& contextRenderer, Cube<Type>& light, Camera& camera);

	Transform transform;
	Math::Color<Type> color{1.f,1.0f,1.0f};

	std::string shaderType;
	bool li = false;
private:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
	GLuint m_shaderProgram;
	Texture m_texture;
};

template <typename Type>
Cube<Type>::Cube(const std::string& st)
	: transform(Transform{}), m_vao(0), m_vbo(0), m_ebo(0), m_shaderProgram(0), m_texture(Texture{}), shaderType(st)
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

	std::string vert = shaderType + ".vert";
	std::string frag = shaderType + ".frag";

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER,  vert.c_str()},
		{GL_FRAGMENT_SHADER, frag.c_str()},
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
void Cube<Type>::render(const ContextRenderer& contextRenderer, Cube<Type>& light, Camera& camera)
{
	glUseProgram(m_shaderProgram);
	glBindVertexArray(m_vao);

	Math::Color<Type> lightColorU{};
	lightColorU.r = std::sin(glfwGetTime() * 2.f);
	lightColorU.g = sin(glfwGetTime() * 0.7f);
	lightColorU.b = sin(glfwGetTime() * 1.3f);
	Math::Color<Type> diffuseColor{};
	diffuseColor.r = lightColorU.a * 0.5f;
	diffuseColor.g = lightColorU.g * 0.5f;
	diffuseColor.b = lightColorU.b * 0.5f;
	Math::Color<Type> ambientColor{};
	diffuseColor.r = lightColorU.a * 0.5f;
	diffuseColor.g = lightColorU.g * 0.5f;
	diffuseColor.b = lightColorU.b * 0.5f;

	GLuint projectionLocation = glGetUniformLocation(m_shaderProgram, "projection");
	glUniformMatrix4fv(projectionLocation, 1, 0, contextRenderer.projection.data());
	GLuint viewLocation = glGetUniformLocation(m_shaderProgram, "view");
	glUniformMatrix4fv(viewLocation, 1, 0, camera.getMatrixView().data());

	GLuint modelLocation = glGetUniformLocation(m_shaderProgram, "model");
	glUniformMatrix4fv(modelLocation, 1, 0, transform.getMatrix().data());
	
	GLuint lightColorLocation = glGetUniformLocation(m_shaderProgram, "lightColor");
	glUniform4fv(lightColorLocation, 1, reinterpret_cast<float*>(&light.color));

	GLuint lightPositionLocation = glGetUniformLocation(m_shaderProgram, "lightPosition");
	glUniform3fv(lightPositionLocation, 1, reinterpret_cast<float*>(&light.transform.position));

	GLuint CameraPositionLocation = glGetUniformLocation(m_shaderProgram, "viewPosition");
	glUniform3fv(CameraPositionLocation, 1, reinterpret_cast<float*>(&camera.transform.position));


	GLuint materialAmbientLocation = glGetUniformLocation(m_shaderProgram, "material.ambient");
	glUniform3f(materialAmbientLocation, 1.0f, 0.5f, 0.31f);

	GLuint materialDiffuseLocation = glGetUniformLocation(m_shaderProgram, "material.diffuse");
	glUniform3f(materialDiffuseLocation, 1.0f, 0.5f, 0.31f);

	GLuint materialSpecularLocation = glGetUniformLocation(m_shaderProgram, "material.specular");
	glUniform3f(materialSpecularLocation, 0.5f, 0.5f, 0.5f);

	GLuint materialShininessLocation = glGetUniformLocation(m_shaderProgram, "material.shininess");
	glUniform1f(materialShininessLocation, 32.f);

	GLuint lightAmbientLocation = glGetUniformLocation(m_shaderProgram, "light.ambient");
	glUniform3fv(lightAmbientLocation, 1, reinterpret_cast<float*>(&ambientColor));
	GLuint lightDiffuseLocation = glGetUniformLocation(m_shaderProgram, "light.diffuse");
	glUniform3fv(lightDiffuseLocation, 1, reinterpret_cast<float*>(&diffuseColor));
	GLuint lightSpecularLocation = glGetUniformLocation(m_shaderProgram, "light.specular");
	glUniform3f(lightSpecularLocation, 1.f, 1.f, 1.f);

	m_texture.bind();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
