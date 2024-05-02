#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"

#include <filesystem>
#include <stb_image.h>

Texture::Texture(const std::string& path, GLenum slot)
	: m_texture(0)
{
	int widthImage, heightImage, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(path.c_str(), &widthImage, &heightImage, &numColCh, STBI_rgb_alpha);

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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Delete the image data as it is already in the OpenGL Texture object
	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);
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
