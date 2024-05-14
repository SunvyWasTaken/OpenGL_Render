#pragma once

#include "PrimitiveUtils.h"
#include "Vertex.h"
#include "Math/Transform.h"
#include "LowLevel_Renderer/Shader/Shader.h"
#include "Math/Matrix.h"

#include <glad/glad.h>
#include <array>
#include <string>
#include <stdexcept>
#include <stb_image.h>

template <typename Type>
class SkyBox
{
	using vertex_type = Vertex<Type>;
	using Transform = Math::Transform<Type>;

public:
	SkyBox();
	~SkyBox();

	void load();
	void update();
	void render(ContextRenderer& contextRenderer);

	Transform transform;
private:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
	GLuint m_shaderProgram;
	Shader* m_shader;
	std::string m_skyBoxImagesPath;
	GLuint m_texture;
};

template <typename Type>
SkyBox<Type>::SkyBox()
	: transform(Transform{}), m_vao(0), m_vbo(0), m_ebo(0), m_shaderProgram(0), m_shader(nullptr), m_skyBoxImagesPath("")
{
	load();
}

template <typename Type>
SkyBox<Type>::~SkyBox()
{
	DELETE_BUFFER_WITH_ELEMENTS(m_shader->program)

	if(m_shader)
	{
		delete m_shader;
		m_shader = nullptr;
	}
}

template <typename Type>
void SkyBox<Type>::load()
{
	std::array<vertex_type, 24> vertices = {
		vertex_type({ -1.f,	-1.f,	 1.f }, { 1.0f,	0.0f,	0.0f }, {  0.0f,		0.0f }),
		vertex_type({ -1.f,	1.f,	 1.f }, { 1.0f,	0.0f,	0.0f }, {  0.0f,		1.0f }),
		vertex_type({  1.f,	1.f,	 1.f }, { 1.0f,	0.0f,	0.0f }, {  1.0f,		1.0f }),
		vertex_type({  1.f,	-1.f,	 1.f }, { 1.0f,	0.0f,	0.0f }, {  1.0f,		0.0f }),

		vertex_type({ 1.f,		-1.f,	-1.f }, { 0.0f,	1.0f,	0.0f }, {  0.0f,		0.0f }),
		vertex_type({ 1.f,		1.f,	-1.f }, { 0.0f,	1.0f,	0.0f }, {  0.0f,		1.0f }),
		vertex_type({ 1.f,		1.f,	 1.f }, { 0.0f,	1.0f,	0.0f }, {  1.0f,		1.0f }),
		vertex_type({ 1.f,		-1.f,	 1.f }, { 0.0f,	1.0f,	0.0f }, {  1.0f,		0.0f }),

		vertex_type({ -1.f,	-1.f,	-1.f }, { 1.0f,	0.5f,	0.0f }, {  0.0f,		0.0f }),
		vertex_type({ -1.f,	1.f,	-1.f }, { 1.0f,	0.5f,	0.0f }, {  0.0f,		1.0f }),
		vertex_type({  1.f,	1.f,	-1.f }, { 1.0f,	0.5f,	0.0f }, {  1.0f,		1.0f }),
		vertex_type({  1.f,	-1.f,	-1.f }, { 1.0f,	0.5f,	0.0f }, {  1.0f,		0.0f }),

		vertex_type({ -1.f,	-1.f,	-1.f }, { 0.0f,	0.0f,	1.0f }, {  0.0f,		0.0f }),
		vertex_type({ -1.f,	1.f,	-1.f }, { 0.0f,	0.0f,	1.0f }, {  0.0f,		1.0f }),
		vertex_type({ -1.f,	1.f,	 1.f }, { 0.0f,	0.0f,	1.0f }, {  1.0f,		1.0f }),
		vertex_type({ -1.f,	-1.f,	 1.f }, { 0.0f,	0.0f,	1.0f }, {  1.0f,		0.0f }),

		vertex_type({ -1.f,	1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		0.0f }),
		vertex_type({ -1.f,	1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		1.0f }),
		vertex_type({  1.f,	1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		1.0f }),
		vertex_type({  1.f,	1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		0.0f }),

		vertex_type({ -1.f,	-1.f,	1.f },	{ 1.0f,	1.0f,	0.0f }, {  0.0f,		0.0f }),
		vertex_type({ -1.f,	-1.f,	-1.f }, { 1.0f,	1.0f,	0.0f }, {  0.0f,		1.0f }),
		vertex_type({  1.f,	-1.f,	-1.f }, { 1.0f,	1.0f,	0.0f }, {  1.0f,		1.0f }),
		vertex_type({  1.f,	-1.f,	 1.f }, { 1.0f,	1.0f,	0.0f }, {  1.0f,		0.0f })
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

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);

	m_skyBoxImagesPath = "Ressources\\SkyBox\\";

	std::vector<std::string> SkyBoxImages = {
		"right.png",
		"left.png",
		"top.png",
		"bottom.png",
		"front.png",
		"back.png"
	};

	int widthImage, heightImage, numColCh;
	for (size_t i = 0; i < SkyBoxImages.size(); ++i) {
		std::string completePath = m_skyBoxImagesPath + SkyBoxImages[i];
		unsigned char* bytes = stbi_load(completePath.c_str(), &widthImage, &heightImage, &numColCh, 0);
		if (bytes) {
			//GL_TEXTURE_CUBE_MAP_POSITIVE_X + i : will iterate in this order : Right, Left, Top, Bottom, Back, Front
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
			stbi_image_free(bytes);
		}
		else {
			std::runtime_error("Could not load skybox image : " + m_skyBoxImagesPath + SkyBoxImages[i]);
			stbi_image_free(bytes);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	LOAD_VERTEX_ARRAYS(m_vao)
	LOAD_ARRAY_BUFFER(m_vbo, vertices)
	LOAD_ELEMENT_ARRAY_BUFFER(m_ebo, indices)

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER,  "skybox.vert"},
		{GL_FRAGMENT_SHADER, "skybox.frag"},
		{GL_NONE, nullptr}
	};

	m_shader = Shader::loadShader(shaders);
	glUseProgram(m_shader->program);

	// /!\ Attention, ca marche que si t = float, -> dommage
	LOAD_BASIC_VERTEX_ATTRIB_POINTER()

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//m_texture.bind();
	//m_texture.textUnit(m_shaderProgram, "tex0");

	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
}

template <typename Type>
void SkyBox<Type>::update()
{
}

template <typename Type>
void SkyBox<Type>::render(ContextRenderer& contextRenderer)
{
	glEnable(GL_TEXTURE_CUBE_MAP);
	glDisable(GL_LIGHTING);
	glDepthMask(GL_FALSE);

	glUseProgram(m_shader->program);
	glBindVertexArray(m_vao);

	m_shader->setMat4("projection", contextRenderer.projection);
	m_shader->setMat4("view", contextRenderer.camera.getMatrixView());
	m_shader->setMat4("model", transform.getMatrix());

	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glDepthMask(GL_TRUE);
	glDisable(GL_TEXTURE_CUBE_MAP);
	glEnable(GL_LIGHTING);
}
