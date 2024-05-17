#pragma once


#include "Procedural/ProceduralMethodeBase.h"

class MidpointDispTerrain : public ProceduralMethodeBase
{
 public:
    MidpointDispTerrain(BaseTerrain* terrain) : ProceduralMethodeBase(terrain) {}

    void GenerationMethode(float Roughness, float MinHeight, float MaxHeight);

 private:

    void DiamondStep(int RectSize, float CurHeight);
    void SquareStep(int RectSize, float CurHeight);
};


