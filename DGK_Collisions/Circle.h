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
	float CIRCLE_VEL = 0.5f;

	//Initializes the variables
	Circle(float _x, float _y, unsigned int _id);

	//Moves the dot
	void move(double deltaTime, const int width, const int height);

	//Shows the circle on the screen
	void render(SDL_Renderer* gRenderer, Texture* gCircleTexture);

	//Checks if this circle collides with another
	void checkCollision(std::vector<Circle*>& circles, bool separationCheck, bool reflectionCheck);

	Vector getPosition();
	Vector getVelocity();
	float getR();
	unsigned int getID();

	void setPosition(Vector v);
	void setVelocity(Vector v);

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
