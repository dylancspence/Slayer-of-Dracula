//Please read
//instuction for test
//Press 1 &2 to test slot, press Q& 3 to test ammo, press e & r to test healt
#if defined(_WIN32)||(_WIN64)
		#include "SDL.h"
		#include "SDL_image.h"
	#include "SDL_mixer.h"
		#include "SDL_ttf.h"


#endif
#if defined(__APPLE__)
		#include "SDL2/SDL.h"
        #include "SDL2_image/SDL_image.h"
 	 	 #include "SDL2_mixer/SDL_mixer.h"
		#include "SDL2_ttf/SDL_ttf.h"
		#include "unistd.h"

#endif
#if defined(__linux__)
		#include "SDL2/SDL.h"
		#include "SDL2_image/SDL_image.h"
		#include "SDL2_mixer/SDL_mixer.h"
		#include "SDL2_ttf/SDL_ttf.h"
		#include "unistd.h"
#endif


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
using namespace std;
//The dimensions of the level
const int LEVEL_WIDTH = 3072;
const int LEVEL_HEIGHT = 2355;

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 785;
SDL_Rect dam = {500,2150,50,50};

SDL_Rect test = {1000,2100,10,100};
SDL_Rect hl = {1500,2100,10,100};

bool testfire = false;

bool playerfire = false;
bool throwknive = false;
bool playerfire1 = false;
bool throwknive1 = false;

Mix_Music *gMusic = NULL;
Mix_Chunk *gBing = NULL;


bool keyon = true;
 int kx =790;
 int ky =550;
 int kx2 =2000;
 int ky2 =550;
 string healthnum;
 SDL_Rect col = {200,2200,10,10};
 SDL_Rect primary = {1100,225,20,100};
 SDL_Rect primary2 = {2000,225,20,200};
 SDL_Rect boss = {1500,225,100,200};
 // x 2968 y 1900
 SDL_Rect cand = {2968,1900,100,200};
 // x 2700 y 2200
 SDL_Rect ehand = {1500,1700,100,200};
 SDL_Rect rangehand = {ehand.x-300 ,ehand.y-300 , 600,600};

 SDL_Rect losebar = {200,-1000,100,200};
 SDL_Rect wonbar = {200,-1000,100,200};

 SDL_Rect colum = {500,2200,10,10};
 //enemy bullet
 SDL_Rect bullet = {800,2200,10,10};
 //throw knive
 SDL_Rect tknive = {10,2000,10,10};
 SDL_Rect Range = {200 , 1500 , 500,1000};

 SDL_Rect orb = {1500,650,50,50};
 SDL_Rect playerPos = {100,2200,50,100};
 SDL_Rect skull1Pos;

 		// Set the x, y, width and height SDL Rectangle values
 		//skull1Pos.x = 109;
 		//skull1Pos.y = 375;
 	//	skull1Pos.w = 64;
 		//skull1Pos.h = 65;
 SDL_Surface* loadedSurface;
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
		//The X and Y offsets of the dot
				int mPosX, mPosY;

				//The velocity of the dot
				int mVelX, mVelY;


    };
LTexture ghealthTexture;
LTexture gammoTexture;
LTexture gslotTexture;
LTexture gslotorbTexture;
LTexture standTexture;
LTexture primaryTexture;
LTexture primary2Texture;
LTexture ammoTexture;
LTexture healthTexture;
LTexture health2Texture;
LTexture damageTexture;
LTexture orbTexture;
LTexture bullTexture;
LTexture kniTexture;
LTexture bossTexture;
LTexture candleTexture;
LTexture handTexture;
LTexture wonTexture;
LTexture loseTexture;


class Stand
{
public:
	void render(int x, int y);
};
void Stand:: render(int x, int y){
	standTexture.render(colum.x - x,colum.y - y);
}
class bar
{
public:
	void lrender();
	void wrender();
};
void bar:: lrender(){
	loseTexture.render(losebar.x,losebar.y );
}
void bar:: wrender(){
	wonTexture.render(wonbar.x ,wonbar.y );
}
class Boss
{
public:
	void render(int x, int y);
};
void Boss:: render(int x, int y){
	bossTexture.render(boss.x - x,boss.y - y);
}
class Prime
{
public:
	void render(int x, int y);
	void render2(int x, int y);
};
void Prime:: render(int x, int y){
	primaryTexture.render(primary.x - x,primary.y - y);
}
void Prime:: render2(int x, int y){
	primary2Texture.render(primary2.x - x,primary2.y - y);
}

