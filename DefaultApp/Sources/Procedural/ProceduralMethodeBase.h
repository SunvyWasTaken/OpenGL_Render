#pragma once

#include "Math/Point.h"

class BaseTerrain;

class ProceduralMethodeBase
{
public:

	ProceduralMethodeBase() = delete;

	explicit ProceduralMethodeBase(BaseTerrain* terrain) : m_terrain(terrain)
	{}

	template <typename ...Args>
	void GenerationMethode(Args... args) = delete;
	//{
	//	//type* obj = static_cast<type*>(this);
	//	//std::invoke([obj](...) mutable { obj->GenerationMethode(args...); }, std::forward<Args>(args)...);
	//};

	int GetTerrainSize() const;

	float GetHeight(const Point2i& coord) const;

protected:
	BaseTerrain* m_terrain;
};
