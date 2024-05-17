#pragma once

#include "Math/Point.h"

#include <string>
#include <glad/glad.h>

class Texture
{
public:
	Texture();

	Texture(const std::string& path, GLenum slot = GL_TEXTURE0);

	Texture(unsigned char* bytes, Point2i& textureSize, int NumColch);

	~Texture();

	void Load(const std::string& path);

	//Delete the image data as it is already in the OpenGL Texture object
	void Unload();

	Point3f GetColor(const Point2i& coord) const;

	void textUnit(GLuint shaderProgram, const char* uniform, GLuint unit = 0);
	void bind(GLuint slot = GL_TEXTURE0);

private:

	void ConfigOpenGL(const Point2i& textureSize);

	unsigned char* m_imageData;
	Point2i m_textureSize;
	int numColCh;

	GLuint m_texture;
};
