#pragma once

#include "Texture.h"
#include "Procedural/BaseTerrain/BaseTerrain.h"

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

template <int numTexture>
class TextureGenerator final
{
public:
	TextureGenerator() = default;

	~TextureGenerator()
	{
		for (int i = numTexture; i > -1; --i)
		{
			delete m_textureTiles[i];
		}
	};

	void LoadTile(const std::string& Filename)
	{
		if (m_numTextureTiles >= numTexture)
		{
			return;
		}
		m_textureTiles[m_numTextureTiles] = new TextureTile();
		m_textureTiles[m_numTextureTiles]->Image.Load(Filename);
		m_numTextureTiles++;
	}

	// Oui pour le moment je fais une copie parce que c'est pas clean
	Texture* GenerateTexture(int TextureSize, BaseTerrain* pTerrain, float MinHeight, float MaxHeight)
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
					Point2i currentCoord{ x, y };
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

		Point2i CurrentTextureSize{ TextureSize, TextureSize };

		return new Texture(pTextureData, CurrentTextureSize, BPP);
	}

private:

	void CalculateTextureRegions(float MinHeight, float MaxHeight)
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

	float RegionPercent(int Tile, float Height)
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

	TextureTile* m_textureTiles[numTexture];
	int m_numTextureTiles = 0;
};
