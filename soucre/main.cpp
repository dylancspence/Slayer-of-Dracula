
#if defined(_WIN32)||(_WIN64)
		#include "SDL.h"

#endif
#if defined(__APPLE__)
		#include "SDL2/SDL.h"
        #include "SDL2_image/SDL_image.h"

#endif
#if defined(__linux__)
		#include "SDL2/SDL.h"
#endif


#include <stdio.h>
#include <iostream>

using namespace std;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

bool loadMedia();

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gHelloWorld = SDL_LoadBMP( "Slayer-of-Dracula/image/mapp.bmp" );
	if( gHelloWorld == NULL )
	{
		//printf( "Unable to load image %s! SDL Error: %s\n", 0, SDL_GetError() );
		success = false;
	}

	return success;
}





int main(int argc, char* argv[]) {

#if defined(_WIN32)||(_WIN64)
		cout <<"Running on Window" << endl;
#endif
#if defined(__APPLE__)
		cout <<"Running on Apple" << endl;
#endif
#if defined(__linux__)
		cout <<"Running on Linux"<< endl;
#endif

    SDL_Window *window;                    // Declare a pointer

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        1024,                               // width, in pixels
        768,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );


		if(window == NULL ){
			printf("could not create window: %s\n",SDL_GetError());
			return 1;


		}
		SDL_Surface* screenSurface = NULL;

		screenSurface = SDL_GetWindowSurface( window );

		SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format,186,186,186));

		SDL_UpdateWindowSurface( window );
//render start
		//Load media
				if( !loadMedia() )
				{
					printf( "Failed to load media!\n" );
				}
				else
				{
					//Apply the image
					SDL_BlitSurface( gHelloWorld, NULL, screenSurface, NULL );

					//Update the surface
					SDL_UpdateWindowSurface( window );

					//Wait two seconds
					//SDL_Delay( 2000 );
				}
//render end

		SDL_Delay(5000);

		SDL_DestroyWindow(window);

		SDL_Quit();
		return 0;



};
