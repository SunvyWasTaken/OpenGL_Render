
#include "Midpoint_Generation.h"
#include "Math/MathUtility.h"

#include <stdexcept>

MidpointGen::MidpointGen(const unsigned int terrainSize, const float Roughness, const float minHeight, const float maxHeight)
	: m_heightMap(terrainSize)
	, m_TerrainSize(terrainSize)
	, m_MinHeight(minHeight)
	, m_MaxHeight(maxHeight)
{
	if (Roughness < 0.f)
	{
		throw std::invalid_argument("Rougness can't be negative my dude");
	}

	CreateDisplacement(Roughness);

}

void MidpointGen::CreateDisplacement(const float Roughness)
{
	int RectangleSize = Utility::NextPowerTwo(m_TerrainSize);

	float CurHeight = static_cast<float>(RectangleSize) / 2.f;

	float HeightReduce = pow(2.f, -Roughness);

	while (RectangleSize > 0)
	{
		DiamondStep(RectangleSize, CurHeight);
		SquareStep(RectangleSize, CurHeight);

		RectangleSize /= 2;
		CurHeight *= HeightReduce;
	}
}

void MidpointGen::DiamondStep(const int rectangleSize, const float currHeight)
{
	int HalfrectangleSize = rectangleSize / 2;

	for (int unsigned y = 0; y < m_TerrainSize; y += rectangleSize) {
		for (int unsigned x = 0; x < m_TerrainSize; x += rectangleSize) {
			unsigned int next_x = (x + rectangleSize) % m_TerrainSize;
			unsigned int next_y = (y + rectangleSize) % m_TerrainSize;

			if (next_x < x) {
				next_x = m_TerrainSize - 1;
			}

			if (next_y < y) {
				next_y = m_TerrainSize - 1;
			}

			float TopLeft = m_heightMap(x, y);
			float TopRight = m_heightMap(next_x, y);
			float BottomLeft = m_heightMap(x, next_y);
			float BottomRight = m_heightMap(next_x, next_y);

			int mid_x = (x + HalfrectangleSize) % m_TerrainSize;
			int mid_y = (y + HalfrectangleSize) % m_TerrainSize;

			float RandValue = Utility::TRandomInRange<float>(currHeight, -currHeight);
			float MidPoint = (TopLeft + TopRight + BottomLeft + BottomRight) / 4.0f;

			m_heightMap(mid_x, mid_y) = MidPoint + RandValue;
		}
	}
}

void MidpointGen::SquareStep(const int rectangleSize, const float currHeight)
{
	int HalfrectangleSize = rectangleSize / 2;

	for (unsigned int y = 0; y < m_TerrainSize; y += rectangleSize)
	{
		for (unsigned int x = 0; x < m_TerrainSize; x += rectangleSize)
		{
			unsigned int next_x = (x + rectangleSize) % m_TerrainSize;
			unsigned int next_y = (y + rectangleSize) % m_TerrainSize;

			if (next_x < x)
			{
				next_x = m_TerrainSize - 1;
			}

			if (next_y < y)
			{
				next_y = m_TerrainSize - 1;
			}

			int mid_x = (x + HalfrectangleSize) % m_TerrainSize;
			int mid_y = (y + HalfrectangleSize) % m_TerrainSize;

			int prev_mid_x = (x - HalfrectangleSize + m_TerrainSize) % m_TerrainSize;
			int prev_mid_y = (y - HalfrectangleSize + m_TerrainSize) % m_TerrainSize;

			float CurTopLeft = m_heightMap(x, y);
			float CurTopRight = m_heightMap(next_x, y);
			float CurCenter = m_heightMap(mid_x, mid_y);
			float PrevYCenter = m_heightMap(mid_x, prev_mid_y);
			float CurBotLeft = m_heightMap(x, next_y);
			float PrevXCenter = m_heightMap(prev_mid_x, mid_y);

			float CurLeftMid = (CurTopLeft + CurCenter + CurBotLeft + PrevXCenter) / 4.0f + Utility::TRandomInRange<float>(-currHeight, currHeight);
			float CurTopMid = (CurTopLeft + CurCenter + CurTopRight + PrevYCenter) / 4.0f + Utility::TRandomInRange<float>(-currHeight, currHeight);

			m_heightMap(mid_x, y) = CurTopMid;
			m_heightMap(x, mid_y) = CurLeftMid;
		}
	}
}

