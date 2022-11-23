#include "Circle.h"

Circle::Circle(float _x, float _y, unsigned int _id)
{
	//Initialize the circle box
	this->position = Vector(_x, _y);
	this->velocity = Vector(CIRCLE_VEL, CIRCLE_VEL);

	this->r = CIRCLE_WIDTH / 2;
	this->id = _id;
}

void Circle::move(double deltaTime)
{
	//Move the circle left or right
	position += velocity;

	
}

void Circle::render(SDL_Renderer* gRenderer, Texture* gCircleTexture)
{
	gCircleTexture->render(gRenderer, static_cast<int>(position.x), static_cast<int>(position.y));
}

void Circle::checkCollision(std::vector<Circle*>& circles, bool separationCheck, bool reflectionCheck, const int width, const int height)
{
	//If the circle went too far to the left or right
	if ((this->position.x - this->r < 0.0f) || (this->position.x + this->r >= width))
	{
		//Move back
		this->position.x -= this->velocity.x;
		this->velocity.x *= -1;
	}

	//If the circle went too far up or downs
	if ((this->position.y - this->r < 0.0f) || (this->position.y + this->r >= height))
	{
		//Move back
		this->position.y -= this->velocity.y;
		this->velocity.y *= -1;
	}

	for (auto& c : circles)
	{
		if (this->id == c->id)
		{
			continue;
		}

		Vector v = this->position - c->position;
		const float length = v.length();

		if (length < this->r + c->r)
		{
			v.normalize();

			if (separationCheck)
			{
				//Separation
				this->position += (v * (c->r - length * 0.5f));
				c->setPosition(c->position - v * (this->r - length * 0.5f));
			}

			if (reflectionCheck)
			{
				//Reflection
				velocity = velocity - v * velocity.dotProduct(v) * 2.0f;
				v *= -1.0f;
				c->setVelocity(c->velocity - v * c->velocity.dotProduct(v) * 2.0f);
			}
		}
	}
}

Vector Circle::getPosition()
{
	return this->position;
}

Vector Circle::getVelocity()
{
	return this->velocity;
}

float Circle::getR()
{
	return this->r;
}

unsigned int Circle::getID()
{
	return this->id;
}

void Circle::setPosition(Vector v)
{
	this->position = v;
}

void Circle::setVelocity(Vector v)
{
	this->velocity = v;
}
