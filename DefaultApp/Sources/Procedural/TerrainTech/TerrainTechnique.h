#pragma once

#include "Technique.h"
#include "Math/Matrix.h"

class TerrainTechnique : public Technique
{
public:

    TerrainTechnique();

    virtual bool Init();

    void SetVP(const Mat4f& VP);

    void SetMinMaxHeight(float Min, float Max);

private:
    GLuint m_VPLoc = -1;
    GLuint m_minHeightLoc = -1;
    GLuint m_maxHeightLoc = -1;
};

