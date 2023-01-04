/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include "Texture.h"
#include "Tile.h"
#include "Sprite.h"
#include "Camera.h"
#include "Level.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia(Tile* tiles[]);

//Sets tiles from tile map
bool setTiles(Tile* tiles[]);

//Frees media and shuts down SDL
void close(Tile* tiles[]);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
Texture gCircleTexture;
Texture gSquareTexture;
Texture gStarTexture;
Texture gTileTexture;
SDL_Rect gTileClips[TOTAL_TILE_SPRITES];

//Sprites
std::vector<Sprite*> sprites;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia(Tile* tiles[])
{
	//Loading success flag
	bool success = true;

	//Load first sprite texture
	if (!gSquareTexture.loadFromFile("square.png", gRenderer))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}

	//Load second sprite texture
	if (!gCircleTexture.loadFromFile("circle.png", gRenderer))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}

	//Load third sprite texture
	if (!gStarTexture.loadFromFile("star.png", gRenderer))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}

	//Load tile texture
	if (!gTileTexture.loadFromFile("tiles.png", gRenderer))
	{
		printf("Failed to load square texture!\n");
		success = false;
	}

	//Load tile map
	if (!setTiles(tiles))
	{
		printf("Failed to load tile set!\n");
		success = false;
	}

	return success;
}

void close(Tile* tiles[])
{
	//Deallocate tiles
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		if (tiles[i] != NULL)
		{
			delete tiles[i];
			tiles[i] = NULL;
		}
	}

	//Free loaded images
	gCircleTexture.free();
	gSquareTexture.free();
	gStarTexture.free();
	gTileTexture.free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool setTiles(Tile* tiles[])
{
	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	int x = 0, y = 0;

	//Open the map
	std::ifstream map("map.map");

	//If the map couldn't be loaded
	if (map.fail())
	{
		printf("Unable to load map file!\n");
		tilesLoaded = false;
	}
	else
	{
		//Initialize the tiles
		for (int i = 0; i < TOTAL_TILES; ++i)
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If there was a problem in reading the map
			if (map.fail())
			{
				//Stop loading map
				printf("Error loading map: Unexpected end of file!\n");
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES))
			{
				tiles[i] = new Tile(x, y, tileType);
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", i);
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += TILE_WIDTH;

			//If we've gone too far
			if (x >= LEVEL_WIDTH)
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
		}

		//Clip the sprite sheet
		if (tilesLoaded)
		{
			gTileClips[TILE_RED].x = 0;
			gTileClips[TILE_RED].y = 0;
			gTileClips[TILE_RED].w = TILE_WIDTH;
			gTileClips[TILE_RED].h = TILE_HEIGHT;

			gTileClips[TILE_BLACK].x = 0;
			gTileClips[TILE_BLACK].y = 100;
			gTileClips[TILE_BLACK].w = TILE_WIDTH;
			gTileClips[TILE_BLACK].h = TILE_HEIGHT;

			gTileClips[TILE_BROWN].x = 0;
			gTileClips[TILE_BROWN].y = 200;
			gTileClips[TILE_BROWN].w = TILE_WIDTH;
			gTileClips[TILE_BROWN].h = TILE_HEIGHT;
		}
	}

	//Close the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//The level tiles
		Tile* tileSet[TOTAL_TILES];

		//Load media
		if (!loadMedia(tileSet))
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			srand(time(nullptr));

			//The dot that will be moving around on the screen
			//Circle circle;
			Sprite circle(0, 1, 1, rand() % 1500 + 30, rand() % 1500 + 30, gCircleTexture.getWidth(), gCircleTexture.getHeight(), 5.0f, 0.5f);
			Sprite square(1, 2, 2, rand() % 1500 + 30, rand() % 1500 + 30, gSquareTexture.getWidth(), gSquareTexture.getHeight(), 5.0f, 0.5f);

			int starX = rand() % 1500 + 20;
			int starY = rand() % 1500 + 20;
			for (int i = 0; i < TOTAL_TILES; ++i)
			{
				if (starX > tileSet[i]->getX() && starX < tileSet[i]->getX() + tileSet[i]->getW() && starY > tileSet[i]->getY() && starY < tileSet[i]->getY() + tileSet[i]->getH())
				{
					if (tileSet[i]->getType() != 2)
					{
						starX = rand() % 1500 + 20;
						starY = rand() % 1500 + 20;
						continue;
					}
					
					starX = tileSet[i]->getX() + 20;
					starY = tileSet[i]->getY() + 20;
				}
			}

			Sprite star(2, 0, 0, starX, starY, gStarTexture.getWidth(), gStarTexture.getHeight(), 5.0f, 0.5f);
			sprites.push_back(&circle);
			sprites.push_back(&square);
			sprites.push_back(&star);

			//Create level camera
			//SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
			Camera cam(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

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
					//Handle input for the dot
					sprites.at(0)->handleEvent(e);
					sprites.at(1)->handleEvent(e);
				}

				//Move the dot
				sprites.at(0)->move(LEVEL_WIDTH, LEVEL_HEIGHT);
				sprites.at(1)->move(LEVEL_WIDTH, LEVEL_HEIGHT);
				//sprite1.setCamera(camera, SCREEN_WIDTH, SCREEN_HEIGHT, LEVEL_WIDTH, LEVEL_HEIGHT, 0.2f);
				cam.move(circle, square, SCREEN_WIDTH, SCREEN_HEIGHT, LEVEL_WIDTH, LEVEL_HEIGHT, 0.2f);

				//Check collisions
				bool levelComplete;

				for (int i = 0; i < TOTAL_TILES; ++i)
				{
					if (tileSet[i]->getType() == 1)
					{
						tileSet[i]->checkCollision(sprites);
					}
				}

				for (auto& s : sprites)
				{
					 levelComplete = s->checkCollision(sprites, LEVEL_WIDTH, LEVEL_HEIGHT);

					 if (levelComplete)
					 {
						 int starX = rand() % 1500 + 20;
						 int starY = rand() % 1500 + 20;

						 for (int i = 0; i < TOTAL_TILES; ++i)
						 {
							 if (starX > tileSet[i]->getX() && starX < tileSet[i]->getX() + tileSet[i]->getW() && starY > tileSet[i]->getY() && starY < tileSet[i]->getY() + tileSet[i]->getH())
							 {
								 if (tileSet[i]->getType() != 2)
								 {
									 starX = rand() % 1500 + 20;
									 starY = rand() % 1500 + 20;
									 continue;
								 }

								 starX = tileSet[i]->getX() + 20;
								 starY = tileSet[i]->getY() + 20;
							 }
						 }

						 sprites.at(0)->setPosition(Vector(rand() % 1500 + 30, rand() % 1500 + 30));
						 sprites.at(1)->setPosition(Vector(rand() % 1500 + 30, rand() % 1500 + 30));
						 sprites.at(2)->setPosition(Vector(starX, starY));
					 }
				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render level
				for (int i = 0; i < TOTAL_TILES; ++i)
				{
					tileSet[i]->render(gRenderer, cam, &gTileTexture, gTileClips);
				}

				//Render objects
				sprites.at(2)->render(gRenderer, cam, &gStarTexture);
				sprites.at(1)->render(gRenderer, cam, &gSquareTexture);
				sprites.at(0)->render(gRenderer, cam, &gCircleTexture);

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
		
		//Free resources and close SDL
		close(tileSet);
	}

	return 0;
}