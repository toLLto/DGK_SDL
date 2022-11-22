#include "Circle.h"

Circle::Circle(float _x, float _y, unsigned int _id)
{
	//Initialize the circle box
	this->position = Vector(_x, _y);
	this->velocity = Vector(CIRCLE_VEL, CIRCLE_VEL);

	this->r = CIRCLE_WIDTH / 2;
	this->id = _id;
}

void Circle::move(const int width, const int height)
{
	//Move the circle left or right
	position.x += velocity.x;

	//If the circle went too far to the left or right
	if ((position.x - r < 0) || (position.x + r > width))
	{
		//Move back
		position.x -= velocity.x;
		velocity.x *= -1;
	}

	//Move the circle up or down
	position.y += velocity.y;

	//If the circle went too far up or down
	if ((position.y - r < 0) || (position.y + r > height))
	{
		//Move back
		position.y -= velocity.y;
		velocity.y *= -1;
	}
}

void Circle::render(SDL_Renderer* gRenderer, Texture* gCircleTexture)
{
	gCircleTexture->render(gRenderer, position.x - r, position.y - r);
}

bool Circle::checkCollision(std::vector<Circle>& circles)
{
	for (auto& c : circles)
	{
		float rSquared = (this->r + c.getR()) * (this->r + c.getR());

		if (this->id != c.getID())
		{
			if (distanceSquared(this->position.x, this->position.y, c.getPosition().x, c.getPosition().y) < rSquared)
			{
				return true;
			}
		}
	}

	return false;
}

float Circle::distanceSquared(float x1, float y1, float x2, float y2)
{
	float dx = x1 - x2;
	float dy = y1 - y2;
	return dx * dx + dy * dy;
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
