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

void Tile::checkCollision(std::vector<Sprite*>& sprites)
{
	if (this->mType == 1)
	{
		for (auto& s : sprites)
		{
			Vector v;

			if (s->collider_type == 1)
			{

			}
			else if (s->collider_type == 2)
			{
				const int left = this->x + this->w - static_cast<int>(s->getPosition().x);
				const int right = static_cast<int>(s->getPosition().x) + static_cast<int>(s->sprite_width) - static_cast<int>(this->x);
				const int top = this->y + this->h - static_cast<int>(s->getPosition().y);
				const int bottom = static_cast<int>(s->getPosition().y) + static_cast<int>(s->sprite_height) - static_cast<int>(this->y);
				SDL_Log("Left: %i Right: %i Top: %i Bottom: %i", left, right, top, bottom);
				

				if (left > 0 && right > 0 && top > 0 && bottom > 0)
				{
					SDL_Log("Square/Tile collision detected");
					SDL_Log("BEFORE SEPARATION! Tile position: (%i, %i) Sprite position: (%f, %f)", this->x, this->y, s->getPosition().x, s->getPosition().y);
					s->setVelocity(Vector(0, 0));

					// Separation
					left < right ? v.x = left : v.x = -right;
					top < bottom ? v.y = top : v.y = -bottom;
					v.normalize();

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
