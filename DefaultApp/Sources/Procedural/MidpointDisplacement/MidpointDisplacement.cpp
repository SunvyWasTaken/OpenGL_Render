
#include "MidpointDisplacement.h"
#include "Procedural/BaseTerrain/BaseTerrain.h"

namespace
{
	int CalcNextPowerOfTwo(int x)
	{
		int ret = 1;

		if (x == 1) {
			return 2;
		}

		while (ret < x) {
			ret = ret * 2;
		}

		return ret;
	}

	float RandomFloat()
	{
		float Max = RAND_MAX;
		return ((float)rand() / Max);
	}


	float RandomFloatRange(float Start, float End)
	{
		if (End == Start) {
			printf("Invalid random range: (%f, %f)\n", Start, End);
			exit(0);
		}

		float Delta = End - Start;

		float RandomValue = RandomFloat() * Delta + Start;

		return RandomValue;
	}
}

void MidpointDispTerrain::GenerationMethode(float Roughness, float MinHeight, float MaxHeight)
{
    if (Roughness < 0.0f) {
        printf("%s: roughness must be positive - %f\n", __FUNCTION__, Roughness);
        exit(0);
    }

    m_terrain->m_minHeight = MinHeight;
    m_terrain->m_maxHeight = MaxHeight;

	int RectSize = CalcNextPowerOfTwo(GetTerrainSize());
	float CurHeight = (float)RectSize / 2.0f;
	float HeightReduce = pow(2.0f, -Roughness);

	while (RectSize > 0)
    {
		DiamondStep(RectSize, CurHeight);

		SquareStep(RectSize, CurHeight);

		RectSize /= 2;
		CurHeight *= HeightReduce;
	}
}

void MidpointDispTerrain::DiamondStep(int RectSize, float CurHeight)
{
    int HalfRectSize = RectSize / 2;

    for (int y = 0 ; y < GetTerrainSize() ; y += RectSize)
    {
        for (int x = 0 ; x < GetTerrainSize() ; x += RectSize)
        {
            int next_x = (x + RectSize) % GetTerrainSize();
            int next_y = (y + RectSize) % GetTerrainSize();

            if (next_x < x) {
                next_x = GetTerrainSize() - 1;
            }

            if (next_y < y) {
                next_y = GetTerrainSize() - 1;
            }

            float TopLeft     = GetHeight({x, y});
            float TopRight    = GetHeight({next_x, y});
            float BottomLeft  = GetHeight({x, next_y});
            float BottomRight = GetHeight({next_x, next_y});

            int mid_x = (x + HalfRectSize) % GetTerrainSize();
            int mid_y = (y + HalfRectSize) % GetTerrainSize();

            float RandValue = RandomFloatRange(CurHeight, -CurHeight);
            float MidPoint = (TopLeft + TopRight + BottomLeft + BottomRight) / 4.0f;

            m_terrain->SetHeight({mid_x, mid_y}, MidPoint + RandValue);
        }
    }
}


void MidpointDispTerrain::SquareStep(int RectSize, float CurHeight)
{
    int HalfRectSize = RectSize / 2;

    for (int y = 0 ; y < GetTerrainSize() ; y += RectSize) {
        for (int x = 0 ; x < GetTerrainSize() ; x += RectSize) {
            int next_x = (x + RectSize) % GetTerrainSize();
            int next_y = (y + RectSize) % GetTerrainSize();

            if (next_x < x) {
                next_x = GetTerrainSize() - 1;
            }

            if (next_y < y) {
                next_y = GetTerrainSize() - 1;
            }

            int mid_x = (x + HalfRectSize) % GetTerrainSize();
            int mid_y = (y + HalfRectSize) % GetTerrainSize();
              
            int prev_mid_x = (x - HalfRectSize + GetTerrainSize()) % GetTerrainSize();
            int prev_mid_y = (y - HalfRectSize + GetTerrainSize()) % GetTerrainSize();

            float CurTopLeft  = GetHeight({x, y});
            float CurTopRight = GetHeight({next_x, y});
            float CurCenter   = GetHeight({mid_x, mid_y});
            float PrevYCenter = GetHeight({mid_x, prev_mid_y});
            float CurBotLeft  = GetHeight({x, next_y});
            float PrevXCenter = GetHeight({prev_mid_x, mid_y});

            float CurLeftMid = (CurTopLeft + CurCenter + CurBotLeft + PrevXCenter) / 4.0f + RandomFloatRange(-CurHeight, CurHeight);
            float CurTopMid  = (CurTopLeft + CurCenter + CurTopRight + PrevYCenter) / 4.0f + RandomFloatRange(-CurHeight, CurHeight);

            m_terrain->SetHeight({mid_x, y}, CurTopMid);
            m_terrain->SetHeight({x, mid_y}, CurLeftMid);
        }
    }
}
