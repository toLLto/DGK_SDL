#include "Circle.h"

Circle::Circle(float _x, float _y, unsigned int _id)
{
	//Initialize the circle box
	this->position = Vector(_x, _y);
	this->velocity = Vector(CIRCLE_VEL, CIRCLE_VEL);

	this->r = CIRCLE_WIDTH / 2;
	this->id = _id;
}

void Circle::move(double deltaTime, const int width, const int height)
{
	//Move the circle left or right
	position += velocity * (float)deltaTime;

	//If the circle went too far to the left or right
	if ((position.x - r < 0) || (position.x + r > width))
	{
		//Move back
		//position.x -= velocity.x;
		velocity.x *= -1;
	}

	//If the circle went too far up or down
	if ((position.y - r < 0) || (position.y + r > height))
	{
		//Move back
		//position.y -= velocity.y;
		velocity.y *= -1;
	}
}

void Circle::render(SDL_Renderer* gRenderer, Texture* gCircleTexture)
{
	gCircleTexture->render(gRenderer, position.x - r, position.y - r);
}

bool Circle::checkCollision(std::vector<Circle*>& circles, bool separationCheck, bool reflectionCheck)
{
	for (auto& c : circles)
	{
		if (this->id == c->getID())
		{
			continue;
		}

		Vector v = this->position - c->getPosition();
		float length = v.length();

		if (length < this->r + c->getR())
		{
			v.normalize();

			if (separationCheck)
			{
				//Separation
				this->position += v * (c->getR() - length / 2.0f);
				c->setPosition(c->getPosition() - v * (this->r - length / 2.0f));
			}

			if (reflectionCheck)
			{
				//Reflection
				float dot = this->velocity.dotProduct(v);
				float dotC = c->velocity.dotProduct(v);

				this->velocity -= v * dot;
				v *= -1.f;
				c->setVelocity(c->velocity - v * dotC);
			}
		}
	}

	return false;
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
