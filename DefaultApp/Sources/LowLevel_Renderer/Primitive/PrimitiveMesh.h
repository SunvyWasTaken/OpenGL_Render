#pragma once
#include "PrimitiveUtils.h"
#include "Vertex.h"
#include "Core/ContextRenderer.h"
#include "LowLevel_Renderer/Materials/Material.h"
#include "LowLevel_Renderer/Shader/Shader.h"
#include "Math/Transform.h"
#include <memory>

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
	Material* getMaterial() { return m_material.get(); }
	void applyMaterial(std::shared_ptr<Material> material);
	void addShaders(std::vector<ShaderInfo> shaders);

	Transform transform;

	int triCount;

protected:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
	Shader* m_shaders;
	
	std::shared_ptr<Material> m_material;
};

template <typename Type>
PrimitiveMesh<Type>::PrimitiveMesh()
	: transform(Transform{}), triCount(0), m_vao(0), m_vbo(0), m_ebo(0), m_shaders(nullptr), m_material(std::unique_ptr<Material>(nullptr))
{
	LOAD_VERTEX_ARRAYS(this->m_vao)
}

template <typename Type>
PrimitiveMesh<Type>::~PrimitiveMesh()
{
	if (m_shaders)
	{
		DELETE_BUFFER_WITH_ELEMENTS(m_shaders->program)

		delete m_shaders;
		m_shaders = nullptr;
	}
}

template <typename Type>
void PrimitiveMesh<Type>::load()
{
	LOAD_BASIC_VERTEX_ATTRIB_POINTER()

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

template <typename Type>
void PrimitiveMesh<Type>::render(ContextRenderer& contextRenderer)
{
	if(!m_shaders)
		return;

	glUseProgram(m_shaders->program);
	glBindVertexArray(m_vao);

	m_shaders->setMat4("projection", contextRenderer.projection);
	m_shaders->setMat4("view", contextRenderer.camera.getMatrixView());
	m_shaders->setMat4("model", transform.getMatrix());

	m_shaders->setVec3("viewPosition", contextRenderer.camera.transform.position);
	m_shaders->setInt("pointLightsCount", (*contextRenderer.pointLights).size());

	if(m_material)
	{
		m_shaders->setInt("material.diffuse", 0);
		m_shaders->setInt("material.specular", 1);
		m_shaders->setFloat("material.shininess", m_material->shininess);
	}

	contextRenderer.directionalLight.getUniform(m_shaders);
	
	for (auto light = contextRenderer.pointLights->begin() ; light != contextRenderer.pointLights->end(); ++light)
	{
		light->get()->getUniform(m_shaders, light - contextRenderer.pointLights->begin());
	}

	if (m_material)
		m_material->Bind();
}

template <typename Type>
void PrimitiveMesh<Type>::applyMaterial(std::shared_ptr<Material> material)
{
	m_material = material;
}

template <typename Type>
void PrimitiveMesh<Type>::addShaders(std::vector<ShaderInfo> shaders)
{
	if (shaders.size() < 0)
		return;

	m_shaders = Shader::loadShader(shaders);
	glUseProgram(m_shaders->program);
}
