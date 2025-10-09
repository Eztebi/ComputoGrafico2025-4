#pragma once
#include "glad.h"
#include <vector>
#include <string>

static class ShaderFuncs {
public:
	static GLuint CreateShader(GLenum eShaderType, const std::string& strShaderFile);
	static GLuint CreateProgram(const std::vector<GLuint>& shaderList);
	static GLuint InitializeProgram(std::string strVertexShader, std::string strFragmentShader);
};