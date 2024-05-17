#pragma once

#include "Math/Vector3D.h"
#include "LowLevel_Renderer/Materials/Material.h"
#include "LowLevel_Renderer/Primitive/Vertex.h"

#include <glad/glad.h>
#include <vector>

class BaseTerrain;
struct ContextRenderer;

using vertex_type = Vertex<float>;
using uint = unsigned int;

class TriangleList final
{
 public:
    TriangleList();

    ~TriangleList();

    void CreateTriangleList(int Width, int Depth, BaseTerrain* terrain);

    void Destroy();

    void Render(ContextRenderer& contextRenderer);
    
    void Load();

 private:

    void ChangeVertice(vertex_type& vertex, int x, int z);

    void InitVertices(std::vector<vertex_type>& Vertices);

    void InitIndices(std::vector<uint>& Indices);

    void CalcNormals(std::vector<vertex_type>& Vertices, std::vector<uint>& Indices);

private:

    int m_width;
    int m_depth;

    BaseTerrain* m_terrain;

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
    Material m_material;
	struct Shader* m_shaders;
};

