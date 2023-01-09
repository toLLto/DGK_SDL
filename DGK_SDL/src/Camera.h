#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>
#include "Sprite.h"

class Sprite;

class Camera
{
public:
	SDL_Rect camera;

	Camera(int start_x, int start_y, int width, int height);

	~Camera();

	void move(Sprite& s1, const int sWidth, const int sHeight, const int lWidth, const int lHeight, float alpha);

	double getScale();

protected:
	double scale = 1.0;
	double factor = 0.0003;
};

#endif CAMERA_H