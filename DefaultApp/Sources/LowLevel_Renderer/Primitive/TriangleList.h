#pragma once

#include "Math/Vector3D.h"
#include "LowLevel_Renderer/Primitive/Vertex.h"

#include <glad/glad.h>
#include <vector>

class BaseTerrain;
struct ContextRenderer;

using vertex_type = Vertex<float>;

class TriangleList
{
 public:
    TriangleList();

    ~TriangleList();

    void CreateTriangleList(int Width, int Depth, BaseTerrain* terrain);

    void Destroy();

    void Render(ContextRenderer& contextRenderer);
    
    void Load();

 private:

    void ChangeVertice(const BaseTerrain* pTerrain, vertex_type& vertex, int x, int z);
    void InitVertices(const BaseTerrain* pTerrain, std::vector<vertex_type>& Vertices);
    void InitIndices(std::vector<uint>& Indices);

    int m_width;
    int m_depth;

    BaseTerrain* m_terrain;

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
	struct Shader* m_shaders;
};

