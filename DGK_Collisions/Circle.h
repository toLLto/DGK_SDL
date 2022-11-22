#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL.h>
#include <string>
#include <vector>
#include "Texture.h"
#include "Vector.h"

class Circle
{
public:
	//The dimensions of the circle
	static const int CIRCLE_WIDTH = 60;
	static const int CIRCLE_HEIGHT = 60;

	//Maximum axis velocity of the circle
	float CIRCLE_VEL = 3.0f;

	//Initializes the variables
	Circle(float _x, float _y, unsigned int _id);

	//Moves the dot
	void move(/*CircleCollider& circle,*/ const int width, const int height);

	//Shows the circle on the screen
	void render(SDL_Renderer* gRenderer, Texture* gCircleTexture);

	//Checks if this circle collides with another
	bool checkCollision(std::vector<Circle>& circles);

	float distanceSquared(float x1, float y1, float x2, float y2);

	Vector getPosition();
	Vector getVelocity();
	float getR();
	unsigned int getID();

private:
	//The X and Y offsets of the circle
	Vector position;

	//The velocity of the circle
	Vector velocity;

	//Radius
	float r;

	//Circle ID
	unsigned int id;
};
#endif CIRCLE_H
