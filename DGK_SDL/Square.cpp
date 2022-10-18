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

//void Square::handleEvent(SDL_Event& e)
//{
//	//If a key was pressed
//	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
//	{
//		//Adjust the velocity
//		switch (e.key.keysym.sym)
//		{
//		case SDLK_UP: mVelY -= SQUARE_VEL; break;
//		case SDLK_DOWN: mVelY += SQUARE_VEL; break;
//		case SDLK_LEFT: mVelX -= SQUARE_VEL; break;
//		case SDLK_RIGHT: mVelX += SQUARE_VEL; break;
//		}
//	}
//	//If a key was released
//	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
//	{
//		//Adjust the velocity
//		switch (e.key.keysym.sym)
//		{
//		case SDLK_UP: mVelY = 0; break;
//		case SDLK_DOWN: mVelY = 0; break;
//		case SDLK_LEFT: mVelX = 0; break;
//		case SDLK_RIGHT: mVelX = 0; break;
//		}
//	}
//}

//void Square::move(const int width, const int height)
//{
//	//Move the square left or right
//	mPosX += mVelX;
//
//	//If the dot went too far to the left or right
//	if ((mPosX < 0) || (mPosX + SQUARE_WIDTH > width))
//	{
//		//Move back
//		mPosX -= mVelX;
//	}
//
//	//Move the square up or down
//	mPosY += mVelY;
//
//	//If the dot went too far up or down
//	if ((mPosY < 0) || (mPosY + SQUARE_HEIGHT > height))
//	{
//		//Move back
//		mPosY -= mVelY;
//	}
//}

void Square::render(SDL_Renderer* gRenderer, Texture* gSquareTexture)
{
	//Show the dot
	gSquareTexture->render(gRenderer, mPosX, mPosY);
}
