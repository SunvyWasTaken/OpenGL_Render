#pragma once

#include "Math/Array.h"

#include <vector>

class MidpointGen
{

public:

	explicit MidpointGen(const unsigned int terrainSize = 25, const float Roughness = 1.f, const float minHeight = 0.f, const float maxHeight = 9.f);

	void CreateDisplacement(const float Roughness);

	void DiamondStep(int rectangleSize, float currHeight);

	void SquareStep(int rectangleSize, float currHeight);

private:

	TArray2D<float> m_heightMap;

	unsigned int m_TerrainSize;

	float m_MinHeight;

	float m_MaxHeight;
};