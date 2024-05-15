#include "FaultFormation.h"

#include <assert.h>
#include <iostream>

void FaultFormation::GenerateTerrain(int TerrainSize, int Iterations, float MinHeight, float MaxHeight, float Filter)
{
	std::cout << "Terrain generated!!!" << std::endl;
	m_terrainSize = TerrainSize;
	m_minHeight = MinHeight;
	m_maxHeight = MaxHeight;

	m_heightMap.InitArray2D(TerrainSize, TerrainSize, 0.0f);

	CreateFaultFormationInternal(Iterations, MinHeight, MaxHeight, Filter);

	m_heightMap.Normalize(MinHeight, MaxHeight);

	m_triangleList.CreateTriangleList(m_terrainSize, m_terrainSize, this);
}

void FaultFormation::CreateFaultFormationInternal(int Iterations, float MinHeight, float MaxHeight, float Filter)
{
	float DeltaHeight = MaxHeight - MinHeight;

	for (int CurIter = 0; CurIter < Iterations; CurIter++) {
		float IterationRatio = ((float)CurIter / (float)Iterations);
		float Height = MaxHeight - IterationRatio * DeltaHeight;

		TerrainPoint p1, p2;

		GenRandomTerrainPoints(p1, p2);

		int DirX = p2.x - p1.x;
		int DirZ = p2.z - p1.z;

		for (int z = 0; z < m_terrainSize; z++) {
			for (int x = 0; x < m_terrainSize; x++) {
				int DirX_in = x - p1.x;
				int DirZ_in = z - p1.z;

				int CrossProduct = DirX_in * DirZ - DirX * DirZ_in;

				if (CrossProduct > 0) {
					float CurHeight = m_heightMap.Get(x, z);
					m_heightMap.Set(x, z, CurHeight + Height);
				}
			}
		}
	}

	ApplyFIRFilter(Filter);
}

void FaultFormation::GenRandomTerrainPoints(TerrainPoint& p1, TerrainPoint& p2)
{
	p1.x = rand() % m_terrainSize;
	p1.z = rand() % m_terrainSize;

	int Counter = 0;

	do {
		p2.x = rand() % m_terrainSize;
		p2.z = rand() % m_terrainSize;

		if (Counter++ == 1000) {
			printf("Endless loop detected in %s:%d\n", __FILE__, __LINE__);
			assert(0);
		}
	} while (p1.IsEqual(p2));
}

void FaultFormation::ApplyFIRFilter(float Filter)
{
	// left to right
	for (int z = 0; z < m_terrainSize; z++) {
		float PrevVal = m_heightMap.Get(0, z);
		for (int x = 1; x < m_terrainSize; x++) {
			PrevVal = FIRFilterSinglePoint(x, z, PrevVal, Filter);
		}
	}

	// right to left
	for (int z = 0; z < m_terrainSize; z++) {
		float PrevVal = m_heightMap.Get(m_terrainSize - 1, z);
		for (int x = m_terrainSize - 2; x >= 0; x--) {
			PrevVal = FIRFilterSinglePoint(x, z, PrevVal, Filter);
		}
	}

	// bottom to top
	for (int x = 0; x < m_terrainSize; x++) {
		float PrevVal = m_heightMap.Get(x, 0);
		for (int z = 1; z < m_terrainSize; z++) {
			PrevVal = FIRFilterSinglePoint(x, z, PrevVal, Filter);
		}
	}

	// top to bottom
	for (int x = 0; x < m_terrainSize; x++) {
		float PrevVal = m_heightMap.Get(x, m_terrainSize - 1);
		for (int z = m_terrainSize - 2; z >= 0; z--) {
			PrevVal = FIRFilterSinglePoint(x, z, PrevVal, Filter);
		}
	}
}

float FaultFormation::FIRFilterSinglePoint(int x, int z, float PrevVal, float Filter)
{
	float CurVal = m_heightMap.Get(x, z);
	float NewVal = Filter * PrevVal + (1 - Filter) * CurVal;
	m_heightMap.Set(x, z, NewVal);
	return NewVal;
}

