#pragma once
#include "PrimitiveUtils.h"
#include "Vertex.h"
#include "Core/ContextRenderer.h"
#include "LowLevel_Renderer/Materials/Material.h"
#include "LowLevel_Renderer/Shader/Shader.h"
#include "Math/Transform.h"

template <typename Type>
class PrimitiveMesh
{
public:
	using vertex_type = Vertex<Type>;
	using Transform = Math::Transform<Type>;

	PrimitiveMesh();
	virtual ~PrimitiveMesh();

	virtual void load();
	virtual void render(ContextRenderer& contextRenderer);

	Transform transform;

protected:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
	Shader* m_shaders;

	Material m_material;
};

template <typename Type>
PrimitiveMesh<Type>::PrimitiveMesh()
	: transform(Transform{}), m_vao(0), m_vbo(0), m_ebo(0), m_shaders(nullptr), m_material(Material{})
{
	load();
}

template <typename Type>
PrimitiveMesh<Type>::~PrimitiveMesh()
{
	DELETE_BUFFER_WITH_ELEMENTS(m_shaders->program)

	if (m_shaders)
	{
		delete m_shaders;
		m_shaders = nullptr;
	}
}

template <typename Type>
void PrimitiveMesh<Type>::load()
{
	LOAD_VERTEX_ARRAYS(m_vao)
}

template <typename Type>
void PrimitiveMesh<Type>::render(ContextRenderer& contextRenderer)
{
	glUseProgram(m_shaders->program);
	glBindVertexArray(m_vao);

	m_shaders->setMat4("projection", contextRenderer.projection);
	m_shaders->setMat4("view", contextRenderer.camera.getMatrixView());
	m_shaders->setMat4("model", transform.getMatrix());

	m_shaders->setVec3("viewPostion", contextRenderer.camera.transform.position);
	m_shaders->setInt("pointLightsCount", contextRenderer.pointLights.size());

	m_shaders->setFloat("material.shininess", m_material.shininess);

	contextRenderer.directionalLight.getUniform(m_shaders);

	for (size_t i = 0; i < contextRenderer.pointLights.size(); ++i)
	{
		contextRenderer.pointLights[i].getUniform(m_shaders, i);
	}

	m_material.diffuseMap.bind(GL_TEXTURE0);
	m_material.specularMap.bind(GL_TEXTURE1);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
