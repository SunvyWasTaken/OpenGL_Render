#pragma once
#include <string>
#include <glad/glad.h>

#include "Math/Color.h"
#include "Math/Matrix.h"
#include "Math/Point.h"

struct ShaderInfo
{
	unsigned int type;
	const char* filename;
	unsigned int shaderId;
};

struct Shader
{
	static Shader* loadShader(ShaderInfo* shaderInfo);

	explicit Shader(unsigned int programId);

	void setFloat(const GLchar* variable, float value);
	void setInt(const GLchar* variable, int value);
	void setVec3(const GLchar* variable, Math::Point3D<float>& values);
	void setVec3(const GLchar* variable, Math::Color<float>& values);
	void setMat4(const GLchar* variable, const Math::Mat4<float>& values);

	void setFloat(const GLchar* variable, float value) const;
	void setInt(const GLchar* variable, int value) const;
	void setVec3(const GLchar* variable, Math::Point3D<float>& values) const;
	void setVec3(const GLchar* variable, Math::Color<float>& values) const;
	void setMat4(const GLchar* variable, const Math::Mat4<float>& values) const;

	GLuint program;
};
