#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL.h>
#include <string>
#include "Texture.h"

struct CircleCollider
{
	float x, y;
	float r;
};

class Circle
{
public:
	//The dimensions of the circle
	static const int CIRCLE_WIDTH = 60;
	static const int CIRCLE_HEIGHT = 60;

	//Maximum axis velocity of the circle
	float CIRCLE_VEL = 2.0f;

	//Initializes the variables
	Circle(int x, int y);

	//Moves the dot
	void move(CircleCollider& circle, const int width, const int height);

	//Shows the circle on the screen
	void render(SDL_Renderer* gRenderer, Texture* gCircleTexture);

	//Get collision circle
	CircleCollider& getCollider();

	//Checks if this circle collides with another
	bool checkCollision(CircleCollider& c);

	float vectorLength(float x1, float y1, float x2, float y2);

private:
	//The X and Y offsets of the circle
	float mPosX, mPosY;

	//The velocity of the circle
	float mVelX, mVelY;

	//Circle's collider
	CircleCollider mCollider;

	//Move the collider
	void shiftColliders();
};
#endif CIRCLE_H
