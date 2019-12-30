#include "main.h"
using namespace std;

GLuint programId;
GLuint VBO;
GLuint IBO;

int main(int argc, char* argv[]) {

	initSDL();
	initGL();
	initApp();
	mainLoop(handleKeys, updateStep);
	destroySDL();
	return 0;
}

void initApp() {

	//Init shaders
	ShaderList vertShaders;
	vertShaders.push_back(readFile("../../../../../resources/shaders/simple.vs"));
	ShaderList fragShaders;
	fragShaders.push_back(readFile("../../../../../resources/shaders/simple.fs"));

	programId = createShaderProgram(vertShaders, fragShaders);
	SDL_Log("Created GL program id: %d", programId);

	//Init geometry
	unsigned int sizeOfVertex = cube::numPointsPerVertex * sizeof(cube::CoordType);
	unsigned int sizeOfIndex = cube::numPointsPerVertex * sizeof(cube::IndexType);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, cube::numVertices * sizeOfVertex, cube::vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube::numIndices * sizeOfIndex, cube::indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void handleKeys(unsigned char key, int x, int y)
{
	//Toggle quad
	if (key == 'q')
	{
		SDL_Event sdlevent;
		sdlevent.type = SDL_QUIT;
		SDL_PushEvent(&sdlevent);
	}

	else if (key == SDLK_ESCAPE) {
		SDL_Event sdlevent;
		sdlevent.type = SDL_QUIT;
		SDL_PushEvent(&sdlevent);
	}

}

void updateStep()
{
	//define the projection matrix
	float fovy = 45.0f;
	float znear = 0.01f;
	float zfar = 100.0f;
	float aspectRatio = 4.0f / 3.0f;
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(fovy), aspectRatio, znear, zfar);

	//define the view matrix
	glm::mat4 viewMatrix = glm::lookAt(
		glm::vec3(2.5, 2.5, 2.5), // Camera position in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	//define the model matrix
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	//calculate the model x view x projection matrix (mvp)
	glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

	//get position of mvp in shader
	GLuint locMvp = glGetUniformLocation(programId, "mvp");
	//set value of mvp in shader based on location
	glUniformMatrix4fv(locMvp, 1, GL_FALSE, &mvp[0][0]);

	//Render screen
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// enable shader program
	glUseProgram(programId);

	// bind VBOs before drawing
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// enable vertex arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, (void*)0);

	// primitive type, # of indices, data type, offset to indices
	glDrawElements(GL_TRIANGLES, cube::numIndices * cube::numPointsPerVertex, GL_UNSIGNED_SHORT, (void*)0);               // 

	// disable vertex arrays
	glDisableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}