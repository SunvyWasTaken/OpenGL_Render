#pragma once

#include "Procedural/BaseTerrain/BaseTerrain.h"

int ProceduralMethodeBase::GetTerrainSize() const
{
	return ((m_terrain != nullptr) ? m_terrain->GetTerrainSize() : 0);
}

float ProceduralMethodeBase::GetHeight(const Point2i& coord) const
{
	return (m_terrain != nullptr ? m_terrain->GetHeight(coord.x, coord.y) : 0);
}
