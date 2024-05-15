#include "DirectionalLight.h"

void DirectionalLight::getUniform(Shader* shader)
{
	shader->setVec3("directionalLight.direction", direction);
	shader->setVec3("directionalLight.ambient", ambient);
	shader->setVec3("directionalLight.diffuse", diffuse);
	shader->setVec3("directionalLight.specular", specular);
}

void DirectionalLight::getUniform(Shader* shader, size_t index)
{
}
