#pragma once

#include "Core/ProceduralGeneration.h"
#include "LowLevel_Renderer/Primitive/TriangleList.h"
#include "Math/Array2D.h"
#include "Math/Transform.h"

struct ContextRenderer;

using FTransform = Math::Transform<float>;

class BaseTerrain
{
public:
	BaseTerrain();

	virtual ~BaseTerrain();

	void InitTerrain(const int terrainSize);

	void InitTerrainWithMethode(const int terrainSize, int Methode);

	void Destroy();

	void Render(ContextRenderer& contextRenderer); 

	template <typename type, typename... Args>
	void GenerateProceduralTerrain(Args... args)
	{
		type* currMethode = std::get_if<type>(&m_GenerationMethode);
		if (!currMethode)
		{
			return;
		}
		currMethode->GenerationMethode(args...);

		m_triangleList.Destroy();

		m_triangleList.CreateTriangleList(m_terrainSize, m_terrainSize, this);
	}

	void SetGenMethode(const int index);

	int GetMethodeIndex() const { return m_currentIndeMethode; }

	int GetTerrainSize() const { return m_terrainSize; }

	float GetHeight(int x, int z) const { return m_heightMap.Get(x, z); }

	void SetHeight(Point2i coord, float height) { m_heightMap.Set(coord.x, coord.y, height); }

	float GetHeightInterpolated(float x, float z) const;

	FTransform transform;

	Array2D<float> m_heightMap;

	float m_minHeight = 0.0f;
	float m_maxHeight = 0.0f;

	ProceduralGen_t m_GenerationMethode;

private:
	
	int m_currentIndeMethode = 0;

	int m_terrainSize = 50;

	TriangleList m_triangleList;
};