class Orb
{
public:
	void render(int x, int y);
};
void Orb:: render(int x, int y){
	orbTexture.render(orb.x - x,orb.y - y);
}
class EvilHand
{
public:
	void render(int x, int y);
};
void EvilHand:: render(int x, int y){
	handTexture.render(ehand.x - x,ehand.y - y);
}
class Knive
{
public:
	void render(int x, int y);
};
void Knive:: render(int x, int y){
	kniTexture.render(tknive.x - x,tknive.y - y);
}

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

class candle{
public:

	void render(int x, int y);
};

void candle::render(int x, int y){
	candleTexture.render(cand.x - x,cand.y - y);
}




class damage{
public:

	void render(int x, int y);
};

void damage::render(int x, int y){
	damageTexture.render(dam.x - x,dam.y - y);
}
class bull{
public:

	void render(int x, int y);
};

void bull::render(int x, int y){
	bullTexture.render(bullet.x - x,bullet.y - y);
}


class heal{
public:

	void rendera(int x2, int y2);
	void renderb(int x2, int y2);
};

void heal::rendera(int x2, int y2){
	healthTexture.render(test.x - x2 , test.y -y2);
}
void heal::renderb(int x2, int y2){
	health2Texture.render(hl.x - x2 , hl.y -y2);
}

class Ammo{
public:

	void arender(int x, int y);
};

