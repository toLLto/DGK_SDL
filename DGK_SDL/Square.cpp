#include "Square.h"

Square::Square()
{
	//Initialize the offsets
	mPosX = 0;
	mPosY = 0;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

void Square::handleEvent(SDL_Event& e)
{
	//If mouse event happened
	if (e.type == SDL_MOUSEMOTION)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		mPosX = x;
		mPosY = y;

		SDL_Log("Mouse is at [%d, %d]", x, y);
	}
}

void Square::move(const int width, const int height)
{
	//Move the square left or right
	mPosX += mVelX;

	//If the dot went too far to the left or right
	if ((mPosX < 0) || (mPosX + SQUARE_WIDTH > width))
	{
		//Move back
		mPosX -= mVelX;
	}

	//Move the square up or down
	mPosY += mVelY;

	//If the dot went too far up or down
	if ((mPosY < 0) || (mPosY + SQUARE_HEIGHT > height))
	{
		//Move back
		mPosY -= mVelY;
	}
}

void Square::render(SDL_Renderer* gRenderer, Texture* gSquareTexture)
{
	//Show the dot
	gSquareTexture->render(gRenderer, mPosX, mPosY);
}
