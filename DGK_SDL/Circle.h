#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL.h>
#include <string>
#include "Texture.h"

class Circle
{
public:
	//The dimensions of the circle
	static const int CIRCLE_WIDTH = 20;
	static const int CIRCLE_HEIGHT = 20;

	//Maximum axis velocity of the circle
	float CIRCLE_VEL = 5.0f;

	//Smoothing value
	float CIRCLE_SMOOTHING = 0.5f;

	//Initializes the variables
	Circle();

	//Takes key presses and adjusts the circle's velocity
	void handleEvent(SDL_Event& e);

	//Moves the dot
	void move(const int width, const int height);

	//Centers the camera over the circle
	void setCamera(SDL_Rect& camera, const int sWidth, const int sHeight, const int lWidth, const int lHeight, float alpha);

	//Shows the circle on the screen
	void render(SDL_Renderer* gRenderer, SDL_Rect& camera, Texture* gCircleTexture);

private:
	//The box for our circle
	SDL_Rect mBox;

	bool direction;

	//The velocity of the circle
	float mVelX, mVelY;
};
#endif CIRCLE_H
