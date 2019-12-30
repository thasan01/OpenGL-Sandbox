#include "WindowSDL.h"

SDL_Window* ptrWindow = NULL;
SDL_GLContext winContext;

std::string getSDLError(const std::string& prefix) {
	return prefix + std::string(SDL_GetError());
}

void initSDL(int screenWidth, int screenHeight) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw getSDLError("SDL could not initialize! SDL Error:");
	}

	//Create window
	ptrWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (ptrWindow == NULL) {
		throw getSDLError("Window failed to be created. SDL Error:");
	}

	winContext = SDL_GL_CreateContext(ptrWindow);
	if (winContext == NULL) {
		throw getSDLError("Could not create OpenGL Context. SDL Error:");
	}



}

void mainLoop(
	void (*handleKeys)(unsigned char key, int x, int y),
	void (*updateStep)() ) 
{
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//Enable text input
	SDL_StartTextInput();

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			//Handle keypress with current mouse position
			else if (e.type == SDL_TEXTINPUT)
			{
				int x = 0, y = 0;
				SDL_GetMouseState(&x, &y);
				handleKeys(e.text.text[0], x, y);
			}


		}

		updateStep();

		//Update screen
		SDL_GL_SwapWindow(ptrWindow);

	}
	//Disable text input
	SDL_StopTextInput();

}

void destroySDL()
{
	SDL_GL_DeleteContext(winContext);
	SDL_DestroyWindow(ptrWindow);
}
