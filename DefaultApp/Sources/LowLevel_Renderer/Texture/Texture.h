#pragma once
#include <string>
#include <glad/glad.h>

class Texture
{
public:
	Texture() = default;
	Texture(const std::string& path, GLenum slot = GL_TEXTURE0);

	void textUnit(GLuint shaderProgram, const char* uniform, GLuint unit = 0);
	void bind(GLuint slot = GL_TEXTURE0);

private:
	GLuint m_texture;
};
