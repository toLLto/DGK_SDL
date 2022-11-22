#include "Circle.h"

Circle::Circle(int x, int y)
{
	//Initialize the circle box
	mPosX = x;
	mPosY = y;

	mCollider.r = CIRCLE_WIDTH / 2;

	//Initialize the velocity
	mVelX = CIRCLE_VEL;
	mVelY = CIRCLE_VEL;

	shiftColliders();
}

void Circle::move(CircleCollider& circle, const int width, const int height)
{
	//Move the circle left or right
	mPosX += mVelX;
	shiftColliders();

	//If the circle went too far to the left or right
	if ((mPosX - mCollider.r < 0) || (mPosX + mCollider.r > width)/* ||
		checkCollision(mCollider, circle)*/)
	{
		//Move back
		mPosX -= mVelX;
		mVelX *= -1;
		shiftColliders();
	}

	//Move the circle up or down
	mPosY += mVelY;
	shiftColliders();

	//If the circle went too far up or down
	if ((mPosY - mCollider.r < 0) || (mPosY + mCollider.r > height)/* ||
		checkCollision(mCollider, circle)*/)
	{
		//Move back
		mPosY -= mVelY;
		mVelY *= -1;
		shiftColliders();
	}
}

void Circle::render(SDL_Renderer* gRenderer, Texture* gCircleTexture)
{
	gCircleTexture->render(gRenderer, mPosX - mCollider.r, mPosY - mCollider.r);
}

CircleCollider& Circle::getCollider()
{
	return mCollider;
}

bool Circle::checkCollision(CircleCollider& c)
{
	if (vectorLength(this->mCollider.x, this->mCollider.y, c.x, c.y) < this->mCollider.r + c.r)
	{
		return true;
	}

	return false;
}

float Circle::vectorLength(float x1, float y1, float x2, float y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}


void Circle::shiftColliders()
{
	mCollider.x = mPosX;
	mCollider.y = mPosY;
}
