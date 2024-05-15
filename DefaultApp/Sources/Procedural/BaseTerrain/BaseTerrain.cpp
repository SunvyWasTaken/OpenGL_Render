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

void BaseTerrain::InitTerrain(float WorldScale)
{
	m_worldScale = WorldScale;
}

void BaseTerrain::Render(ContextRenderer& contextRenderer)
{
	m_triangleList.Render(contextRenderer);
}