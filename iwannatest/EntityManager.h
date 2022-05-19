#pragma once
#include <vector>
#include "Kid.h"
#include "Block.h"
#include "InputData.h"
#include <ObjIdl.h>
#include <gdiplus.h>
#include <Windows.h>
#pragma comment(lib, "gdiplus")

class EntityManager {
public:
	std::vector<Kid> kid;
	std::vector<Block> block;

	static char blockPixel[(1 + 19 + 1) * 32][(1 + 25 + 1) * 32];
	static char killerPixel[(1 + 19 + 1) * 32][(1 + 25 + 1) * 32];

	HDC blockDC;
	HBITMAP blockBitmap;
	HBITMAP blockBitmapOld;
	Gdiplus::Graphics *blockGraphics;
	HDC killerDC;
	HBITMAP killerBitmap;
	HBITMAP killerBitmapOld;
	Gdiplus::Graphics *killerGraphics;
	RECT windowRect;
	Gdiplus::Graphics *graphics;
	Gdiplus::SolidBrush *backgroundBrush;

	void init(HDC hdc, RECT &rect, int cx, int cy);
	void setPreference(Gdiplus::Color &backgroundColor);
	void destroy();
	void destroyPreference();
	EntityManager();
	~EntityManager();
	void enterFrame(InputData &inputData);
	void draw();
	void createKid(float y, float x);
	void createBlock(float y, float x);
	void createKid(Kid &c);
	void createBlock(Block &c);
};

