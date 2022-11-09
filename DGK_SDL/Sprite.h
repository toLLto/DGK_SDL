#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include "Texture.h"
#include "Camera.h"

class Camera;

class Sprite
{
public:
	// Movement Types
	enum movement_scheme
	{
		keyboard_arrows = 0,
		keyboard_wasd = 1,
		mouse = 2,
		gamepad = 3
	};
	unsigned int movement_type;

	// Dimensions
	unsigned int sprite_width, sprite_height;
	
	//Maximum axis velocity
	float sprite_vel;

	// Smoothing
	float sprite_smooth;

	Sprite(unsigned int mt, unsigned int width, unsigned int height, float vel, float smooth);

	//Takes key presses and adjusts the sprite's velocity
	void handleEvent(SDL_Event& e);

	//Moves the sprite
	void move(const int width, const int height);

	//Centers the camera over the sprite
	void setCamera(SDL_Rect& camera, const int sWidth, const int sHeight, const int lWidth, const int lHeight, float alpha);

	//Shows the sprite on the screen
	void render(SDL_Renderer* gRenderer, Camera& cam, Texture* gSpriteTexture);

	int getBoxX();
	int getBoxY();
	bool getDirection();

private:
	//The box for our sprite
	SDL_Rect mBox;

	bool direction;

	//The velocity of the sprite
	float mVelX, mVelY;
};

#endif SPRITE_H