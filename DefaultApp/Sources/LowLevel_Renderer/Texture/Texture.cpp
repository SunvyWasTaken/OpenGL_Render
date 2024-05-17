#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include "Procedural/BaseTerrain/BaseTerrain.h"

#include <filesystem>
#include <stb_image.h>
//
//#define STBI_MSC_SECURE_CRT
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include <stb_image_write.h>

Texture::Texture()
	: m_imageData(nullptr)
	, m_textureSize(Point2i(0, 0))
	, numColCh(0)
	, m_texture(0)
{
}

Texture::Texture(const std::string& path, GLenum slot)
	: m_imageData(nullptr)
	, m_textureSize(Point2i(0, 0))
	, numColCh(0)
	, m_texture(0)
{
	Load(path);

	ConfigOpenGL(m_textureSize);

	Unload();
}

Texture::Texture(unsigned char* bytes, Point2i& textureSize, int NumColch)
	: m_imageData(bytes)
	, m_textureSize(textureSize)
	, numColCh(NumColch)
	, m_texture(0)
{
	//stbi_write_png("texture.png", m_textureSize.x, m_textureSize.y, numColCh, m_imageData, m_textureSize.x * numColCh);

	ConfigOpenGL(m_textureSize);

	Unload();
}

Texture::~Texture()
{
	Unload();
}

void Texture::Load(const std::string& path)
{
	stbi_set_flip_vertically_on_load(true);
	if (path.find(".jpg") != std::string::npos)
	{
		m_imageData = stbi_load(path.c_str(), &m_textureSize.x, &m_textureSize.y, &numColCh, STBI_rgb);
	}
	else
	{
		m_imageData = stbi_load(path.c_str(), &m_textureSize.x, &m_textureSize.y, &numColCh, STBI_rgb_alpha);
	}
	// Check if the image was load

	if (!m_imageData)
	{
		printf("Can't load texture from '%s' - %s\n", path.c_str(), stbi_failure_reason());
		exit(0);
	}
}

void Texture::Unload()
{
	if (m_imageData)
	{
		stbi_image_free(m_imageData);
	}
	m_imageData = nullptr;
}

Point3f Texture::GetColor(const Point2i& coord) const
{
	if (!m_imageData) {
		printf("%s:%d - trying to get the color but no texture was loaded\n", __FILE__, __LINE__);
		exit(0);
	}

	int WrappedX = coord.x % m_textureSize.x;
	int WrappedY = coord.y % m_textureSize.y;

	Point3f Color;

	unsigned char* p = m_imageData + (WrappedY * m_textureSize.x + WrappedX) * 3;
	Color.x = (float)p[0];
	Color.y = (float)p[1];
	Color.z = (float)p[2];

	return Color;
}

void Texture::textUnit(GLuint shaderProgram, const char* uniform, GLuint unit)
{
	GLuint textUni = glGetUniformLocation(shaderProgram, uniform);
	glUniform1f(textUni, unit);
}


void Texture::bind(GLuint slot)
{
	glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture::ConfigOpenGL(const Point2i& textureSize)
{
	//Generates an OpenGL texture object
	glGenTextures(1, &m_texture);

	//Assigns the texture to a texture unit
	//glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	//Configure the alogo that is used to make the image smaller or bigger
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Configure the way the texture repeats
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Assign the image to OpengGL Texture object
	if (numColCh == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureSize.x, textureSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_imageData);
	}
	if (numColCh == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureSize.x, textureSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, m_imageData);
	}
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}
