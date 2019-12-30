#pragma once

#include <string>


//sdl headers
#include <SDL2/SDL.h>

extern SDL_Window* ptrWindow;
extern SDL_GLContext winContext;

void initSDL(int screenWidth = 640, int screenHeight = 480);
void mainLoop( 
	void (*handleKeys)(unsigned char key, int x, int y),
	void (*updateStep)()
);
void destroySDL();
