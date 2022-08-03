#pragma once
#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")

class Sprite {
public:

	Gdiplus::Image *sprite;
	Gdiplus::CachedBitmap *bitmap[40][10];
	int frame[40];
	int number[40];
	int imageWidth;
	int imageHeight;
	int width;
	int height;

	Sprite();

};

