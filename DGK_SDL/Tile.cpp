#include "Tile.h"

Tile::Tile(int x, int y, int tileType)
{
	//Get the offsets
	mBox.x = x;
	mBox.y = y;

	//Set the collision box
	mBox.w = TILE_WIDTH;
	mBox.h = TILE_HEIGHT;

	//Get the tile type
	mType = tileType;
}

void Tile::render(SDL_Renderer* gRenderer, SDL_Rect& camera, Texture* gTileTexture, SDL_Rect* gTileClips)
{
	//Show the tile
	gTileTexture->render(gRenderer, mBox.x - camera.x, mBox.y - camera.y, &gTileClips[mType]);
}

int Tile::getType()
{
	return mType;
}
