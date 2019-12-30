#pragma once
#include "GraphicsTypeDef.h"

GLuint createShaderProgram(const ShaderList& vertShaders, const ShaderList& fragShaders);
void createShader(GLuint programId, GLenum shaderType, const char* shaderSource);

