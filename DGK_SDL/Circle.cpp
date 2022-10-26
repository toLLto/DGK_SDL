#include "Circle.h"

Circle::Circle()
{
	//Initialize the circle box
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = CIRCLE_WIDTH;
	mBox.h = CIRCLE_HEIGHT;

	direction = false;

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
			direction = true;
			break;
		case SDLK_RIGHT: 
			mVelX += CIRCLE_VEL; 
			SDL_Log("Right was pressed");
			direction = false;
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
	//Move the circle left or right
	mBox.x += mVelX;

	//If the circle went too far to the left or right
	if ((mBox.x < 0) || (mBox.x + CIRCLE_WIDTH > width))
	{
		//Move back
		mBox.x -= mVelX;
	}

	//Move the circle up or down
	mBox.y += mVelY;

	//If the circle went too far up or down
	if ((mBox.y < 0) || (mBox.y + CIRCLE_HEIGHT > height))
	{
		//Move back
		mBox.y -= mVelY;
	}
}

void Circle::setCamera(SDL_Rect& camera, const int sWidth, const int sHeight, const int lWidth, const int lHeight, float alpha)
{
	//Center the camera over the circle
	//camera.x = (mBox.x + CIRCLE_WIDTH / 2) - sWidth / 2;
	camera.y = (mBox.y + CIRCLE_HEIGHT / 2) - sHeight / 2;

	//Lerp
	if (direction)
	{

		camera.x = camera.x + (alpha * (mBox.x - (sWidth * 0.2) - camera.x));
	}
	else
	{
		camera.x = camera.x + (alpha * (mBox.x - (sWidth * 0.8) - camera.x));
	}
	

	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > lWidth - camera.w)
	{
		camera.x = lWidth - camera.w;
	}
	if (camera.y > lHeight - camera.h)
	{
		camera.y = lHeight - camera.h;
	}
}

void Circle::render(SDL_Renderer* gRenderer, SDL_Rect& camera, Texture* gCircleTexture)
{
	gCircleTexture->render(gRenderer, mBox.x - camera.x, mBox.y - camera.y);
}
