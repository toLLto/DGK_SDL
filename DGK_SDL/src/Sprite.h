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
	float sprite_vel = 1;

	// Smoothing
	float sprite_smooth;

	Sprite(unsigned int _id, unsigned int mt, unsigned int ct, unsigned int x, unsigned int y, unsigned int width, unsigned int height, float vel, float h, float xh, float smooth);

	//Takes key presses and adjusts the sprite's velocity
	void handleEvent(SDL_Event& e);

	//Moves the sprite
	void move(double deltaTime);

	void jump(double deltaTime);

	void calculatePhysics(double deltaTime);

	//Shows the sprite on the screen
	void render(SDL_Renderer* gRenderer, Camera& cam, Texture* gSpriteTexture);

	int clamp(int x, int min, int max);

	//Checks if this circle collides with another
	bool checkCollision(std::vector<Sprite*>& sprites, const int width, const int height);

	// Update jump parameters
	void updateParameters(float h, float vx, float xh);

	Vector getPosition();
	Vector getVelocity();
	Vector getAcceleration();
	float getRadius();
	double getTimeSinceLastJump();
	bool isOnGround();
	bool getDirection();
	unsigned int getID();

	void setPosition(Vector v);
	void setVelocity(Vector v);
	void setAcceleration(Vector v);
	void setOnGround(bool b);
	void resetTimer();
	void resetMultiJump();

private:
	Vector position;
	Vector velocity;
	Vector acceleration;

	float v0, g;

	double timeSinceLastJump = 0.0;

	bool onGround = false;

	bool direction;
	float radius;
	unsigned int id;
	int multiJump = 0;
};

#endif SPRITE_H