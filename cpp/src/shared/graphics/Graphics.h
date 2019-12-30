#pragma once
#include "GraphicsTypeDef.h"


void initGL();
GLuint createVAO(unsigned int numVertices, const float vertices[]);
GLuint crateIBO(unsigned int numIndicies, const unsigned int indicies[]);
