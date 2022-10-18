#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL.h>
#include <string>
#include "Texture.h"

class Circle
{
public:
	//The dimensions of the dot
	static const int CIRCLE_WIDTH = 20;
	static const int CIRCLE_HEIGHT = 20;

	//Maximum axis velocity of the dot
	float CIRCLE_VEL = 10.0f;

	//Smoothing value
	float CIRCLE_SMOOTHING = 0.5f;

	//Initializes the variables
	Circle();

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the dot
	void move(const int width, const int height);

	//Shows the dot on the screen
	void render(SDL_Renderer* gRenderer, Texture* gCircleTexture);

private:
	//The X and Y offsets of the dot
	float mPosX, mPosY;

	//The velocity of the dot
	float mVelX, mVelY;
};
#endif CIRCLE_H
