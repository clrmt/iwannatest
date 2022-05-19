#pragma once
#include "Entity.h"
#include "InputData.h"
#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")

class Block : public Entity {
public:
	static Gdiplus::Image* image;
	const static int imageWidth = 32;
	const static int imageHeight = 32;
};

