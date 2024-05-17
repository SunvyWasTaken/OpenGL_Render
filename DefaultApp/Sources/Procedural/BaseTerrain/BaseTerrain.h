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

	void InitTerrain();

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

	float GetHeight(int x, int z) const { return m_heightMap.Get(x, z); }

	int GetTerrainSize() const { return m_terrainSize; }

	void SetGenMethode(const int index);

	float GetHeightInterpolated(float x, float z) const;

	void SetHeight(Point2i coord, float height) {m_heightMap.Set(coord.x, coord.y, height); }

	FTransform transform;

	Array2D<float> m_heightMap;

	float m_minHeight = 0.0f;
	float m_maxHeight = 0.0f;

private:

	int m_terrainSize = 50;

	ProceduralGen_t m_GenerationMethode;

	TriangleList m_triangleList;
};
