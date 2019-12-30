#include "main.h"
using namespace std;

GLuint programId;
GLuint VBO, normVBO, tcVBO;
GLuint IBO;
GLuint cubeVAO;
GLuint textureId;

int main(int argc, char* argv[]) {

	initSDL();
	initGL();
	initApp();
	mainLoop(handleKeys, updateStep);
	destroySDL();
	return 0;
}

void initApp() {

	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glReadBuffer(GL_BACK);
	glDrawBuffer(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	glClearDepth(1.0);
	glEnable(GL_TEXTURE_2D);

	//Init shaders
	ShaderList vertShaders;
	vertShaders.push_back(readFile("../../../../../resources/shaders/texture.vs"));
	ShaderList fragShaders;
	fragShaders.push_back(readFile("../../../../../resources/shaders/texture.fs"));

	programId = createShaderProgram(vertShaders, fragShaders);
	SDL_Log("Created GL program id: %d", programId);

	try{
		textureId = createTexture("../../../../../resources/textures/brick1.jpg");
		SDL_Log("Created texture: %d", textureId);
	}
	catch (const std::exception& ex) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Encountered error", ex.what(), NULL);
	}

	//Init geometry
	unsigned int sizeOfVertex = cube::numPointsPerVertex * sizeof(cube::CoordType);
	unsigned int sizeOfTextCoord = 2 * sizeof(cube::CoordType);
	unsigned int sizeOfIndex = cube::numPointsPerVertex * sizeof(cube::IndexType);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, cube::numVertices * sizeOfVertex, cube::vertices, GL_STATIC_DRAW);

	//Normal VBO
	glGenBuffers(1, &normVBO);
	glBindBuffer(GL_ARRAY_BUFFER, normVBO);
	glBufferData(GL_ARRAY_BUFFER, cube::numVertices * sizeOfVertex, cube::normals, GL_STATIC_DRAW);

	//TextureCoord VBO
	glGenBuffers(1, &tcVBO);
	glBindBuffer(GL_ARRAY_BUFFER, tcVBO);
	glBufferData(GL_ARRAY_BUFFER, cube::numVertices * sizeOfTextCoord, cube::texcoords, GL_STATIC_DRAW);

	//Indices IBO
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube::numIndices * sizeOfIndex, cube::indices, GL_STATIC_DRAW);



	//Cube VAO
	int vertexAttribLoc = 0;
	int normalAttribLoc = 1;
	int textCoordAttribLoc = 2;

	glGenVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);

	//add vertices VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(vertexAttribLoc, cube::numPointsPerVertex, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(vertexAttribLoc);
	//add normals VBO
	glBindBuffer(GL_ARRAY_BUFFER, normVBO);
	glVertexAttribPointer(normalAttribLoc, cube::numPointsPerVertex, GL_FLOAT, GL_TRUE, 0, (void*)0);
	glEnableVertexAttribArray(normalAttribLoc);
	//add texcoords VBO
	glBindBuffer(GL_ARRAY_BUFFER, tcVBO);
	glVertexAttribPointer(textCoordAttribLoc, 2, GL_FLOAT, GL_TRUE, 0, (void*)0);
	glEnableVertexAttribArray(textCoordAttribLoc);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glVertexAttribPointer(5, 3, GL_UNSIGNED_SHORT, GL_FALSE, 0, (void*)0);
	glBindVertexArray(0);

	//reset all object bindings
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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
		glm::vec3(0, 0, 1), // Camera position in World Space
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(cubeVAO);
	glDrawElements(GL_TRIANGLES, cube::numIndices * cube::numPointsPerVertex, GL_UNSIGNED_SHORT, (void*)0);
	glBindVertexArray(0);

	// enable shader program
	glUseProgram(programId);


}