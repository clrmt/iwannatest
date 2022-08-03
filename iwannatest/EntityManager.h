#pragma once
#include <vector>
#include "Kid.h"
#include "Block.h"
#include "Killer.h"
#include "InputData.h"
#include <ObjIdl.h>
#include <gdiplus.h>
#include <Windows.h>
#pragma comment(lib, "gdiplus")
using namespace Gdiplus;

class EntityManager {
public:
	std::vector<Kid> kid;
	std::vector<Block> block;
	std::vector<Killer> killer;

	static Bitmap* blockBitmap;
	Gdiplus::Graphics* blockGraphics;

	static Bitmap* killerBitmap;
	Gdiplus::Graphics* killerGraphics;

	Graphics *graphics;
	Gdiplus::SolidBrush *backgroundBrush;


	
	void init(Gdiplus::Graphics *graphics_);
	void setPreference(Gdiplus::Color &backgroundColor);
	void destroy();
	void destroyPreference();
	EntityManager();
	~EntityManager();
	void enterFrame(InputData &inputData);
	void draw();
	void drawCollision();
	void createKid(float y, float x);
	void createBlock(float y, float x);
	void createKid(Kid &c);
	void createBlock(Block &c);
	void createKiller(float y, float x);

};

