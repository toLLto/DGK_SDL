/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include "Circle.h"
#include <iostream>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

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

//Scene textures
Texture gCircleTexture;

//Circles
vector<Circle> circles;

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

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if (!gCircleTexture.loadFromFile("circle.png", gRenderer))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	gCircleTexture.free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
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
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Circle circle(Circle::CIRCLE_WIDTH / 2, Circle::CIRCLE_HEIGHT / 2, 0);
			for (int i = 1; i <= 2; i++)
			{
				float x, y;
				x = (float)(rand() % SCREEN_WIDTH);
				y = (float)(rand() % SCREEN_HEIGHT);

				if (x - Circle::CIRCLE_WIDTH < 0)
				{
					x += Circle::CIRCLE_WIDTH;
				}
				else if (x + Circle::CIRCLE_WIDTH > SCREEN_WIDTH)
				{
					x -= Circle::CIRCLE_WIDTH;
				}

				if (y - Circle::CIRCLE_HEIGHT < 0)
				{
					y += Circle::CIRCLE_HEIGHT;
				}
				else if (y + Circle::CIRCLE_HEIGHT > SCREEN_HEIGHT)
				{
					y -= Circle::CIRCLE_HEIGHT;
				}

				Circle tmp(x, y, i);
				circles.push_back(tmp);
			}

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
				}

				//Move the circles
				for (auto& c : circles)
				{
					c.move(SCREEN_WIDTH, SCREEN_HEIGHT);
				}

				//Check collisions
				for (auto& c : circles)
				{
					c.checkCollision(circles);
				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render circles
				for (auto& c : circles)
				{
					c.render(gRenderer, &gCircleTexture);
				}
				//circle.render(gRenderer, &gCircleTexture);

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}