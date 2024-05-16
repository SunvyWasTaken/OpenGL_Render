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
#include <algorithm>

template <typename T>
class Water
{
	using vertex_type = Vertex<T>;

public:
	Water(int WindowWidth, int WindowHeight, Math::Point2D<int> ReflectionResolution, Math::Point2D<int> RefractionResolution)
		: m_windowSize({WindowWidth,WindowHeight}), transform(Math::Transform<T>()), m_vao(0), m_vbo(0), m_shaders(nullptr), m_material(Material{})
		, m_reflectionResolution(ReflectionResolution), m_refractionResolution(RefractionResolution)
	{
		

		m_reflectionFrameBuffer = CreateFrameBuffer();
		m_reflectionTexture = CreateTextureAttachment(m_reflectionResolution.x, m_reflectionResolution.y);
		//m_reflectionDepthBuffer = CreateDepthBufferAttachment(m_reflectionResolution.x, m_reflectionResolution.y);
		UnbindCurrentFrameBuffer();

		m_refractionFrameBuffer = CreateFrameBuffer();
		m_refractionTexture = CreateTextureAttachment(m_refractionResolution.x, m_refractionResolution.y);;
		m_refractionDepthTexture = CreateDepthTextureAttachment(m_refractionResolution.x, m_refractionResolution.y);
		UnbindCurrentFrameBuffer();

		

		load();
	}

	~Water()
	{
		DELETE_BUFFER_WITH_ELEMENTS(m_shaders->program)

		if(m_shaders)
		{
			delete m_shaders;
			m_shaders = nullptr;
		}

		glDeleteFramebuffers(1,&m_reflectionFrameBuffer);
		glDeleteTextures(1,&m_reflectionTexture);
		glDeleteRenderbuffers(1,&m_reflectionDepthBuffer);
		glDeleteFramebuffers(1,&m_refractionFrameBuffer);
		glDeleteTextures(1,&m_refractionTexture);
		glDeleteTextures(1,&m_refractionDepthTexture);
	}

	GLuint CreateFrameBuffer() {
		GLuint frameBuffer;
		glGenFramebuffers(1, &frameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		//glDrawBuffer(GL_COLOR_ATTACHMENT0);
		
		return frameBuffer;
	}

	void BindFrameBuffer(GLuint FrameBuffer, GLuint Texture, int Width, int Height) {
		glBindTexture(GL_TEXTURE_2D, Texture);
		glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
		glViewport(0, 0, Width, Height);
	}

	GLuint CreateTextureAttachment(int Width, int Height) {
		
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, texture,0);
		glBindTexture(GL_TEXTURE_2D, 0);

		return texture;
	}

	GLuint CreateDepthBufferAttachment(int Width, int Height) {
		GLuint depthBuffer;
		glGenRenderbuffers(1, &depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Width, Height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

		return depthBuffer;
	}

	GLuint CreateDepthTextureAttachment(int Width, int Height) {
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, Width, Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);

		return texture;
	}

	void BindReflectionFrameBuffer() {
		BindFrameBuffer(m_reflectionFrameBuffer, m_reflectionTexture, m_reflectionResolution.x, m_reflectionResolution.y);
	}

	void BindRefractionFrameBuffer() {
		BindFrameBuffer(m_refractionFrameBuffer, m_refractionTexture, m_refractionResolution.x, m_refractionResolution.y);
	}

	//Switch to default frame buffer
	void UnbindCurrentFrameBuffer() {
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, m_windowSize.x, m_windowSize.y);
	}

	void load()
	{

		std::array<vertex_type, 4> vertices = {
			vertex_type( { -1.f,	0.0f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		0.0f }, { 0.f, 1.f, 0.f} ),
			vertex_type( { -1.f,	0.0f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		1.0f }, { 0.f, 1.f, 0.f}),
			vertex_type( { 1.f,	0.0f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		1.0f }, { 0.f, 1.f, 0.f}),
			vertex_type( { 1.f,	0.0f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		0.0f }, { 0.f, 1.f, 0.f})
		};

		std::array<GLuint, 6> indices = {
			//0, 1, 2,
			//2, 3, 0
			2,1,0,
			0,3,2
		};

		LOAD_VERTEX_ARRAYS(m_vao)
		LOAD_ARRAY_BUFFER(m_vbo, vertices)
		LOAD_ELEMENT_ARRAY_BUFFER(m_ebo, indices)

		std::vector<ShaderInfo> shaders = {
			{GL_VERTEX_SHADER,  "water.vert"},
			{GL_FRAGMENT_SHADER, "water.frag"}
		};

		m_shaders = Shader::loadShader(shaders);
		glUseProgram(m_shaders->program);

		// /!\ Attention, ca marche que si t = float, -> dommage
		LOAD_BASIC_VERTEX_ATTRIB_POINTER()

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		
	}

	void render(ContextRenderer& contextRenderer)
	{
		m_dudvMap = Texture("Ressources\\water_dudv.png", GL_TEXTURE2);

		glUseProgram(m_shaders->program);
		glBindVertexArray(m_vao);

		m_shaders->setMat4("projection", contextRenderer.projection);
		m_shaders->setMat4("view", contextRenderer.camera.getMatrixView());
		m_shaders->setMat4("model", transform.getMatrix());

		m_shaders->setVec3("viewPosition", contextRenderer.camera.transform.position);

		contextRenderer.directionalLight.getUniform(m_shaders);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_reflectionTexture);

		//GLuint reflTextUni = glGetUniformLocation((m_shaders->program), "reflectionText");
		//glUniform1f(reflTextUni, m_reflectionTexture);

		m_shaders->setFloat("reflectionText", m_reflectionTexture);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_refractionTexture);

		//GLuint refrTextUni = glGetUniformLocation((m_shaders->program), "refractionText");
		//glUniform1f(refrTextUni, m_refractionTexture);

		m_shaders->setFloat("refractionText", m_refractionTexture);

		m_dudvMap.bind(GL_TEXTURE2);
		m_shaders->setFloat("dudvMap", m_dudvMap.GetTexture());

		m_shaders->setFloat("moveFactor", m_moveFactor);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void UpdateWaveMovement(float deltaTime) {
		m_moveFactor += m_waveSpeed * deltaTime;
		
		if (m_moveFactor > 1.f) {
			m_moveFactor -= 1.f;
		}
	}

	Math::Transform<T> transform;

private:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
	GLuint m_shaderProgram;
	Shader* m_shaders;
	Material m_material;

	Math::Point2D<int> m_windowSize;
	Math::Point2D<int> m_reflectionResolution;
	Math::Point2D<int> m_refractionResolution;

	GLuint m_reflectionFrameBuffer;
	GLuint m_reflectionTexture;
	GLuint m_reflectionDepthBuffer;
	GLuint m_refractionFrameBuffer;
	GLuint m_refractionTexture;
	GLuint m_refractionDepthTexture;

	Texture m_dudvMap;

	T m_waveSpeed = 0.03f;
	T m_moveFactor = 0.f;
};