void Ammo:: arender(int x, int y){
	ammoTexture.render(col.x- x,col.y- y);
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
TTF_Font *gFont3 = NULL;
//Rendered texture
LTexture gTextTexture;
//Rendered texture
LTexture aTextTexture;
LTexture hTextTexture;

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
	loadedSurface = IMG_Load( path.c_str() );
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
    mPosX = playerPos.x;
    mPosY = playerPos.y;

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
							//	keyon =false;


							}
							if (state[SDL_SCANCODE_2]){
							printf( "1 key has been press\n" );
						//	keyon =true;

														}

							//this is to test the damage

							//this is to test the heal
							/*if (state[SDL_SCANCODE_R]){
																					printf( "Player has been healed\n" );
																					healthn= healthn + 1;
																					healthnum = to_string(healthn);
																					SDL_Color textColor = { 0, 0, 0 };
																					gTextTexture.loadFromRenderedText( healthnum, textColor);
							}*/
							//button to fire
							// it will stop firing at 0
												if(ammon > 0)	{
							if (state[SDL_SCANCODE_Q] && playerfire  == false && ammon >= 0){
																					printf( "Player through knife\n" );
																					ammon= ammon - 1;
																					ammonum = to_string(ammon);
																					SDL_Color textColor = { 0, 0, 0 };
																					aTextTexture.loadFromRenderedText( ammonum, textColor);

																					playerfire = true;
																					throwknive = true;



																					}
							}
												/*if (state[SDL_SCANCODE_E] && playerfire  == false && ammon >= 0){
																																	printf( "Player through knife\n" );
																																	ammon= ammon - 1;
																																	ammonum = to_string(ammon);
																																	SDL_Color textColor = { 0, 0, 0 };
																																	aTextTexture.loadFromRenderedText( ammonum, textColor);

																																	playerfire1 = true;
																																	throwknive1 = true;



																																	}
*/


												//this is to test the reload



}
/*
void damage::render(int x, int y){
	SDL_Rect renderQuad = { 300, 300,100, 100 };
	loadedSurface = SDL_LoadBMP("images/skull.bmp");
	SDL_Texture *eye = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

	SDL_RenderCopy( gRenderer, eye,NULL, &renderQuad );
}
*/
void Player::move()
{
    //Move the dot left or right
    mPosX += mVelX;
    playerPos.x = mPosX;
   // tknive.x = playerPos.x;

    //If the dot went too far to the left or right
    if( ( mPosX < 25 ) || ( mPosX + DOT_WIDTH > 2900 ) )
    {
        //Move back
        mPosX -= mVelX;
        playerPos.x = mPosX;
    	//tknive.x = playerPos.x;

    }

    //Move the dot up or down
    mPosY += mVelY;
    playerPos.y = mPosY;
    tknive.y = playerPos.y;

    //If the dot went too far up or down
    if( ( mPosY < 25 ) || ( mPosY + DOT_HEIGHT > 2200 ) )
    {
        //Move back
        mPosY -= mVelY;
        playerPos.y = mPosY;
        tknive.y = playerPos.y;
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
		gWindow = SDL_CreateWindow( "Slayer of Dracula", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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

	// load damage
	if( !damageTexture.loadFromFile( "Slayer-of-Dracula/image/eye.bmp" ) )
		{
			printf( "Failed to load dot texture!\n" );
			success = false;
		}
	// load hand
		if( !handTexture.loadFromFile( "Slayer-of-Dracula/image/ehand.bmp" ) )
			{
				printf( "Failed to load dot texture!\n" );
				success = false;
			}
		// load
	// load candle
		if( !candleTexture.loadFromFile( "Slayer-of-Dracula/image/candle.bmp" ) )
			{
				printf( "Failed to load dot texture!\n" );
				success = false;
			}
		//lose /won
		if( !loseTexture.loadFromFile( "Slayer-of-Dracula/image/losebar.bmp" ) )
					{
						printf( "Failed to load dot texture!\n" );
						success = false;
					}
		if( !wonTexture.loadFromFile( "Slayer-of-Dracula/image/Wonbar.bmp" ) )
							{
								printf( "Failed to load dot texture!\n" );
								success = false;
							}
	// load column
		if( !standTexture.loadFromFile( "Slayer-of-Dracula/image/colum.bmp" ) )
			{
				printf( "Failed to load dot texture!\n" );
				success = false;
			}
		// load column
				if( !primaryTexture.loadFromFile( "Slayer-of-Dracula/image/primary.bmp" ) )
					{
						printf( "Failed to load dot texture!\n" );
						success = false;
					}
				if( !primary2Texture.loadFromFile( "Slayer-of-Dracula/image/primary.bmp" ) )
									{
										printf( "Failed to load dot texture!\n" );
										success = false;
									}
				if( !bossTexture.loadFromFile( "Slayer-of-Dracula/image/boss.bmp" ) )
													{
														printf( "Failed to load dot texture!\n" );
														success = false;
													}
				// load throwing knive
								if( !kniTexture.loadFromFile( "Slayer-of-Dracula/image/tknive.bmp" ) )
									{
										printf( "Failed to load dot texture!\n" );
										success = false;
									}

								if( !orbTexture.loadFromFile( "Slayer-of-Dracula/image/ord.bmp" ) )
											{
												printf( "Failed to load dot texture!\n" );
												success = false;
											}

	// load health
		if( !healthTexture.loadFromFile( "Slayer-of-Dracula/image/heal2.bmp" ) )
			{
				printf( "Failed to load dot texture!\n" );
				success = false;
			}
		if( !health2Texture.loadFromFile( "Slayer-of-Dracula/image/heal2.bmp" ) )
					{
						printf( "Failed to load dot texture!\n" );
						success = false;
					}
		// load health
				if( !ammoTexture.loadFromFile( "Slayer-of-Dracula/image/knive.bmp" ) )
					{
						printf( "Failed to load dot texture!\n" );
						success = false;
					}
				// load enemy bullet
								if( !bullTexture.loadFromFile( "Slayer-of-Dracula/image/bullet.bmp" ) )
									{
										printf( "Failed to load dot texture!\n" );
										success = false;
									}

	//Load background texture
	if( !gBGTexture.loadFromFile( "Slayer-of-Dracula/image/bigmap.png" ) )
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

				gFont2 = TTF_OpenFont( "Slayer-of-Dracula/Alexis Expanded.ttf",30 );
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
								 //Load sound effects
							/*
								    gBing = Mix_LoadWAV( "audio/noise.wav" );
								    if( gBing == NULL )
								    {
								        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
								        success = false;
								    }*/



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
	hTextTexture.free();


	health2Texture.free();
	damageTexture.free();
	ammoTexture.free();
	orbTexture.free();
	standTexture.free();
	primaryTexture.free();
	primary2Texture.free();
	bullTexture.free();
	kniTexture.free();
	bossTexture.free();
	candleTexture.free();
	handTexture.free();
	wonTexture.free();
	loseTexture.free();

	//Free global font
		TTF_CloseFont( gFont );
		gFont = NULL;
		 Mix_FreeChunk( gBing );
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

//testing
//float startX = dam.x;
//float startY = dam.y;
//float endX = playerPos.x;
//float endY = playerPos.y;
		bool stophand = false;
		Uint32 callback( Uint32 interval, void* param );
		bool hit = false;
		bool gamedoor = false;
		bool enemyhit = false;
		bool enemydead = false;
		bool bossdead = false;
		bool stop = false;
		bool bossturn = true;
		int turretHealth = 1;
		int bossHealth = 1;
		int handHealth = 1;
		 bossHealth = rand() % 20 +7;
			turretHealth = rand() % 5 +1;
			handHealth = rand() % 6 +1;

		int startEnemyY = dam.y+10;
		bool fireright = false;


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


					GuiHealth health;
					GuiAmmo ammo;
					GuiKey key;
					damage d;
					Ammo amo;
					heal h;
					Stand sta;
					Prime pri;
					bull b;
					Knive knive;
					Orb or1;
					Boss bos;
					candle ca;
					EvilHand eh;
					bar barr;








					SDL_Rect Player;
					Player.x = dot.mPosX;
					Player.y = dot.mPosY;
					Player.w = 50;
					Player.h = 50;

					SDL_Rect box = {0,1910,2300,10};
					SDL_Rect box2 = {0,1850,2300,10};
					SDL_Rect box3 = {0,1525,1100,100};
					SDL_Rect box4 = {0,1511,1100,2};
					SDL_Rect box5 = {1000,1225,1100,100};
					SDL_Rect box6 = {1000,1200,1100,100};
					SDL_Rect box7 = {2200,1175,1000,10};
					SDL_Rect box8 = {2200,1100,1000,10};
					SDL_Rect box9 = {900,825,1200,100};
					SDL_Rect box10 = {900,800,1200,100};
					SDL_Rect box11 = {0,700,850,10};
					SDL_Rect box12 = {0,600,850,10};
					SDL_Rect box13 = {2310,610,900,10};
					SDL_Rect box14 = {2300,530,900,10};
					SDL_Rect boxa1 = {1000,475,1000,100};
					SDL_Rect boxa2 = {1000,475,100,100};
					SDL_Rect boxa3 = {1000,450,1000,100};
					SDL_Rect boxa4 = {2000,475,100,100};
					SDL_Rect boxb = {1000,1,100,200};
					SDL_Rect boxb2 = {1900,1,150,200};
					SDL_Rect boxc = {2510,2150,1000,10};
					SDL_Rect boxc2 = {2510,2055,1000,10};

					SDL_Rect door = {1025,250,10,200};

					tknive.x = dot.mPosX;
					tknive.y = dot.mPosY;
					bullet.x = dam.x;
					bullet.y = startEnemyY;

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

						if( SDL_HasIntersection(&playerPos, &box) || SDL_HasIntersection(&playerPos, &boxc) ||SDL_HasIntersection(&playerPos, &box7)|| SDL_HasIntersection(&playerPos, &box9)){
						dot.mPosY += 10;


						}
						if( SDL_HasIntersection(&playerPos, &box2) ||SDL_HasIntersection(&playerPos, &boxc2) || SDL_HasIntersection(&playerPos, &box8)|| SDL_HasIntersection(&playerPos, &box10)){
												dot.mPosY -= 10;
												}
						if( SDL_HasIntersection(&playerPos, &box3) ||  SDL_HasIntersection(&playerPos, &box11)){
												dot.mPosY += 10;
												}
						if( SDL_HasIntersection(&playerPos, &box4) || SDL_HasIntersection(&playerPos, &box12)  ){
																		dot.mPosY -= 10;
																		}
						if( SDL_HasIntersection(&playerPos, &box5) ||  SDL_HasIntersection(&playerPos, &box13) ){
												dot.mPosY += 10;
												}
						if( SDL_HasIntersection(&playerPos, &box6) ||  SDL_HasIntersection(&playerPos, &box14)){
																		dot.mPosY -= 10;
																		}
						if( SDL_HasIntersection(&playerPos, &boxa1) ){
											dot.mPosY += 10;
														}
						if( SDL_HasIntersection(&playerPos, &boxa2) || SDL_HasIntersection(&playerPos, &boxb) ){
																	dot.mPosX -= 10;
																				}
						if( SDL_HasIntersection(&playerPos, &boxa3) ){
													dot.mPosY -= 10;
																	}
						if( SDL_HasIntersection(&playerPos, &boxa4) || SDL_HasIntersection(&playerPos, &boxb2)){
																	dot.mPosX += 10;
																				}
						if( SDL_HasIntersection(&playerPos, &orb) ){
							orb.x = -1000;
							gamedoor = true;
							keyon =false;
						}
						if(gamedoor == true){
							primary.y = -1000;
							primary2.y = -1000;
							door.y = -1000;
						}

						if(bossturn == true && stop == false){
							boss.y -= 1;

							if(boss.y == 150){
								bossturn = false;
							}
						}
						if(bossturn == false && stop == false){
													boss.y += 1;

													if(boss.y == 225){
														bossturn =true;
													}
												}




						if( SDL_HasIntersection(&playerPos, &bullet) && hit == false){

												printf( "Player got hit\n" );
															//health goes down
												healthn= healthn - 5;
												healthnum = to_string(healthn);
												SDL_Color textColor = { 0, 0, 0 };
												gTextTexture.loadFromRenderedText( healthnum, textColor);
												//bullet disappear
												bullet.x = -1000;
												hit = true;
												testfire = false;



											}
						if( SDL_HasIntersection(&dam, &tknive) && enemyhit == false ){
							printf( "enemy hit\n" );
							tknive.x = -1000;
							//dam.y = -1000;
							turretHealth -= 1;
							playerfire = false;
							throwknive = false;

						throwknive = false;
							enemyhit = true;


						}
						if(turretHealth <= 0){
							//printf( "enemy destory\n" );
							dam.y = -1000;
							enemydead = true;
						}
						if( SDL_HasIntersection(&boss, &tknive) && enemyhit == false ){
													printf( "enemy hit\n" );
													tknive.x = -1000;
													//dam.y = -1000;
													bossHealth -= 1;
													playerfire = false;
													throwknive = false;

													enemyhit = true;


												}
												if(bossHealth <= 0){
													//printf( "enemy destory\n" );
													boss.y = -1000;
													bossdead = true;
													stop = true;
												}
												if( SDL_HasIntersection(&ehand, &tknive) && enemyhit == false ){
																									printf( "enemy hand hit\n" );
																									tknive.x = -1000;
																									//dam.y = -1000;
																									handHealth -= 1;
																									playerfire = false;
																									throwknive = false;

																									enemyhit = true;


																								}
																								if(handHealth <= 0){

																									ehand.y = -1000;


																								}



						if( SDL_HasIntersection(&playerPos, &primary) || SDL_HasIntersection(&playerPos, &door) ){
							dot.mPosX -= 10;
						}
						if( SDL_HasIntersection(&playerPos, &primary2) ){
													dot.mPosX += 10;
												}




						if( SDL_HasIntersection(&playerPos, &col) ){
							col.x = - 1000;
							// Mix_PlayChannel( -1, gBing, 0 );

							printf( "Player pickup ammo\n" );
										ammon= ammon + 10;
									ammonum = to_string(ammon);
									SDL_Color textColor = { 0, 0, 0 };
										aTextTexture.loadFromRenderedText( ammonum, textColor);

						}

						/*if( SDL_HasIntersection(&playerPos, &dam) ){

								printf( "Player has been damaged\n" );
								healthn= healthn - 1;
								healthnum = to_string(healthn);
								SDL_Color textColor = { 0, 0, 0 };
								gTextTexture.loadFromRenderedText( healthnum, textColor);

												}*/
						if( SDL_HasIntersection(&playerPos, &test) ){
							test.x = -1000;

														printf( "Player has been heal\n" );
														healthn= healthn + 30;
														healthnum = to_string(healthn);
														SDL_Color textColor = { 0, 0, 0 };
														gTextTexture.loadFromRenderedText( healthnum, textColor);

																		}
						if( SDL_HasIntersection(&playerPos, &hl) ){
													hl.x = -1000;

																				printf( "Player has been heal\n" );
																				healthn= healthn + 30;
																				healthnum = to_string(healthn);
																				SDL_Color textColor = { 0, 0, 0 };
																				gTextTexture.loadFromRenderedText( healthnum, textColor);

																								}
						//checking distance
						double distancex = ((dam.x + (dam.w / 2))
										- (playerPos.x + (playerPos.w / 2)))
										* ((dam.x + (dam.w / 2))
												- (playerPos.x + (playerPos.w / 2)));
								double distancey = (dam.y - playerPos.y)
										* (dam.y - playerPos.y);

								double calcdistance = sqrt(distancex + distancey);
								//cout << calcdistance << endl;
						if( /*SDL_HasIntersection(&playerPos, &Range)*/ calcdistance <= 300 && enemydead == false){
							testfire = true;

						}
						if( playerPos.x > dam.x){
							//printf( "Fire backward \n" );
							fireright = true;
						}
						if( playerPos.x < dam.x){
													//printf( "Fire backward \n" );
													fireright = false;
												}

						//Evil Hand
						double distancex1 = ((ehand.x + (ehand.w / 2))
																- (playerPos.x + (playerPos.w / 2)))
																* ((ehand.x + (ehand.w / 2))
																		- (playerPos.x + (playerPos.w / 2)));
														double distancey1 = (ehand.y - playerPos.y)
																* (ehand.y - playerPos.y);

														double calcdistance1 = sqrt(distancex1 + distancey1);


						if(SDL_HasIntersection(&playerPos, &rangehand)){
							//printf( "Test Evil hand  \n" );
							stophand = false;
							if(playerPos.x >= ehand.x && stophand == false){
								ehand.x += 1;
								rangehand.x += 1;
							}
							if(playerPos.x <= ehand.x && stophand == false){
								ehand.x -= 1;
								rangehand.x -= 1;
														}
							if(playerPos.y >= ehand.y ){
										ehand.y += 1;
										rangehand.y += 1;
													}
							if(playerPos.y <= ehand.y ){
															ehand.y -= 1;
															rangehand.y -= 1;
																					}

						}
						if(!SDL_HasIntersection(&playerPos, &rangehand)){
							stophand = true;
						}
						//enemy hand deal damage to player
						if(calcdistance1 < 30){
							printf( "Player has been damaged by hand\n" );


							healthn= healthn - 1;
							healthnum = to_string(healthn);
							SDL_Color textColor = { 0, 0, 0 };
							gTextTexture.loadFromRenderedText( healthnum, textColor);
												}



						//if Play is dead
						if(healthn <= 0){
							healthn= 0;
							healthnum = to_string(healthn);
							SDL_Color textColor = { 255, 0, 0 };
							gTextTexture.loadFromRenderedText( healthnum, textColor);

						}
						if(ammon <= 0){
							ammon= 0;
							ammonum = to_string(ammon);
							SDL_Color textColor = { 255, 0, 0 };
							aTextTexture.loadFromRenderedText( ammonum, textColor);

									}



						//Clear screen
						SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
						SDL_RenderClear( gRenderer );

						//Render background
						gBGTexture.render( 0, 0, &camera );

						//Render objects
						dot.render( camera.x, camera.y );
						//b.render( camera.x, camera.y);
						//enemy fire bullet test
						if(testfire == true){
							if(hit == true){
								hit = false;
								bullet.x = dam.x;
								bullet.y = startEnemyY;

							}
													//printf( "test enemy bullet\n" );
													b.render( camera.x, camera.y);
													if(fireright == false){
													bullet.x -= 15;
													}
													if(fireright == true){
																				bullet.x += 15;
																}
													if( bullet.x <= 20){
															bullet.y = -1000;
															hit = true;
															testfire = false;
																}
													if( bullet.x >= 3000){
																	bullet.y = -1000;
																	hit = true;
																			testfire = false;
																			}

												}

						//player throw knife
						if(throwknive == true){

							if(enemyhit == true){
								enemyhit = false;
								tknive.x = playerPos.x;
								tknive.y = playerPos.y;
							}






							knive.render(camera.x, camera.y);
							//tknive.x = playerPos.x;
							tknive.x += 50;
							if( tknive.x >= 3500){
							tknive.x = -1000;
							playerfire = false;
							throwknive = false;
							enemyhit = true;
							printf("bing\n");
								}
						}


						//Render objects
						bos.render( camera.x, camera.y);
						h.rendera( camera.x, camera.y);
						h.renderb( camera.x, camera.y);

						d.render( camera.x, camera.y);
						ca.render( camera.x, camera.y);

						eh.render( camera.x, camera.y);
						amo.arender(camera.x, camera.y);
						pri.render( camera.x, camera.y);
						pri.render2( camera.x, camera.y);
						sta.render(camera.x, camera.y);
						or1.render(camera.x, camera.y);
						//knive.render(camera.x, camera.y);
						//Render current frame
						health.render( camera.x, camera.y );
											key.keyrender( camera.x, camera.y );
											key.keyorbrender( camera.x, camera.y );
											ammo.arender( camera.x, camera.y );
					gTextTexture.render( 150, 50);
					aTextTexture.render( 150, 200);
					hTextTexture.render( 400, 10);
					barr.lrender();
					barr.wrender();


						//Update screen
						SDL_RenderPresent( gRenderer );
					}
				}
			}

			//Free resources and close SDL
			close();

			return 0;



};
