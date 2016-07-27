
#if defined(_WIN32)||(_WIN64)
		#include "SDL.h"

#endif
#if defined(__APPLE__)
		#include "SDL2/SDL.h"
        #include "SDL2_image/SDL_image.h"
		#include "SDL2_ttf/SDL_ttf.h"

#endif
#if defined(__linux__)
		#include "SDL2/SDL.h"
#endif


#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
//The dimensions of the level
const int LEVEL_WIDTH = 2048;
const int LEVEL_HEIGHT = 1570;

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 785;

bool keyon = true;
 int kx =790;
 int ky =550;
 int kx2 =2000;
 int ky2 =550;
 string healthnum;

 //health number
int healthn = 100;

int ammon = 30;

string ammonum ;
//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );

		#ifdef _SDL_TTF_H
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};
//The dot that will move around on the screen
class Player
{
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 2;
		static const int DOT_HEIGHT = 2;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 10;

		//Initializes the variables
		Player();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move();

		//Shows the dot on the screen relative to the camera
		void render( int camX, int camY );

		//Position accessors
		int getPosX();
		int getPosY();

    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;
};
LTexture ghealthTexture;
LTexture gammoTexture;
LTexture gslotTexture;
LTexture gslotorbTexture;

LTexture ammoTexture;
LTexture healthTexture;
LTexture damageTexture;
LTexture orbTexture;

class GuiHealth
{
public:
	//double healthnum = 100;
	void render( int camX, int camY );
	void keyrender( int camX, int camY );

	void takehealth();


};
void GuiHealth::render( int camX, int camY )
{
    //Show the dot relative to the camera
	ghealthTexture.render( 0,0);
}
class GuiAmmo{
public:
	void arender( int camX, int camY );

};



void GuiAmmo::arender( int camX, int camY )
{
    //Show the dot relative to the camera
	gammoTexture.render( 0,155);
}

class GuiKey{
public:
	void keyrender( int camX, int camY );
	void keyorbrender( int camX, int camY );
};
void GuiKey::keyrender( int camX, int camY )
{
	if(keyon == true){
    //Show the dot relative to the camera
	gslotTexture.render( kx,ky);
	}
	if(keyon == false){
	    //Show the dot relative to the camera
		gslotTexture.render( 2000,550);
		}
}
void GuiKey::keyorbrender( int camX, int camY )
{
	if(keyon == true){
	    //Show the dot relative to the camera
		gslotorbTexture.render( kx2,ky2);
		}
	if(keyon == false){
		    //Show the dot relative to the camera
			gslotorbTexture.render( 790,550);
			}
}


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font *gFont = NULL;
TTF_Font *gFont2 = NULL;
//Rendered texture
LTexture gTextTexture;
//Rendered texture
LTexture aTextTexture;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;


//Scene textures
LTexture gDotTexture;
LTexture gBGTexture;

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}



void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}

	//Return success
	return mTexture != NULL;
}


int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

Player::Player()
{
    //Initialize the offsets
    mPosX = 100;
    mPosY = 1430;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

void Player::handleEvent( SDL_Event& e )
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
	//input for testing slot
							if (state[SDL_SCANCODE_1]){
								printf( "1 key has been press\n" );
								keyon =false;


							}
							if (state[SDL_SCANCODE_2]){
							printf( "1 key has been press\n" );
							keyon =true;

														}

							//this is to test the damage
							if (state[SDL_SCANCODE_E]){
														printf( "Player has been damaged\n" );
														healthn= healthn - 1;
														healthnum = to_string(healthn);
														SDL_Color textColor = { 0, 0, 0 };
														gTextTexture.loadFromRenderedText( healthnum, textColor);
																					}
							//this is to test the heal
							if (state[SDL_SCANCODE_R]){
																					printf( "Player has been healed\n" );
																					healthn= healthn + 1;
																					healthnum = to_string(healthn);
																					SDL_Color textColor = { 0, 0, 0 };
																					gTextTexture.loadFromRenderedText( healthnum, textColor);
							}
							//button to fire
							// it will stop firing at 0
												if(ammon > 0)	{
							if (state[SDL_SCANCODE_Q] && e.key.repeat == 0){
																					printf( "Player through knife\n" );
																					ammon= ammon - 1;
																					ammonum = to_string(ammon);
																					SDL_Color textColor = { 0, 0, 0 };
																					aTextTexture.loadFromRenderedText( ammonum, textColor);
																												}
							}
												//this is to test the reload
														if (state[SDL_SCANCODE_3]){
																												printf( "Player pickup ammo\n" );
																												ammon= ammon + .5;
																												ammonum = to_string(ammon);
																												SDL_Color textColor = { 0, 0, 0 };
																												aTextTexture.loadFromRenderedText( ammonum, textColor);
																																			}
}

void Player::move()
{
    //Move the dot left or right
    mPosX += mVelX;

    //If the dot went too far to the left or right
    if( ( mPosX < 25 ) || ( mPosX + DOT_WIDTH > 1941 ) )
    {
        //Move back
        mPosX -= mVelX;
    }

    //Move the dot up or down
    mPosY += mVelY;

    //If the dot went too far up or down
    if( ( mPosY < 25 ) || ( mPosY + DOT_HEIGHT > 1440 ) )
    {
        //Move back
        mPosY -= mVelY;
    }
}

