#include "Circle.h"

Circle::Circle()
{
	//Initialize the offsets
	mPosX = 600;
	mPosY = 200;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

void Circle::handleEvent(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: 
			mVelY -= CIRCLE_VEL; 
			SDL_Log("Up was pressed");
			break;
		case SDLK_DOWN: 
			mVelY += CIRCLE_VEL; 
			SDL_Log("Down was pressed");
			break;
		case SDLK_LEFT: 
			mVelX -= CIRCLE_VEL; 
			SDL_Log("Left was pressed");
			break;
		case SDLK_RIGHT: 
			mVelX += CIRCLE_VEL; 
			SDL_Log("Right was pressed");
			break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: 
			mVelY = 0; 
			SDL_Log("Up was released");
			break;
		case SDLK_DOWN: 
			mVelY = 0; 
			SDL_Log("Down was released");
			break;
		case SDLK_LEFT: 
			mVelX = 0; 
			SDL_Log("Left was released");
			break;
		case SDLK_RIGHT: 
			mVelX = 0; 
			SDL_Log("Right was released");
			break;
		}
	}
}

void Circle::move(const int width, const int height)
{
	//Move the dot left or right
	mPosX += mVelX;

	//If the dot went too far to the left or right
	if ((mPosX < 0) || (mPosX + CIRCLE_WIDTH > width))
	{
		//Move back
		mPosX -= mVelX;
	}

	//Move the dot up or down
	mPosY += mVelY;

	//If the dot went too far up or down
	if ((mPosY < 0) || (mPosY + CIRCLE_HEIGHT > height))
	{
		//Move back
		mPosY -= mVelY;
	}
}

void Circle::render(SDL_Renderer* gRenderer, Texture* gCircleTexture)
{
	gCircleTexture->setAlpha(127);

	//Show the dot
	gCircleTexture->render(gRenderer, mPosX, mPosY);
}
