#pragma once

#include "Procedural/BaseTerrain/BaseTerrain.h"
#include <iostream>
#include <functional>
#include <utility>

class FaultFormation : public BaseTerrain
{
public:
	void GenerateTerrain(int TerrainSize, int Iterations, float MinHeight, float MaxHeight, float Filter);

private:

	struct TerrainPoint {
		int x = 0;
		int z = 0;

		void Print()
		{
			printf("[%d,%d]", x, z);
		}

		bool IsEqual(TerrainPoint& p) const
		{
			return ((x == p.x) && (z == p.z));
		}
	};

	void CreateFaultFormationInternal(int Iterations, float MinHeight, float MaxHeight, float Filter);
	void GenRandomTerrainPoints(TerrainPoint& p1, TerrainPoint& p2);
	void ApplyFIRFilter(float Filter);
	float FIRFilterSinglePoint(int x, int z, float PrevVal, float Filter);
};

class NoErrosion : public BaseTerrain
{
public:
	void GenerateTerrain(float MawHeight)
	{
		std::cout << "NoErrosion" << MawHeight << std::endl;
	}
};