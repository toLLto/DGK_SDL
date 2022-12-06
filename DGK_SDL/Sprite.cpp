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
		this->radius = 0;
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
		gSpriteTexture->render(gRenderer, static_cast<int>(position.x) - cam.camera.x, static_cast<int>(position.y) - cam.camera.y, cam.getScale());
	}
	else if (movement_type == 1)
	{
		gSpriteTexture->render(gRenderer, static_cast<int>(position.x) - cam.camera.x, static_cast<int>(position.y) - cam.camera.y, cam.getScale());
	}
	else if (movement_type == 2)
	{
		gSpriteTexture->render(gRenderer, static_cast<int>(position.x) - cam.camera.x, static_cast<int>(position.y) - cam.camera.y, cam.getScale());
	}
	else if (movement_type == 3)
	{
		gSpriteTexture->render(gRenderer, static_cast<int>(position.x), static_cast<int>(position.y), cam.getScale());
	}
}

void Sprite::checkCollision(std::vector<Sprite*>& sprites, const int width, const int height)
{
	if (this->collider_type == 1)
	{
		// Sprite went outside boundaries
		if ((this->position.x < 0.0f) || (static_cast<int>(this->position.x) + this->sprite_width > width))
		{
			//Move back
			SDL_Log("Circle: Out on X axis");
			this->position.x -= this->velocity.x;
			this->velocity.x = 0;
		}

		if ((this->position.y < 0.0f) || (static_cast<int>(this->position.y) + this->sprite_height > height))
		{
			//Move back
			SDL_Log("Circle: Out on Y axis");
			this->position.y -= this->velocity.y;
			this->velocity.y = 0;
		}
	}

	if (this->collider_type == 2)
	{
		// Sprite went outside boundaries
		if ((this->position.x < 0.0f) || (static_cast<int>(this->position.x) + this->sprite_width > width))
		{
			//Move back
			SDL_Log("Square: Out on X axis");
			this->position.x -= this->velocity.x;
			this->velocity.x = 0;
		}

		if ((this->position.y < 0.0f) || (static_cast<int>(this->position.y) + this->sprite_height > height))
		{
			//Move back
			SDL_Log("Square: Out on Y axis");
			this->position.y -= this->velocity.y;
			this->velocity.y = 0;
		}
	}

	for (auto& s : sprites)
	{
		if (this->id == s->id)
			continue;

		Vector v = this->position - s->position;
		const float length = v.length();

		if (this->collider_type == 1 && s->collider_type == 1)
		{
			if (length < this->radius + s->radius)
			{
				SDL_Log("Collision detected");
				v.normalize();

				//Separation
				this->position += (v * (s->radius - length * 0.5f));
				s->setPosition(s->position - v * (this->radius - length * 0.5f));

				this->setVelocity(Vector(0, 0));
				s->setVelocity(Vector(0, 0));

				////Reflection
				//velocity = velocity - v * velocity.dotProduct(v) * 2.0f;
				//v *= -1.0f;
				//s->setVelocity(s->velocity - v * s->velocity.dotProduct(v) * 2.0f);
			}
		}
		else if (this->collider_type == 2 && s->collider_type == 2)
		{
			const int left = static_cast<int>(this->getPosition().x) + static_cast<int>(this->sprite_width) - static_cast<int>(s->getPosition().x);
			const int right = static_cast<int>(s->getPosition().x) + static_cast<int>(s->sprite_width) - static_cast<int>(this->getPosition().x);
			const int top = static_cast<int>(this->getPosition().y) + static_cast<int>(this->sprite_height) - static_cast<int>(s->getPosition().y);
			const int bottom = static_cast<int>(s->getPosition().y) + static_cast<int>(s->sprite_height) - static_cast<int>(this->getPosition().y);

			if (left == 0 && right == 0 && top == 0 && bottom == 0)
			{
				SDL_Log("Collision detected");

				//Separation
				left < right ? v.x = static_cast<float>(-left) : v.x = static_cast<float>(right);
				top < bottom ? v.y = static_cast<float>(-top) : v.y = static_cast<float>(bottom);

				this->position += (v * (static_cast<float>(s->sprite_width / 2) - length * 0.5f));
				s->setPosition(s->position - v * (this->radius - length * 0.5f));
			}
		}
		else if (this->collider_type == 1 && s->collider_type == 2)
		{
			if (length < this->radius + s->sprite_width / 2)
			{
				SDL_Log("Collision detected");
				v.normalize();

				//Separation
				this->position += (v * (s->sprite_width / 2 - length * 0.5f));
				s->setPosition(s->position - v * (this->radius - length * 0.5f));

				////Reflection
				//velocity = velocity - v * velocity.dotProduct(v) * 2.0f;
				//v *= -1.0f;
				//s->setVelocity(s->velocity - v * s->velocity.dotProduct(v) * 2.0f);
			}
		}
		
	}
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
