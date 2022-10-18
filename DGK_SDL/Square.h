#ifndef SQUARE_H
#define SQUARE_H

#include <SDL.h>
#include <string>
#include "Texture.h"

class Square
{
public:
	//The dimensions of the square
	static const int SQUARE_WIDTH = 60;
	static const int SQUARE_HEIGHT = 60;

	//Maximum axis velocity of the square
	float SQUARE_VEL = 10.0f;

	//Smoothing value
	float SQUARE_SMOOTHING = 0.5f;

	//Initializes the variables
	Square();

	//Takes key presses and adjusts the square's velocity
	void handleEvent(SDL_Event& e);

	//Moves the square
	void move(const int width, const int height);

	//Shows the square on the screen
	void render(SDL_Renderer* gRenderer, Texture* gSquareTexture);

private:
	//The X and Y offsets of the square
	float mPosX, mPosY;

	//The velocity of the square
	float mVelX, mVelY;
};
#endif SQUARE_H
