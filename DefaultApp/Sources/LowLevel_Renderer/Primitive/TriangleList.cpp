
#include "PrimitiveUtils.h"

#include "Core\ContextRenderer.h"
#include "Procedural/BaseTerrain/BaseTerrain.h"
#include "TriangleList.h"

#include <assert.h>
#include <stdio.h>
#include <vector>

using Mat4f = Math::Mat4<float>;

TriangleList::TriangleList()
    : m_width(0)
    , m_depth(0)
    , m_terrain(nullptr)
    , m_vao(0)
    , m_vbo(0)
    , m_ebo(0)
    , m_material(Material{})
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

void TriangleList::ChangeVertice(vertex_type& vertex, int x, int z)
{
    float y = m_terrain->GetHeight(x, z);

	vertex.m_point = vertex_type::P3D(x * m_terrain->transform.scale.x, y * m_terrain->transform.scale.y, z * m_terrain->transform.scale.z) + m_terrain->transform.position;
    vertex.m_color = vertex_type::Color(1, 1, 1);
    vertex.m_textureCoords = vertex_type::P2D((float)x / (float)m_width, (float)z / (float)m_depth);
    vertex.m_normal = vertex_type::P3D(0.f, -1.f, 0.f);
}


void TriangleList::InitVertices(std::vector<vertex_type>& Vertices)
{
    int Index = 0;

    for (int z = 0 ; z < m_depth ; z++)
    {
        for (int x = 0 ; x < m_width ; x++)
        {
            assert(Index < Vertices.size());
			ChangeVertice(Vertices[Index], x, z);
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
	//Mat4f mTransform = Mat4f::identity();
	//Mat4f mTrans = Mat4f::translate(m_terrain->transform.position);
	//Mat4f mRot = Mat4f::rotation(m_terrain->transform.rotation);
 //   Mat4f mScale = Mat4f::scale(m_terrain->transform.scale * m_width);
	m_shaders->setMat4("model", m_terrain->transform.getMatrix());

	m_shaders->setVec3("viewPostion", contextRenderer.camera.transform.position);
    m_shaders->setFloat("material.shininess", m_material.shininess);

	contextRenderer.directionalLight.getUniform(m_shaders);

	m_material.diffuseMap.bind(GL_TEXTURE0);
	m_material.specularMap.bind(GL_TEXTURE1);

    glDrawElements(GL_TRIANGLES, (m_depth - 1) * (m_width - 1) * 6, GL_UNSIGNED_INT, NULL);
}

void TriangleList::Load()
{
    TextureGenerator textureGen;
    textureGen.LoadTile("Ressources\\Landscape\\Stone_BaseColor.jpg");
    textureGen.LoadTile("Ressources\\Landscape\\Grass_BaseColor.jpg");
    textureGen.LoadTile("Ressources\\Landscape\\Snow_BaseColor.jpg");
   
	m_material = Material
    {
        textureGen.GenerateTexture(m_width, m_terrain, 0.f, 150.f),
		Texture("Ressources\\Landscape\\Grass_Specular.jpg", GL_TEXTURE1),
		32.f
	};

	std::vector<vertex_type> Vertices;
	Vertices.resize(m_width * m_depth, vertex_type(vertex_type::P3D(0), vertex_type::Color()));

	InitVertices(Vertices);

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

	m_material.diffuseMap.textUnit(m_shaders->program, "tex0");
	m_material.specularMap.textUnit(m_shaders->program, "tex1");

	glBindVertexArray(0);

    // Kristo
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // ogldev
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices[0]) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0]) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

}
