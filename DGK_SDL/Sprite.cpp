#include "Sprite.h"

Sprite::Sprite(unsigned int mt, unsigned int width, unsigned int height, float vel, float smooth)
{
	movement_type = mt;
	sprite_width = width;
	sprite_height = height;
	sprite_vel = vel;
	sprite_smooth = smooth;

	// Initialize sprite box
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = sprite_width;
	mBox.h = sprite_height;

	direction = false;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

void Sprite::handleEvent(SDL_Event& e)
{
	if (movement_type == 1)
	{
		//If a key was pressed
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				mVelY -= sprite_vel;
				SDL_Log("Up was pressed");
				break;
			case SDLK_DOWN:
				mVelY += sprite_vel;
				SDL_Log("Down was pressed");
				break;
			case SDLK_LEFT:
				mVelX -= sprite_vel;
				SDL_Log("Left was pressed");
				direction = true;
				break;
			case SDLK_RIGHT:
				mVelX += sprite_vel;
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
	else if (movement_type == 3)
	{
		//If mouse event happened
		if (e.type == SDL_MOUSEMOTION)
		{
			//Get mouse position
			int x, y;
			SDL_GetMouseState(&x, &y);

			mBox.x = x;
			mBox.y = y;

			SDL_Log("Mouse is at [%d, %d]", x, y);
		}
	}
}

void Sprite::move(const int width, const int height)
{
	if (movement_type == 1)
	{
		//Move the circle left or right
		mBox.x += mVelX;

		//If the circle went too far to the left or right
		if ((mBox.x < 0) || (mBox.x + sprite_width > width))
		{
			//Move back
			mBox.x -= mVelX;
		}

		//Move the circle up or down
		mBox.y += mVelY;

		//If the circle went too far up or down
		if ((mBox.y < 0) || (mBox.y + sprite_height > height))
		{
			//Move back
			mBox.y -= mVelY;
		}
	}
}

void Sprite::setCamera(SDL_Rect& camera, const int sWidth, const int sHeight, const int lWidth, const int lHeight, float alpha)
{
	//Center the camera over the circle
	//camera.x = (mBox.x + CIRCLE_WIDTH / 2) - sWidth / 2;
	camera.y = (mBox.y + sprite_height / 2) - sHeight / 2;

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

void Sprite::render(SDL_Renderer* gRenderer, Camera& cam, Texture* gSpriteTexture)
{
	if (movement_type == 1)
	{
		gSpriteTexture->render(gRenderer, mBox.x - cam.camera.x, mBox.y - cam.camera.y, cam.getScale());
	}
	else if (movement_type == 3)
	{
		gSpriteTexture->render(gRenderer, mBox.x, mBox.y, cam.getScale());
	}
}

int Sprite::getBoxX()
{
	return mBox.x;
}

int Sprite::getBoxY()
{
	return mBox.y;
}

bool Sprite::getDirection()
{
	return direction;
}
