#include "BaseTerrain.h"

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

void BaseTerrain::InitTerrain(float WorldScale)
{
	if (!m_terrainTech.Init()) {
		printf("Error initializing tech\n");
		exit(0);
	}

	m_worldScale = WorldScale;
}

void BaseTerrain::Render(const Camera& Camera)
{
	Mat4f VP = Camera.getMatrixView();

	m_terrainTech.Enable();
	m_terrainTech.SetVP(VP);

	m_triangleList.Render();
}