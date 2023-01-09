#ifndef TILE_H
#define TILE_H

#include <SDL.h>
#include <string>
#include "Texture.h"
#include "Camera.h"

class Tile
{
public:
	//Tile constants
	const int TILE_WIDTH = 32;
	const int TILE_HEIGHT = 32;

	//Initializes position and type
	Tile(int x, int y, int tileType);

	//Shows the tile
	void render(SDL_Renderer* gRenderer, Camera& camera, Texture* gTileTexture, SDL_Rect gTileClips[7], float n);

	// Check collisions
	void checkCollision(std::vector<Sprite*>& sprites);

	//Get the tile type
	int getType();

	int getX();
	int getY();
	int getW();
	int getH();

	int clamp(int x, int min, int max);

private:
	//The attributes of the tile
	int x, y, w, h;

	//The tile type
	int mType;
};
#endif TILE_H
