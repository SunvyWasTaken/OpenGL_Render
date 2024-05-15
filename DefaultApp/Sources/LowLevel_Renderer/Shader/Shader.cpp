#include "Shader.h"

#include <glad/glad.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <filesystem>

#include "Math/Color.h"


namespace
{
	std::string readShaderFile(const char* filename)
	{
		std::filesystem::path path = std::filesystem::current_path() / "Ressources\\Shader" / filename;

		std::ifstream inputFile(path.c_str());
		if (!inputFile.is_open())
			throw std::runtime_error("Impossible to read shader file");

		std::stringstream buffer;
		buffer << inputFile.rdbuf();

		inputFile.close();
		return buffer.str();
	}
}

Shader* Shader::loadShader(ShaderInfo* shaderInfo)
{
	if (shaderInfo == nullptr)
		throw std::runtime_error("Shader info not valid");

	auto program = glCreateProgram();
	auto* entry = shaderInfo;

	while (entry->type != GL_NONE)
	{
		auto shaderId = glCreateShader(entry->type);
		entry->shaderId = shaderId;

		auto str = readShaderFile(entry->filename);
		const char* shaderData = str.c_str();

		glShaderSource(shaderId, 1, &shaderData, nullptr);
		glCompileShader(shaderId);

		GLint hasCompiled;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &hasCompiled);

		if (!hasCompiled)
		{
			GLint infoLogSize;
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogSize);
			
			GLchar* logBuffer = new GLchar[infoLogSize + 1];
			glGetShaderInfoLog(shaderId, infoLogSize, &infoLogSize, logBuffer);

			std::cout << "FileName : " << entry->filename << std::endl;
			std::cerr << logBuffer << std::endl;

			delete[] logBuffer;
			throw std::runtime_error("Shader does not compile");
		}

		glAttachShader(program, shaderId);
		++entry;
	}

	glLinkProgram(program);

	GLint hasLinked;
	glGetProgramiv(program, GL_LINK_STATUS, &hasLinked);

	if (!hasLinked)
	{
		GLint infoLogSize;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogSize);

		GLchar* logBuffer = new GLchar[infoLogSize + 1];
		glGetProgramInfoLog(program, infoLogSize, &infoLogSize, logBuffer);

		std::cerr << logBuffer << std::endl;

		delete[] logBuffer;
		throw std::runtime_error("Program does not linked");
	}
	
	return new Shader(program);
}

Shader::Shader(unsigned programId)
	: program(programId)
{
}

void Shader::setFloat(const GLchar* variable, float value)
{
	glUniform1f(glGetUniformLocation(program, variable), value);
}

void Shader::setInt(const GLchar* variable, int value)
{
	glUniform1i(glGetUniformLocation(program, variable), value);
}

void Shader::setVec3(const GLchar* variable, Math::Point3D<float>& values)
{
	glUniform3fv(glGetUniformLocation(program, variable), 1, reinterpret_cast<float*>(&values));
}

void Shader::setVec3(const GLchar* variable, Math::Color<float>& values)
{
	glUniform3fv(glGetUniformLocation(program, variable), 1, reinterpret_cast<float*>(&values));
}

void Shader::setMat4(const GLchar* variable, const Math::Mat4<float>& values)
{
	glUniformMatrix4fv(glGetUniformLocation(program, variable), 1, 0, values.data());
}

void Shader::setFloat(const GLchar* variable, float value) const
{
	setFloat(variable, value);
}

void Shader::setInt(const GLchar* variable, int value) const
{
	setInt(variable, value);
}

void Shader::setVec3(const GLchar* variable, Math::Point3D<float>& values) const
{
	setVec3(variable, values);
}

void Shader::setVec3(const GLchar* variable, Math::Color<float>& values) const
{
	setVec3(variable, values);
}

void Shader::setMat4(const GLchar* variable, const Math::Mat4<float>& values) const
{
	setMat4(variable, values);
}
