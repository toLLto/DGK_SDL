#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <vector>

#include "Texture.h"
#include "Camera.h"
#include "Vector.h"

class Camera;

class Sprite
{
public:
	// Movement Types
	/*enum movement_scheme
	{
		none = 0,
		keyboard_arrows = 1,
		keyboard_wasd = 2,
		mouse = 3,
		gamepad = 4
	};*/
	unsigned int movement_type;

	// Collider Types
	/*enum collider_type
	{
		noCollision = 0,
		circle = 1,
		rectangle = 2
	};*/
	unsigned int collider_type;

	// Dimensions
	unsigned int sprite_width, sprite_height;
	
	//Maximum axis velocity
	float sprite_vel;

	// Smoothing
	float sprite_smooth;

	Sprite(unsigned int _id, unsigned int mt, unsigned int ct, unsigned int x, unsigned int y, unsigned int width, unsigned int height, float vel, float smooth);

	//Takes key presses and adjusts the sprite's velocity
	void handleEvent(SDL_Event& e);

	//Moves the sprite
	void move(const int width, const int height);

	//Shows the sprite on the screen
	void render(SDL_Renderer* gRenderer, Camera& cam, Texture* gSpriteTexture);

	int clamp(int x, int min, int max);

	//Checks if this circle collides with another
	void checkCollision(std::vector<Sprite*>& sprites, const int width, const int height);

	Vector getPosition();
	Vector getVelocity();
	bool getDirection();
	float getRadius();
	unsigned int getID();

	void setPosition(Vector v);
	void setVelocity(Vector v);

private:
	Vector position;
	Vector velocity;
	bool direction;
	float radius;
	unsigned int id;
};

#endif SPRITE_H