/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
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
bool loadMedia(Tile* level[], Tile* fore[], Tile* back[]);

//Sets tiles from tile map
bool setTiles(Tile* tiles[], std::string fileName);

//Frees media and shuts down SDL
void close(Tile* level[], Tile* fore[], Tile* back[]);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
Texture gCharacterTexture;
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

bool loadMedia(Tile* level[], Tile* fore[], Tile* back[])
{
	//Loading success flag
	bool success = true;

	//Load sprite texture
	if (!gCharacterTexture.loadFromFile("Character.png", gRenderer))
	{
		printf("Failed to load character texture!\n");
		success = false;
	}

	//Load tile texture
	if (!gTileTexture.loadFromFile("DGK_sprite_sheet.png", gRenderer))
	{
		printf("Failed to load sprite sheet!\n");
		success = false;
	}

	//Load tile maps
	if (!setTiles(level, "level.map") || !setTiles(fore, "foreground.map") || !setTiles(back, "background.map"))
	{
		printf("Failed to load tile sets!\n");
		success = false;
	}

	return success;
}

void close(Tile* level[], Tile* fore[], Tile* back[])
{
	//Deallocate tiles
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		if (level[i] != NULL)
		{
			delete level[i];
			level[i] = NULL;
		}

		if (fore[i] != NULL)
		{
			delete fore[i];
			fore[i] = NULL;
		}

		if (back[i] != NULL)
		{
			delete back[i];
			back[i] = NULL;
		}
	}

	//Free loaded images
	gCharacterTexture.free();
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

bool setTiles(Tile* tiles[], std::string fileName)
{
	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	int x = 0, y = 0;

	//Open the map
	std::ifstream map(fileName);

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
			gTileClips[TILE_BLANK].x = 0;
			gTileClips[TILE_BLANK].y = 32;
			gTileClips[TILE_BLANK].w = TILE_WIDTH;
			gTileClips[TILE_BLANK].h = TILE_HEIGHT;

			gTileClips[TILE_1].x = 32;
			gTileClips[TILE_1].y = 32;
			gTileClips[TILE_1].w = TILE_WIDTH;
			gTileClips[TILE_1].h = TILE_HEIGHT;

			gTileClips[TILE_2].x = 64;
			gTileClips[TILE_2].y = 32;
			gTileClips[TILE_2].w = TILE_WIDTH;
			gTileClips[TILE_2].h = TILE_HEIGHT;

			gTileClips[TILE_3].x = 96;
			gTileClips[TILE_3].y = 32;
			gTileClips[TILE_3].w = TILE_WIDTH;
			gTileClips[TILE_3].h = TILE_HEIGHT;

			gTileClips[TILE_4].x = 0;
			gTileClips[TILE_4].y = 64;
			gTileClips[TILE_4].w = TILE_WIDTH;
			gTileClips[TILE_4].h = TILE_HEIGHT;

			gTileClips[TILE_5].x = 32;
			gTileClips[TILE_5].y = 64;
			gTileClips[TILE_5].w = TILE_WIDTH;
			gTileClips[TILE_5].h = TILE_HEIGHT;

			gTileClips[TILE_6].x = 64;
			gTileClips[TILE_6].y = 64;
			gTileClips[TILE_6].w = TILE_WIDTH;
			gTileClips[TILE_6].h = TILE_HEIGHT;
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
		Tile* levelTileSet[TOTAL_TILES];
		Tile* foregroundTileSet[TOTAL_TILES];
		Tile* backgroundTileSet[TOTAL_TILES];

		//Load media
		if (!loadMedia(levelTileSet, foregroundTileSet, backgroundTileSet))
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

			// Sprites
			Sprite character(0, 1, 2, 64, 64, gCharacterTexture.getWidth(), gCharacterTexture.getHeight(), 5.0f, 0.5f);

			
			sprites.push_back(&character);

			//Create level camera
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
				}

				//Move the dot
				sprites.at(0)->move(LEVEL_WIDTH, LEVEL_HEIGHT);
				cam.move(character, SCREEN_WIDTH, SCREEN_HEIGHT, LEVEL_WIDTH, LEVEL_HEIGHT, 0.2f);

				//Check collisions
				for (int i = 0; i < TOTAL_TILES; ++i)
				{
					if (levelTileSet[i]->getType() != 0)
					{
						levelTileSet[i]->checkCollision(sprites);
					}
				}

				sprites.at(0)->checkCollision(sprites, LEVEL_WIDTH, LEVEL_HEIGHT);

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render background
				for (int i = 0; i < TOTAL_TILES; ++i)
				{
					backgroundTileSet[i]->render(gRenderer, cam, &gTileTexture, gTileClips);
				}

				//Render foreground
				for (int i = 0; i < TOTAL_TILES; ++i)
				{
					foregroundTileSet[i]->render(gRenderer, cam, &gTileTexture, gTileClips);
				}

				//Render level
				for (int i = 0; i < TOTAL_TILES; ++i)
				{
					levelTileSet[i]->render(gRenderer, cam, &gTileTexture, gTileClips);
				}

				//Render objects
				sprites.at(0)->render(gRenderer, cam, &gCharacterTexture);

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
		
		//Free resources and close SDL
		close(levelTileSet, foregroundTileSet, backgroundTileSet);
	}

	return 0;
}