
#if defined(_WIN32)||(_WIN64)
		#include "SDL.h"
#endif
#if defined(__APPLE__)
		#include "SDL2/SDL.h"
#endif
#if defined(__linux__)
		#include "SDL2/SDL.h"
#endif


#include <stdio.h>

int main(int argc, char* argv[]) {

    SDL_Window *window;                    // Declare a pointer

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

		if(window == NULL ){
			printf("could not create window: %s\n",SDL_GetError());
			return 1;


		}
		SDL_Surface* screenSurface = NULL;

		screenSurface = SDL_GetWindowSurface( window );

		SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0,42,254));

		SDL_UpdateWindowSurface( window );

		SDL_Delay(3000);

		SDL_DestroyWindow(window);

		SDL_Quit();
		return 0;



};
