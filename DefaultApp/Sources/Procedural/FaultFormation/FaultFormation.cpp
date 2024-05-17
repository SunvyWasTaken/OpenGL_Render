#include "FaultFormation.h"

#include "Procedural/BaseTerrain/BaseTerrain.h"

#include <assert.h>

void FaultFormation::GenerationMethode(int Iterations, float MinHeight, float MaxHeight, float Filter)
{
	m_terrain->m_minHeight = MinHeight;
	m_terrain->m_maxHeight = MaxHeight;

	float DeltaHeight = MaxHeight - MinHeight;

	for (int CurIter = 0; CurIter < Iterations; CurIter++)
	{
		float IterationRatio = ((float)CurIter / (float)Iterations);
		float Height = MaxHeight - IterationRatio * DeltaHeight;

		Point2i p1, p2;

		GenRandomTerrainPoints(p1, p2);

		int DirX = p2.x - p1.x;
		int DirZ = p2.y - p1.y;

		for (int z = 0; z < GetTerrainSize(); z++)
		{
			for (int x = 0; x < GetTerrainSize(); x++)
			{
				int DirX_in = x - p1.x;
				int DirZ_in = z - p1.y;

				int CrossProduct = DirX_in * DirZ - DirX * DirZ_in;

				if (CrossProduct > 0)
				{
					float CurHeight = GetHeight({x, z});
					m_terrain->SetHeight({x, z}, CurHeight + Height);
				}
			}
		}
	}

	ApplyFIRFilter(Filter);

	m_terrain->m_heightMap.Normalize(MinHeight, MaxHeight);
}

void FaultFormation::GenRandomTerrainPoints(Point2i& p1, Point2i& p2)
{
	p1.x = rand() % GetTerrainSize();
	p1.y = rand() % GetTerrainSize();

	int Counter = 0;

	do {
		p2.x = rand() % GetTerrainSize();
		p2.y = rand() % GetTerrainSize();

		if (Counter++ == 1000) {
			printf("Endless loop detected in %s:%d\n", __FILE__, __LINE__);
			assert(0);
		}
	} while (p1 == p2);
}

void FaultFormation::ApplyFIRFilter(float Filter)
{
	// left to right
	for (int z = 0; z < GetTerrainSize(); z++) {
		float PrevVal = GetHeight({0, z});
		for (int x = 1; x < GetTerrainSize(); x++) {
			PrevVal = FIRFilterSinglePoint(x, z, PrevVal, Filter);
		}
	}

	// right to left
	for (int z = 0; z < GetTerrainSize(); z++) {
		float PrevVal = GetHeight({GetTerrainSize() - 1, z});
		for (int x = GetTerrainSize() - 2; x >= 0; x--) {
			PrevVal = FIRFilterSinglePoint(x, z, PrevVal, Filter);
		}
	}

	// bottom to top
	for (int x = 0; x < GetTerrainSize(); x++) {
		float PrevVal = GetHeight({x, 0});
		for (int z = 1; z < GetTerrainSize(); z++) {
			PrevVal = FIRFilterSinglePoint(x, z, PrevVal, Filter);
		}
	}

	// top to bottom
	for (int x = 0; x < GetTerrainSize(); x++) {
		float PrevVal = GetHeight({x, GetTerrainSize() - 1});
		for (int z = GetTerrainSize() - 2; z >= 0; z--) {
			PrevVal = FIRFilterSinglePoint(x, z, PrevVal, Filter);
		}
	}
}

float FaultFormation::FIRFilterSinglePoint(int x, int z, float PrevVal, float Filter)
{
	float CurVal = GetHeight({x, z});
	float NewVal = Filter * PrevVal + (1 - Filter) * CurVal;
	m_terrain->SetHeight({x, z}, NewVal);
	return NewVal;
}

