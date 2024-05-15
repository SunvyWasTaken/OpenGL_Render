
#include "PrimitiveUtils.h"

#include "Core\ContextRenderer.h"
#include "Procedural/BaseTerrain/BaseTerrain.h"
#include "TriangleList.h"

#include <assert.h>
#include <stdio.h>
#include <vector>


TriangleList::TriangleList()
    : m_width(0)
    , m_depth(0)
    , m_terrain(nullptr)
    , m_vao(0)
    , m_vbo(0)
    , m_ebo(0)
    , m_shaders(nullptr)
{
}


TriangleList::~TriangleList()
{
    Destroy();
}

void TriangleList::CreateTriangleList(int Width, int Depth, BaseTerrain* terrain)
{
    m_width = Width;
    m_depth = Depth;
    m_terrain = terrain;

    Load();
}


void TriangleList::Destroy()
{
    if (!m_shaders)
        return;

    DELETE_BUFFER_WITH_ELEMENTS(m_shaders->program);

    if (m_shaders)
    {
        delete m_shaders;
        m_shaders = nullptr;
    }
}

void TriangleList::ChangeVertice(const BaseTerrain* pTerrain, vertex_type& vertex, int x, int z)
{
    float y = pTerrain->GetHeight(x, z);

	float WorldScale = pTerrain->GetWorldScale();

	vertex.m_point = vertex_type::P3D(x * WorldScale, y, z * WorldScale);
}


void TriangleList::InitVertices(const BaseTerrain* pTerrain, std::vector<vertex_type>& Vertices)
{
    int Index = 0;

    for (int z = 0 ; z < m_depth ; z++) {
        for (int x = 0 ; x < m_width ; x++) {
            assert(Index < Vertices.size());
			ChangeVertice(pTerrain, Vertices[Index], x, z);
			Index++;
        }
    }

    assert(Index == Vertices.size());
}


void TriangleList::InitIndices(std::vector<GLuint>& Indices)
{
    int Index = 0;

    for (int z = 0 ; z < m_depth - 1 ; z++) {
        for (int x = 0 ; x < m_width - 1 ; x++) {
            GLuint IndexBottomLeft = z * m_width + x;
            GLuint IndexTopLeft = (z + 1) * m_width + x;
            GLuint IndexTopRight = (z + 1) * m_width + x + 1;
            GLuint IndexBottomRight = z * m_width + x + 1;

            // Add "top left" triangle
            assert(Index < Indices.size());
            Indices[Index++] = IndexBottomLeft;
            assert(Index < Indices.size());
            Indices[Index++] = IndexTopLeft;
            assert(Index < Indices.size());
            Indices[Index++] = IndexTopRight;

            // Add "bottom right" triangle
            assert(Index < Indices.size());
            Indices[Index++] = IndexBottomLeft;
            assert(Index < Indices.size());
            Indices[Index++] = IndexTopRight;
            assert(Index < Indices.size());
            Indices[Index++] = IndexBottomRight;
        }
    }

    assert(Index == Indices.size());
}


void TriangleList::Render(ContextRenderer& contextRenderer)
{
	glUseProgram(m_shaders->program);
	glBindVertexArray(m_vao);

	m_shaders->setMat4("projection", contextRenderer.projection);
	m_shaders->setMat4("view", contextRenderer.camera.getMatrixView());
	m_shaders->setMat4("model", m_terrain->transform.getMatrix());

	m_shaders->setVec3("viewPostion", contextRenderer.camera.transform.position);

	contextRenderer.directionalLight.getUniform(m_shaders);

    glDrawElements(GL_TRIANGLES, (m_depth - 1) * (m_width - 1) * 6, GL_UNSIGNED_INT, NULL);
}

void TriangleList::Load()
{
	std::vector<vertex_type> Vertices;
	Vertices.resize(m_width * m_depth, vertex_type(vertex_type::P3D(0), vertex_type::Color()));

	InitVertices(m_terrain, Vertices);

	std::vector<GLuint> Indices;
	int NumQuads = (m_width - 1) * (m_depth - 1);
	Indices.resize(NumQuads * 6);
	InitIndices(Indices);


	LOAD_VERTEX_ARRAYS(m_vao);
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(vertex_type), Vertices.data(), GL_STATIC_DRAW);
	LOAD_ELEMENT_ARRAY_BUFFER(m_ebo, Indices);

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER,  "default.vert"},
		{GL_FRAGMENT_SHADER, "default.frag"},
		{GL_NONE, nullptr}
	};

	m_shaders = Shader::loadShader(shaders);
	glUseProgram(m_shaders->program);

	LOAD_BASIC_VERTEX_ATTRIB_POINTER();

	glBindVertexArray(0);

    // Kristo
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // ogldev
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices[0]) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0]) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}
