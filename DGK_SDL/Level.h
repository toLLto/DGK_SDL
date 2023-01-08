#ifndef LEVEL_H
#define LEVEL_H

#include <SDL.h>
#include <vector>

#include "Texture.h"
#include "Camera.h"
#include "Vector.h"
#include "Tile.h"

//The dimensions of the level
const int LEVEL_WIDTH = 1600;
const int LEVEL_HEIGHT = 1600;

//Tile constants
const int TILE_WIDTH = 100;
const int TILE_HEIGHT = 100;
const int TOTAL_TILES = 256;
const int TOTAL_TILE_SPRITES = 3;

//The different tile sprites
const int TILE_RED = 0;
const int TILE_BLACK = 1;
const int TILE_BROWN = 2;

class Camera;

class Level
{
public:
	int whatever;

private:
	Tile* tileSet[TOTAL_TILES];
};
#endif
