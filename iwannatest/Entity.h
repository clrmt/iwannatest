#pragma once
typedef long long ll;
#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")

class Entity {
public:
	float x;
	float y;
	int imageState;
	int imageNumber;
	int imageFrame;
	int imageFlip;

	Entity();
	void enterFrame();
};

