#pragma once

#include "Procedural/ProceduralMethodeBase.h"

#include <functional>
#include <utility>

class BaseTerrain;

class FaultFormation : public ProceduralMethodeBase
{
public:

	explicit FaultFormation(BaseTerrain* terrain) : ProceduralMethodeBase(terrain) {};

	void GenerationMethode(int Iterations, float MinHeight, float MaxHeight, float Filter);

private:

	void GenRandomTerrainPoints(Point2i& p1, Point2i& p2);
	void ApplyFIRFilter(float Filter);
	float FIRFilterSinglePoint(int x, int z, float PrevVal, float Filter);
};

class NoGeneration : public ProceduralMethodeBase
{
public:

	explicit NoGeneration(BaseTerrain* terrain) : ProceduralMethodeBase(terrain) {};

};