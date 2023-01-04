#include "Tile.h"

Tile::Tile(int x, int y, int tileType)
{
	//Get the offsets
	this->x = x;
	this->y = y;

	//Set the collision box
	this->w = TILE_WIDTH;
	this->h = TILE_HEIGHT;

	//Get the tile type
	mType = tileType;
}

void Tile::render(SDL_Renderer* gRenderer, Camera& camera, Texture* gTileTexture, SDL_Rect* gTileClips)
{
	//Show the tile
	gTileTexture->render(gRenderer, this->x - camera.camera.x, this->y - camera.camera.y, camera.getScale(), &gTileClips[mType]);
}

int Tile::clamp(int x, int min, int max)
{
	if (x < min)
		return min;
	else if (x > max)
		return max;
	else if (x > min && x < max)
		return x;
}

void Tile::checkCollision(std::vector<Sprite*>& sprites)
{
	if (this->mType == 1)
	{
		for (auto& s : sprites)
		{
			Vector v;

			if (s->collider_type == 1)
			{
				Vector f = Vector(
					clamp(s->getPosition().x + s->getRadius(), this->x, this->x + this->w),
					clamp(s->getPosition().y + s->getRadius(), this->y, this->y + this->h)
				);
				Vector c = Vector(s->getPosition().x + s->getRadius(), s->getPosition().y + s->getRadius());
				Vector tmp = c - f;
				//v = v - f;
				const float length = tmp.length();

				if (length < s->getRadius())
				{
					SDL_Log("Circle/Tile collision detected");
					SDL_Log("BEFORE SEPARATION! Tile position: (%i, %i) Sprite position: (%f, %f)", this->x, this->y, s->getPosition().x, s->getPosition().y);
					s->setVelocity(Vector(0, 0));

					if (s->getPosition().x + s->getRadius() == f.x && s->getPosition().y + s->getRadius() == f.y)
					{
						const int left = static_cast<int>(s->getPosition().x) + static_cast<int>(s->getRadius()) - this->x + static_cast<int>(s->getRadius());
						const int right = this->x + this->w - static_cast<int>(s->getPosition().x) + static_cast<int>(s->getRadius() * 2);
						const int top = static_cast<int>(s->getPosition().y) + static_cast<int>(s->getRadius()) - this->y + static_cast<int>(s->getRadius());
						const int bottom = this->y + this->h - static_cast<int>(s->getPosition().y) + static_cast<int>(s->getRadius() * 2);

						//Separation
						left < right ? v.x = left : v.x = -right;
						top < bottom ? v.y = top : v.y = -bottom;

						if (abs(v.x) > abs(v.y))
							v.x = 0;
						else
							v.y = 0;

						//v.normalize();

						Vector newPosition = s->getPosition() + v;
						s->setPosition(newPosition);
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
						/*this->position += (res * (s->sprite_width / 2 - length * 0.5f));
						s->setPosition(s->position - res * (this->radius - length * 0.5f));*/

						Vector newPosition = s->getPosition() + res;
						s->setPosition(newPosition);

						//this->setVelocity(Vector(0, 0));
						//this->position += res;
					}
					SDL_Log("AFTER SEPARATION! Tile position: (%i, %i) Sprite position: (%f, %f)", this->x, this->y, s->getPosition().x, s->getPosition().y);
				}
			}
			else if (s->collider_type == 2)
			{
				const int left = this->x + this->w - static_cast<int>(s->getPosition().x);
				const int right = static_cast<int>(s->getPosition().x) + static_cast<int>(s->sprite_width) - static_cast<int>(this->x);
				const int top = this->y + this->h - static_cast<int>(s->getPosition().y);
				const int bottom = static_cast<int>(s->getPosition().y) + static_cast<int>(s->sprite_height) - static_cast<int>(this->y);
				//SDL_Log("Left: %i Right: %i Top: %i Bottom: %i", left, right, top, bottom);
				

				if (left > 0 && right > 0 && top > 0 && bottom > 0)
				{
					SDL_Log("Square/Tile collision detected");
					SDL_Log("BEFORE SEPARATION! Tile position: (%i, %i) Sprite position: (%f, %f)", this->x, this->y, s->getPosition().x, s->getPosition().y);
					s->setVelocity(Vector(0, 0));

					// Separation
					left < right ? v.x = left : v.x = -right;
					top < bottom ? v.y = top : v.y = -bottom;
					//v.normalize();

					if (abs(v.x) > abs(v.y))
						v.x = 0;
					else
						v.y = 0;

					Vector newPosition = s->getPosition() + v;
					s->setPosition(newPosition);
					
					SDL_Log("AFTER SEPARATION! Tile position: (%i, %i) Sprite position: (%f, %f)", this->x, this->y, s->getPosition().x, s->getPosition().y);
				}
				
			}
		}
	}
}

int Tile::getType()
{
	return mType;
}

int Tile::getX()
{
	return x;
}

int Tile::getY()
{
	return y;
}

int Tile::getW()
{
	return w;
}

int Tile::getH()
{
	return h;
}
