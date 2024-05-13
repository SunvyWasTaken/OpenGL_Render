#pragma once

#include <glad/glad.h>
#include <vector>

#include "Math/Vector3D.h"

class BaseTerrain;

class TriangleList {
 public:
    TriangleList();

    ~TriangleList();

    void CreateTriangleList(int Width, int Depth, const BaseTerrain* pTerrain);

    void Destroy();

    void Render();

 private:

    struct Vertex
    {
        Vertex();

        Vector3Df Pos;

        void InitVertex(const BaseTerrain* pTerrain, int x, int z);
    };

    void CreateGLState();

	void PopulateBuffers(const BaseTerrain* pTerrain);
    void InitVertices(const BaseTerrain* pTerrain, std::vector<Vertex>& Vertices);
    void InitIndices(std::vector<uint>& Indices);

    int m_width = 0;
    int m_depth = 0;
    GLuint m_vao = 0;
    GLuint m_vb = 0;
    GLuint m_ib = 0;
};

