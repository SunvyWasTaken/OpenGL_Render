#include "BaseTerrain.h"
#include "Core\ContextRenderer.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include <string.h>

#include <iostream>

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
	float BaseHeight = GetHeight((int)x, (int)z);

	if (((int)x + 1 >= m_terrainSize) || ((int)z + 1 >= m_terrainSize)) {
		return BaseHeight;
	}

	float NextXHeight = GetHeight((int)x + 1, (int)z);

	float RatioX = x - floorf(x);

	float InterpolatedHeightX = (float)(NextXHeight - BaseHeight) * RatioX + (float)BaseHeight;

	float NextZHeight = GetHeight((int)x, (int)z + 1);

	float RatioZ = z - floorf(z);

	float InterpolatedHeightZ = (float)(NextZHeight - BaseHeight) * RatioZ + (float)BaseHeight;

	float FinalHeight = (InterpolatedHeightX + InterpolatedHeightZ) / 2.0f;

	return FinalHeight;
}
