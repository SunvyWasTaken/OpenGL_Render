#pragma once

struct ShaderInfo
{
	unsigned int type;
	const char* filename;
	unsigned int shaderId;
};

struct Shader
{
	static unsigned int loadShader(ShaderInfo* shaderInfo);
};