void Player::render( int camX, int camY )
{
    //Show the dot relative to the camera
	gDotTexture.render( mPosX - camX, mPosY - camY );
}

int Player::getPosX()
{
	return mPosX;
}

int Player::getPosY()
{
	return mPosY;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Dracula", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				 //Initialize SDL_ttf
								if( TTF_Init() == -1 )
								{
									printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
									success = false;
								}

			}
		}


	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if( !gDotTexture.loadFromFile( "Slayer-of-Dracula/image/playerfin.bmp" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	//Load background texture
	if( !gBGTexture.loadFromFile( "Slayer-of-Dracula/image/bmap.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}


	//Load health texture
		if( !ghealthTexture.loadFromFile( "Slayer-of-Dracula/image/healthbard.bmp" ) )
		{
			printf( "Failed to load background texture!\n" );
			success = false;
		}
		//Load ammo texture
				if( !gammoTexture.loadFromFile( "Slayer-of-Dracula/image/abar.bmp" ) )
				{
					printf( "Failed to load background texture!\n" );
					success = false;
				}
				//Load background texture
			if( !gslotTexture.loadFromFile( "Slayer-of-Dracula/image/slot.png" ) )
								{
					printf( "Failed to load background texture!\n" );
									success = false;
				}
			if( !gslotorbTexture.loadFromFile( "Slayer-of-Dracula/image/slotorb.png" ) )
											{
								printf( "Failed to load background texture!\n" );
												success = false;
							}

			gFont = TTF_OpenFont( "Slayer-of-Dracula/Alexis Expanded.ttf",100 );
				if( gFont == NULL )
				{
					printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
				else
					{
						//Render text
						SDL_Color textColor = { 0, 0, 0 };
						healthnum = to_string(healthn);
						if( !gTextTexture.loadFromRenderedText( healthnum, textColor ) )
						{
							printf( "Failed to render text texture!\n" );
							success = false;
						}


					}

				gFont2 = TTF_OpenFont( "Slayer-of-Dracula/Alexis Expanded.ttf",100 );
								if( gFont2 == NULL )
								{
									printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
									success = false;
								}
								else
									{
										//Render text
										SDL_Color textColor = { 0, 0, 0 };
										ammonum = to_string(ammon);
										if( !aTextTexture.loadFromRenderedText( ammonum, textColor ) )
										{
											printf( "Failed to render text texture!\n" );
											success = false;
										}
									}


	return success;
}

void close()
{
	//Free loaded images
	gDotTexture.free();
	gBGTexture.free();
	ghealthTexture.free();
	gammoTexture.free();
	gslotTexture.free();
	gslotorbTexture.free();
	gTextTexture.free();
	aTextTexture.free();
	healthTexture.free();
	damageTexture.free();
	ammoTexture.free();
	orbTexture.free();

	//Free global font
		TTF_CloseFont( gFont );
		gFont = NULL;
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
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
//int x = 100 , y = 100;
		//Start up SDL and create window
			if( !init() )
			{
				printf( "Failed to initialize!\n" );
			}
			else
			{
				//Load media
				if( !loadMedia() )
				{
					printf( "Failed to load media!\n" );
				}
				else
				{
					//Main loop flag
					bool quit = false;

					//Event handler
					SDL_Event e;

					//The dot that will be moving around on the screen
					Player dot;

					// Gui health
					GuiHealth health;
					GuiAmmo ammo;
					GuiKey key;


					//The camera area
					SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
					//SDL_Rect level = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

					//While application is running
					while( !quit )
					{
						//Handle events on queue
						while( SDL_PollEvent( &e ) != 0 )
						{
							//User requests quit
							if( e.type == SDL_QUIT )
							{
								quit = true;
							}

							//Handle input for the dot
							dot.handleEvent( e );
						}

						//Move the dot
						dot.move();

						//Center the camera over the dot
						camera.x = ( dot.getPosX() + Player::DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
						camera.y = ( dot.getPosY() + Player::DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;
//level width 2048
						// level height 1570
						//Keep the camera in bounds
						if( camera.x < 0 )
						{
							camera.x = 0;
						}
						if( camera.y < 0 )
						{
							camera.y = 0;
						}
						if( camera.x > LEVEL_WIDTH - camera.w )
						{
							camera.x = LEVEL_WIDTH - camera.w;
						}
						if( camera.y > LEVEL_HEIGHT - camera.h )
						{
							camera.y = LEVEL_HEIGHT - camera.h;
						}




						//Clear screen
						SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
						SDL_RenderClear( gRenderer );

						//Render background
						gBGTexture.render( 0, 0, &camera );

						//Render objects
						dot.render( camera.x, camera.y );

						//Render objects
						health.render( camera.x, camera.y );
						key.keyrender( camera.x, camera.y );
						key.keyorbrender( camera.x, camera.y );
						ammo.arender( camera.x, camera.y );
						//Render current frame
					gTextTexture.render( 150, 50);
					aTextTexture.render( 150, 200);



						//Update screen
						SDL_RenderPresent( gRenderer );
					}
				}
			}

			//Free resources and close SDL
			close();

			return 0;



};
