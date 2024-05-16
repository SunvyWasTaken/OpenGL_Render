#include "PointLight.h"

#include <string>

void PointLight::getUniform(Shader* shader)
{
}

void PointLight::getUniform(Shader* shader, size_t index)
{
	std::string pre = "pointLights[" + std::to_string(index) + "]";

	shader->setVec3( std::string(pre+".direction").c_str(), direction);
	shader->setVec3(std::string(pre + ".ambient").c_str(),ambient);
	shader->setVec3(std::string(pre + ".diffuse").c_str(), diffuse);
	shader->setVec3(std::string(pre + ".specular").c_str(),specular);

	shader->setFloat(std::string(pre + ".constant").c_str(), constant);
	shader->setFloat(std::string(pre + ".linear").c_str(), linear);
	shader->setFloat(std::string(pre + ".quadratic").c_str(), quadratic);
;}
