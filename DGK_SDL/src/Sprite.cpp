#include "Sprite.h"

Sprite::Sprite(unsigned int id, unsigned int mt, unsigned int ct, unsigned int x, unsigned int y, unsigned int width, unsigned int height, float vel, float h, float xh, float smooth)
{
	this->movement_type = mt;
	this->collider_type = ct;
	this->sprite_width = width;
	this->sprite_height = height;
	this->sprite_vel = vel;
	this->sprite_smooth = smooth;
	this->id = id;

	updateParameters(h, vel, xh);
	SDL_Log("Parameter update: current v0: %f and g: %f", v0, g);

	if (ct != 1)
		this->radius = 0;
	else
		this->radius = width / 2;

	this->position = Vector(x, y);
	this->velocity = Vector(0, 0);
	this->acceleration = Vector(0, this->g);

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
				if (multiJump < 2)
				{
					multiJump++;
					velocity.y = v0;
				}
				//SDL_Log("W was pressed");
				break;
			case SDLK_s:
				//velocity.y += sprite_vel;
				this->position = Vector(64, 832);
				//SDL_Log("S was pressed");
				break;
			case SDLK_a:
				velocity.x -= sprite_vel;
				//SDL_Log("A was pressed");
				direction = true;
				break;
			case SDLK_d:
				velocity.x += sprite_vel;
				//SDL_Log("D was pressed");
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
			//case SDLK_w:
			//	velocity.y = 0;
			//	//SDL_Log("W was released");
			//	break;
			//case SDLK_s:
			//	velocity.y = 0;
			//	//SDL_Log("S was released");
			//	break;
			case SDLK_a:
				velocity.x = 0;
				//SDL_Log("A was released");
				break;
			case SDLK_d:
				velocity.x = 0;
				//SDL_Log("D was released");
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
				//SDL_Log("Up was pressed");
				break;
			case SDLK_DOWN:
				velocity.y += sprite_vel;
				//SDL_Log("Down was pressed");
				break;
			case SDLK_LEFT:
				velocity.x -= sprite_vel;
				//SDL_Log("Left was pressed");
				direction = true;
				break;
			case SDLK_RIGHT:
				velocity.x += sprite_vel;
				//SDL_Log("Right was pressed");
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
				//SDL_Log("Up was released");
				break;
			case SDLK_DOWN:
				velocity.y = 0;
				//SDL_Log("Down was released");
				break;
			case SDLK_LEFT:
				velocity.x = 0;
				//SDL_Log("Left was released");
				break;
			case SDLK_RIGHT:
				velocity.x = 0;
				//SDL_Log("Right was released");
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

			//SDL_Log("Mouse is at [%d, %d]", x, y);
		}
	}
}

void Sprite::move(double deltaTime)
{
	position.x += velocity.x;

	if (this->onGround)
	{
		velocity.y = this->v0;
	}
	else if (!onGround)
	{
		velocity.y += acceleration.y * deltaTime;
	}

	if (!onGround)
	{
		position.y += velocity.y * deltaTime + acceleration.y * 0.5 * deltaTime * deltaTime;
	}

	acceleration.y = g;
	onGround = false;
	timeSinceLastJump += deltaTime;
}

void Sprite::jump(double deltaTime)
{
	this->position += this->velocity * deltaTime + this->acceleration * 0.5 * deltaTime * deltaTime;
	this->velocity += this->acceleration * deltaTime;
}

