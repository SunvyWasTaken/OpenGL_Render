#include "BaseTerrain.h"
#include "Core\ContextRenderer.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include <string.h>

BaseTerrain::~BaseTerrain()
{
	Destroy();
}

void BaseTerrain::Destroy()
{
	m_heightMap.Destroy();
	m_triangleList.Destroy();
}

void BaseTerrain::Render(ContextRenderer& contextRenderer)
{
	m_triangleList.Render(contextRenderer);
}

float BaseTerrain::GetHeightInterpolated(float x, float z) const
{
	float X0Z0Height = GetHeight((int)x, (int)z);

	if (((int)x + 1 >= m_terrainSize) || ((int)z + 1 >= m_terrainSize)) {
		return X0Z0Height;
	}

	float X1Z0Height = GetHeight((int)x + 1, (int)z);
	float X0Z1Height = GetHeight((int)x, (int)z + 1);
	float X1Z1Height = GetHeight((int)x + 1, (int)z + 1);

	float FactorX = x - floorf(x);

	float InterpolatedBottom = (X1Z0Height - X0Z0Height) * FactorX + X0Z0Height;
	float InterpolatedTop = (X1Z1Height - X0Z1Height) * FactorX + X0Z1Height;

	float FactorZ = z - floorf(z);

	float FinalHeight = (InterpolatedTop - InterpolatedBottom) * FactorZ + InterpolatedBottom;

	return FinalHeight;
}
