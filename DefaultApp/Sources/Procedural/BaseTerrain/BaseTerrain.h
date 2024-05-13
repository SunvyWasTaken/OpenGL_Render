#pragma once

#include "LowLevel_Renderer/Cameras/Camera.h"
#include "Math/Array2D.h"
#include "LowLevel_Renderer/Primitive/TriangleList.h"
#include "Procedural/TerrainTech/TerrainTechnique.h"


class BaseTerrain
{
public:
	BaseTerrain() {}

	~BaseTerrain();

	void Destroy();

	void InitTerrain(float WorldScale);

	void Render(const Camera& Camera);

	float GetHeight(int x, int z) const { return m_heightMap.Get(x, z); }

	float GetWorldScale() const { return m_worldScale; }

protected:

	int m_terrainSize = 0;
	float m_worldScale = 1.0f;
	Array2D<float> m_heightMap;
	TriangleList m_triangleList;
	TerrainTechnique m_terrainTech;
	float m_minHeight = 0.0f;
	float m_maxHeight = 0.0f;
};
