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

	//Unload();
}

Texture::Texture(unsigned char* bytes, Point2i& textureSize, int NumColch)
	: m_imageData(bytes)
	, m_textureSize(textureSize)
	, numColCh(NumColch)
	, m_texture(0)
{
	//stbi_write_png("texture.png", m_textureSize.x, m_textureSize.y, numColCh, m_imageData, m_textureSize.x * numColCh);

	ConfigOpenGL(m_textureSize);
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
	m_imageData = NULL;
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

void Texture::operator=(const Texture& other)
{
	m_imageData = nullptr;
	m_textureSize = other.m_textureSize;
	numColCh = other.numColCh;
	m_texture = other.m_texture;
}

void Texture::operator=(Texture& other)
{
	m_imageData = nullptr;
	m_textureSize = other.m_textureSize;
	numColCh = other.numColCh;
	m_texture = other.m_texture;
}

const GLuint Texture::GetTexture() const
{
	return m_texture;
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

TextureGenerator::~TextureGenerator()
{
	for (int i = 2; i > -1; --i)
	{
		delete m_textureTiles[i];
	}
}

void TextureGenerator::LoadTile(const std::string& Filename)
{
	if (m_numTextureTiles >= 3)
	{
		return;
	}
	m_textureTiles[m_numTextureTiles] = new TextureTile();
	m_textureTiles[m_numTextureTiles]->Image.Load(Filename);
	m_numTextureTiles++;
}

Texture TextureGenerator::GenerateTexture(int TextureSize, BaseTerrain* pTerrain, float MinHeight, float MaxHeight)
{
	if (m_numTextureTiles == 0) {
		printf("%s:%d: no texture tiles loaded\n", __FILE__, __LINE__);
		exit(0);
	}

	CalculateTextureRegions(MinHeight, MaxHeight);

	int BPP = 3;
	int TextureBytes = TextureSize * TextureSize * BPP;
	unsigned char* pTextureData = new unsigned char[TextureBytes];
	unsigned char* pixel = pTextureData;

	float HeightMapToTextureRatio = (float)pTerrain->GetTerrainSize() / (float)TextureSize;

	printf("Height map to texture ratio: %f\n", HeightMapToTextureRatio);

	for (int y = 0; y < TextureSize; ++y)
	{
		for (int x = 0; x < TextureSize; ++x)
		{

			float InterpolatedHeight = pTerrain->GetHeightInterpolated((float)x * HeightMapToTextureRatio,
				(float)y * HeightMapToTextureRatio);

			float Red = 0.0f;
			float Green = 0.0f;
			float Blue = 0.0f;

			for (int Tile = 0; Tile < m_numTextureTiles; Tile++)
			{
				Point2i currentCoord{x, y};
				Point3f Color = m_textureTiles[Tile]->Image.GetColor(currentCoord);

				float BlendFactor = RegionPercent(Tile, InterpolatedHeight);

				Red += BlendFactor * Color.x;
				Green += BlendFactor * Color.y;
				Blue += BlendFactor * Color.z;
			}

			if (Red > 255.0f || Green > 255.0f || Blue > 255.0f) {
				printf("%d:%d: %f %f %f\n", y, x, Red, Green, Blue);
				exit(0);
			}

			pixel[0] = (unsigned char)Red;
			pixel[1] = (unsigned char)Green;
			pixel[2] = (unsigned char)Blue;

			pixel += BPP;
		}
	}

	// TODO : ici à changer pour que la texture reste en mémoire et après penser à la delete lorsque c'est détruit.

	Point2i CurrentTextureSize{TextureSize, TextureSize};
	Texture CurrentTexture = Texture(pTextureData, CurrentTextureSize, BPP);

	//free(pTextureData);

	//pTexture->LoadRaw(TextureSize, TextureSize, BPP, pTextureData);
	return CurrentTexture;
}

void TextureGenerator::CalculateTextureRegions(float MinHeight, float MaxHeight)
{
	float HeightRange = MaxHeight - MinHeight;

	float RangePerTile = HeightRange / m_numTextureTiles;
	float Remainder = HeightRange - RangePerTile * m_numTextureTiles;

	if (Remainder < 0.0f)
	{
		printf("%s:%d: negative remainder %f (num tiles %d range per tile %f)\n", __FILE__, __LINE__, Remainder, m_numTextureTiles, RangePerTile);
		exit(0);
	}

	float LastHeight = -1.0f;

	for (int i = 0; i < m_numTextureTiles; i++)
	{
		m_textureTiles[i]->HeightDesc.Low = LastHeight + 1;
		LastHeight += RangePerTile;
		m_textureTiles[i]->HeightDesc.Optimal = LastHeight;
		m_textureTiles[i]->HeightDesc.High = m_textureTiles[i]->HeightDesc.Optimal + RangePerTile;

		m_textureTiles[i]->HeightDesc.Print(); printf("\n");
	}
}

float TextureGenerator::RegionPercent(int Tile, float Height)
{
	float Percent = 0.0f;

	if (Height < m_textureTiles[Tile]->HeightDesc.Low) {
		Percent = 0.0f;
	}
	else if (Height > m_textureTiles[Tile]->HeightDesc.High) {
		Percent = 0.0f;
	}
	else if (Height < m_textureTiles[Tile]->HeightDesc.Optimal) {
		float Nom = (float)Height - (float)m_textureTiles[Tile]->HeightDesc.Low;
		float Denom = (float)m_textureTiles[Tile]->HeightDesc.Optimal - (float)m_textureTiles[Tile]->HeightDesc.Low;
		Percent = Nom / Denom;
	}
	else if (Height >= m_textureTiles[Tile]->HeightDesc.Optimal) {
		float Nom = (float)m_textureTiles[Tile]->HeightDesc.High - (float)Height;
		float Denom = (float)m_textureTiles[Tile]->HeightDesc.High - (float)m_textureTiles[Tile]->HeightDesc.Optimal;
		Percent = Nom / Denom;
	}
	else {
		printf("%s:%d - shouldn't get here! tile %d Height %f\n", __FILE__, __LINE__, Tile, Height);
		exit(0);
	}

	if ((Percent < 0.0f) || (Percent > 1.0f)) {
		printf("%s:%d - Invalid percent %f\n", __FILE__, __LINE__, Percent);
		exit(0);
	}

	return Percent;
}
