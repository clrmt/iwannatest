#pragma once
#include "Entity.h"
#include "InputData.h"
#include <ObjIdl.h>
#include <gdiplus.h>
#include "Point.h"
#pragma comment(lib, "gdiplus")

class Kid : public Entity {
public:
	bool land = false;
	bool left = false;
	int jumpLeft = 1;
	int jumpMax = 1;
	int jumpStartFrame = 0;
	float ySpeed = 0.0f;
	int state = 0;

	void enterFrame(InputData &inputData);
	bool isCollideWithBlock(float dx, float dy);
	bool isCollideWithKiller();
	Point getCenterPosition();
	Point getDisplayPosition();
	
	static Gdiplus::Image* image;
	static Gdiplus::Image* imageLeft;
	const static int imageWidth = 32;
	const static int imageHeight = 32;
	const static int _KidState_Idle = 0;
	const static int _KidState_Walking = 1;
	const static int _KidState_JumpStart = 2;
	const static int _KidState_Jumping = 3;
	const static int _KidState_Falling = 4;
	const static int _KidState_Vine = 5;
	int imageFrameMax[10] = {5, 3, 4, 4, 4, 4, 4, 4, 4, 4};
	int imageNumberMax[10] = {4, 6, 2, 2, 2, 2, 0, 0, 0, 0};
};