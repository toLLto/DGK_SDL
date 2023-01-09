#include "Camera.h"

Camera::Camera(int start_x, int start_y, int width, int height)
{
	camera = {start_x, start_y, width, height};
}

Camera::~Camera()
{
}

void Camera::move(Sprite& sprite, const int sWidth, const int sHeight, const int lWidth, const int lHeight, float alpha)
{
	camera.y = (sprite.getPosition().y + sprite.sprite_height / 2) - sHeight / 2;
	camera.x = (sprite.getPosition().x + sprite.sprite_width / 2) - sWidth / 2;

	//Lerp
	/*if (s1.getDirection())
	{
		camera.x = camera.x + (alpha * (s1.getPosition().x - (sWidth * 0.2) - camera.x));
	}
	else
	{
		camera.x = camera.x + (alpha * (s1.getPosition().x - (sWidth * 0.8) - camera.x));
	}*/

	//camera.x = ((s1.getPosition().x + s1.sprite_width / 2) + (s2.getPosition().x + s2.sprite_width / 2)) / 2 - sWidth / 2;
	//camera.y = ((s1.getPosition().y + s1.sprite_height / 2) + (s2.getPosition().y + s2.sprite_height / 2)) / 2 - sHeight / 2;

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

	//scale = 1.0 - std::max(abs(s1.getPosition().x - s2.getPosition().x), abs(s1.getPosition().y - s2.getPosition().y)) * factor;*/
}

double Camera::getScale()
{
	return scale;
}
