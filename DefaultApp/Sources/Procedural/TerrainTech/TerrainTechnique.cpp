#include "Procedural/TerrainTech/TerrainTechnique.h"


TerrainTechnique::TerrainTechnique()
{
}

bool TerrainTechnique::Init()
{
    if (!Technique::Init()) {
        return false;
    }

    if (!AddShader(GL_VERTEX_SHADER, "terrain.vs")) {
        return false;
    }

    if (!AddShader(GL_FRAGMENT_SHADER, "terrain.fs")) {
        return false;
    }

    if (!Finalize()) {
        return false;
    }

    m_VPLoc = GetUniformLocation("gVP");
    m_minHeightLoc = GetUniformLocation("gMinHeight");
    m_maxHeightLoc = GetUniformLocation("gMaxHeight");

    if (m_VPLoc == 0xffffffff ||
        m_minHeightLoc == 0xffffffff ||
        m_maxHeightLoc == 0xffffffff) {
        return false;
    }

    return true;
}


void TerrainTechnique::SetVP(const Mat4f& VP)
{
    glUniformMatrix4fv(m_VPLoc, 1, GL_TRUE, (const GLfloat*)VP.data());
}


void TerrainTechnique::SetMinMaxHeight(float Min, float Max)
{
    glUniform1f(m_minHeightLoc, Min);
    glUniform1f(m_maxHeightLoc, Max);}
