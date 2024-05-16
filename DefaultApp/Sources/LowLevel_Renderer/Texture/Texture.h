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

	void operator=(const Texture& other);
	void operator=(Texture& other);

private:

	void ConfigOpenGL(const Point2i& textureSize);

	unsigned char* m_imageData;
	Point2i m_textureSize;
	int numColCh;

	GLuint m_texture;
};

struct TextureHeightDesc
{
	float Low = 0.0f;
	float Optimal = 0.0f;
	float High = 0.0f;

	void Print() const { printf("Low %f Optimal %f High %f", Low, Optimal, High); }
};

struct TextureTile final
{
	TextureHeightDesc HeightDesc;
	Texture Image;
};

class TextureGenerator final
{
public:
	TextureGenerator() = default;

	~TextureGenerator();

	void LoadTile(const std::string& Filename);

	// Oui pour le moment je fais une copie parce que c'est pas clean
	Texture* GenerateTexture(int TextureSize, class BaseTerrain* pTerrain, float MinHeight, float MaxHeight);

private:

	void CalculateTextureRegions(float MinHeight, float MaxHeight);
//
	float RegionPercent(int Tile, float Height);
//#ifndef MAX_TEXTURE_TILES
//#define MAX_TEXTURE_TILES 3
//#endif // !MAX_TEXTURE_TILES
//
	TextureTile* m_textureTiles[3];
	int m_numTextureTiles = 0;
};