void Sprite::calculatePhysics(double deltaTime)
{
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

int Sprite::clamp(int x, int min, int max)
{
	if (x < min)
		return min;
	else if (x > max)
		return max;
	else if (x > min && x < max)
		return x;
}

bool Sprite::checkCollision(std::vector<Sprite*>& sprites, const int width, const int height)
{
	if (this->collider_type == 0)
	{
		int left = static_cast<int>(this->getPosition().x) + static_cast<int>(this->sprite_width) - static_cast<int>(sprites.at(0)->getPosition().x);
		int right = static_cast<int>(sprites.at(0)->getPosition().x) + static_cast<int>(sprites.at(0)->sprite_width) - static_cast<int>(this->getPosition().x);
		int top = static_cast<int>(this->getPosition().y) + static_cast<int>(this->sprite_height) - static_cast<int>(sprites.at(0)->getPosition().y);
		int bottom = static_cast<int>(sprites.at(0)->getPosition().y) + static_cast<int>(sprites.at(0)->sprite_height) - static_cast<int>(this->getPosition().y);

		if (left > 0 && right > 0 && top > 0 && bottom > 0)
		{
			SDL_Log("Star reached");

			return true;
		}

		left = static_cast<int>(this->getPosition().x) + static_cast<int>(this->sprite_width) - static_cast<int>(sprites.at(1)->getPosition().x);
		right = static_cast<int>(sprites.at(1)->getPosition().x) + static_cast<int>(sprites.at(1)->sprite_width) - static_cast<int>(this->getPosition().x);
		top = static_cast<int>(this->getPosition().y) + static_cast<int>(this->sprite_height) - static_cast<int>(sprites.at(1)->getPosition().y);
		bottom = static_cast<int>(sprites.at(1)->getPosition().y) + static_cast<int>(sprites.at(1)->sprite_height) - static_cast<int>(this->getPosition().y);
		if (left > 0 && right > 0 && top > 0 && bottom > 0)
		{
			SDL_Log("Star reached");

			return true;
		}
	}

	for (auto& s : sprites)
	{
		if (this->id == s->id)
			continue;

		Vector v;

		if (this->collider_type == 1 && s->collider_type == 1)
		{
			v = this->position - s->position;
			const float length = v.length();

			if (length < this->radius + s->radius)
			{
				SDL_Log("Circle collision detected");
				v.normalize();

				//Separation
				this->position += (v * (s->radius - length * 0.5f));
				s->setPosition(s->position - v * (this->radius - length * 0.5f));

				this->setVelocity(Vector(0, 0));
				//s->setVelocity(Vector(0, 0));

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

			if (left > 0 && right > 0 && top > 0 && bottom > 0)
			{
				SDL_Log("Square collision detected");

				//Separation
				left < right ? v.x = -left : v.x = right;
				top < bottom ? v.y = -top : v.y = bottom;
				v.normalize();

				this->position += v;
				//s->setPosition(s->position - v * (this->sprite_width / 2 - length * 0.5f));
			}
		}
		else if (this->collider_type == 1 && s->collider_type == 2)
		{
			Vector f = Vector(
				clamp(this->getPosition().x + this->radius, s->getPosition().x, s->getPosition().x + s->sprite_width),
				clamp(this->getPosition().y + this->radius, s->getPosition().y, s->getPosition().y + s->sprite_height)
			);
			Vector c = Vector(this->getPosition().x + this->radius, this->getPosition().y + this->radius);
			Vector tmp = c - f;
			//v = v - f;
			const float length = tmp.length();

			if (length < this->radius)
			{
				SDL_Log("Circle / square collision detected");

				if (this->getPosition().x + this->radius == f.x && this->getPosition().y + this->radius == f.y)
				{
					const int left = static_cast<int>(this->getPosition().x) + static_cast<int>(this->radius) - static_cast<int>(s->getPosition().x) + static_cast<int>(this->radius);
					const int right = static_cast<int>(s->getPosition().x) + static_cast<int>(s->sprite_width) - static_cast<int>(this->getPosition().x) + static_cast<int>(this->radius * 2);
					const int top = static_cast<int>(this->getPosition().y) + static_cast<int>(this->radius) - static_cast<int>(s->getPosition().y) + static_cast<int>(this->radius);
					const int bottom = static_cast<int>(s->getPosition().y) + static_cast<int>(s->sprite_height) - static_cast<int>(this->getPosition().y) + static_cast<int>(this->radius * 2);

					//Separation
					left < right ? v.x = -left : v.x = right;
					top < bottom ? v.y = -top : v.y = bottom;

					if (abs(v.x) > abs(v.y))
						v.x = 0;
					else
						v.y = 0;

					//v.normalize();

					this->position += v;
				}
				else
				{
					Vector res = c - f;
					float l = res.length();
					if (l == 0)
						res = Vector(0, 0);

					res /= l;
					//res = res * (this->radius - l);

					//v.normalize();

					//Separation
					this->position += (res * (s->sprite_width / 2 - length * 0.5f));
					s->setPosition(s->position - res * (this->radius - length * 0.5f));

					//this->setVelocity(Vector(0, 0));
					//this->position += res;
				}
			}
		}

		return false;
	}

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
}

void Sprite::updateParameters(float h, float vx, float xh)
{
	this->v0 = -2 * h * (vx / xh);
	this->g = 2 * h * ((vx * vx) / (xh * xh));
	this->acceleration.y = g;
	SDL_Log("Jump stats: [v0: %f] / [g: %f]", this->v0, this->g);
}

Vector Sprite::getPosition()
{
	return this->position;
}

Vector Sprite::getVelocity()
{
	return this->velocity;
}

Vector Sprite::getAcceleration()
{
	return this->acceleration;;
}

double Sprite::getTimeSinceLastJump()
{
	return this->timeSinceLastJump;
}

bool Sprite::isOnGround()
{
	return this->onGround;
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

void Sprite::setAcceleration(Vector v)
{
	this->acceleration = v;
}

void Sprite::setOnGround(bool b)
{
	this->onGround = b;
}

void Sprite::resetTimer()
{
	this->timeSinceLastJump = 0.0;
}

void Sprite::resetMultiJump()
{
	this->multiJump = 0;
}
