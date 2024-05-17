#pragma once

#include "Math/Point.h"

#include <functional>
#include <utility>

class BaseTerrain;

template <typename type>
class ProceduralMethodeBase
{
public:
	explicit ProceduralMethodeBase(BaseTerrain* terrain) : m_terrain(terrain)
	{}

	template <typename ...Args>
	void GenerationMethode(Args... args) = delete;
	//{
	//	//type* obj = static_cast<type*>(this);
	//	//std::invoke([obj](...) mutable { obj->GenerationMethode(args...); }, std::forward<Args>(args)...);
	//};

	int GetTerrainSize(){ return ((m_terrain != nullptr) ? m_terrain->GetTerrainSize() : 1); }

protected:
	BaseTerrain* m_terrain;
};

class FaultFormation : public ProceduralMethodeBase<FaultFormation>
{
public:

	explicit FaultFormation(BaseTerrain* terrain = nullptr) : ProceduralMethodeBase(terrain) {};

	void GenerationMethode(int Iterations, float MinHeight, float MaxHeight, float Filter);

private:

	void GenRandomTerrainPoints(Point2i& p1, Point2i& p2);
	void ApplyFIRFilter(float Filter);
	float FIRFilterSinglePoint(int x, int z, float PrevVal, float Filter);
};

class NoGeneration : public ProceduralMethodeBase<NoGeneration>
{
public:

	explicit NoGeneration(BaseTerrain* terrain = nullptr) : ProceduralMethodeBase(terrain) {};

	//void GenerationMethode(float MawHeight)
	//{
	//	//std::cout << "NoErrosion" << MawHeight << std::endl;
	//}
};