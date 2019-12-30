#include "Graphics.h"

void initGL() 
{
	//Initialize GLEW Extensions 
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
	}

}


GLuint createVAO(unsigned int numVertices, const float vertices[])
{
	int size = numVertices * 3 * sizeof(float);

	GLuint vaoId;
	glGenBuffers(1, &vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, vaoId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	return vaoId;
}

GLuint crateIBO(unsigned int numIndicies, const unsigned int indicies[])
{
	unsigned int iboId;
	//Create IBO
	glGenBuffers( 1, &iboId );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, iboId );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, numIndicies * sizeof(GLuint), indicies, GL_STATIC_DRAW );
	return iboId;
}
