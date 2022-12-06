#include "Sprite.h"

Sprite::Sprite(unsigned int _mt, unsigned int _ct, unsigned int _x, unsigned int _y, unsigned int _width, unsigned int _height, float _vel, float _smooth)
{
	movement_type = _mt;
	collider_type = _ct;
	sprite_width = _width;
	sprite_height = _height;
	sprite_vel = _vel;
	sprite_smooth = _smooth;

	if (_ct != 1)
		this->radius = 0.f;
	else
		this->radius = _width / 2;

	this->position = Vector(_x, _y);
	this->velocity = Vector(0, 0);

	direction = false;
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
			case SDLK_w:
				velocity.y -= sprite_vel;
				SDL_Log("W was pressed");
				break;
			case SDLK_s:
				velocity.y += sprite_vel;
				SDL_Log("S was pressed");
				break;
			case SDLK_a:
				velocity.x -= sprite_vel;
				SDL_Log("A was pressed");
				direction = true;
				break;
			case SDLK_d:
				velocity.x += sprite_vel;
				SDL_Log("D was pressed");
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
			case SDLK_w:
				velocity.y = 0;
				SDL_Log("W was released");
				break;
			case SDLK_s:
				velocity.y = 0;
				SDL_Log("S was released");
				break;
			case SDLK_a:
				velocity.x = 0;
				SDL_Log("A was released");
				break;
			case SDLK_d:
				velocity.x = 0;
				SDL_Log("D was released");
				break;
			}
		}
	}
	else if (movement_type == 2)
	{
		//If a key was pressed
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				velocity.y -= sprite_vel;
				SDL_Log("Up was pressed");
				break;
			case SDLK_DOWN:
				velocity.y += sprite_vel;
				SDL_Log("Down was pressed");
				break;
			case SDLK_LEFT:
				velocity.x -= sprite_vel;
				SDL_Log("Left was pressed");
				direction = true;
				break;
			case SDLK_RIGHT:
				velocity.x += sprite_vel;
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
				velocity.y = 0;
				SDL_Log("Up was released");
				break;
			case SDLK_DOWN:
				velocity.y = 0;
				SDL_Log("Down was released");
				break;
			case SDLK_LEFT:
				velocity.x = 0;
				SDL_Log("Left was released");
				break;
			case SDLK_RIGHT:
				velocity.x = 0;
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

			position.x = x;
			position.y = y;

			SDL_Log("Mouse is at [%d, %d]", x, y);
		}
	}
}

void Sprite::move(const int width, const int height)
{
	if (movement_type == 1)
	{
		////Move the circle left or right
		//position.x += velocity.x;

		////If the circle went too far to the left or right
		//if ((position.x < 0) || (position.x + sprite_width > width))
		//{
		//	//Move back
		//	position.x -= velocity.x;
		//}

		////Move the circle up or down
		//position.y += velocity.y;

		////If the circle went too far up or down
		//if ((position.y < 0) || (position.y + sprite_height > height))
		//{
		//	//Move back
		//	position.y -= velocity.y;
		//}
		position += velocity;
	}

	if (movement_type == 2)
	{
		////Move the circle left or right
		//position.x += velocity.x;

		////If the circle went too far to the left or right
		//if ((position.x < 0) || (position.x + sprite_width > width))
		//{
		//	//Move back
		//	position.x -= velocity.x;
		//}

		////Move the circle up or down
		//position.y += velocity.y;

		////If the circle went too far up or down
		//if ((position.y < 0) || (position.y + sprite_height > height))
		//{
		//	//Move back
		//	position.y -= velocity.y;
		//}
		position += velocity;
	}
}

void Sprite::render(SDL_Renderer* gRenderer, Camera& cam, Texture* gSpriteTexture)
{
	if (movement_type == 0)
	{
		gSpriteTexture->render(gRenderer, position.x - cam.camera.x, position.y - cam.camera.y, cam.getScale());
	}
	else if (movement_type == 1)
	{
		gSpriteTexture->render(gRenderer, position.x - cam.camera.x, position.y - cam.camera.y, cam.getScale());
	}
	else if (movement_type == 2)
	{
		gSpriteTexture->render(gRenderer, position.x - cam.camera.x, position.y - cam.camera.y, cam.getScale());
	}
	else if (movement_type == 3)
	{
		gSpriteTexture->render(gRenderer, position.x, position.y, cam.getScale());
	}
}

void Sprite::checkCollision(std::vector<Sprite*>& sprites, const int width, const int height)
{

}

Vector Sprite::getPosition()
{
	return this->position;
}

Vector Sprite::getVelocity()
{
	return this->velocity;
}

bool Sprite::getDirection()
{
	return direction;
}

float Sprite::getRadius()
{
	return this->radius;
}

unsigned int Sprite::getID()
{
	return this->id;
}

void Sprite::setPosition(Vector v)
{
	this->position = v;
}

void Sprite::setVelocity(Vector v)
{
	this->velocity = v;
}
