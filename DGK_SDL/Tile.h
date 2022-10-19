#ifndef TILE_H
#define TILE_H

#include <SDL.h>
#include <string>
#include "Texture.h"

class Tile
{
public:
	//Tile constants
	const int TILE_WIDTH = 40;
	const int TILE_HEIGHT = 40;

	//Initializes position and type
	Tile(int x, int y, int tileType);

	//Shows the tile
	void render(SDL_Renderer* gRenderer, Texture* gTileTexture, SDL_Rect gTileClips[3]);

	//Get the tile type
	int getType();

private:
	//The attributes of the tile
	SDL_Rect mBox;

	//The tile type
	int mType;
};
#endif TILE_H
