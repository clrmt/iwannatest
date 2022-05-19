#pragma once
#include "EntityManager.h"
#include "InputData.h"
#include "Kid.h"
#include <Windows.h>
#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")

char EntityManager::blockPixel[(1 + 19 + 1) * 32][(1 + 25 + 1) * 32];
char EntityManager::killerPixel[(1 + 19 + 1) * 32][(1 + 25 + 1) * 32];

void EntityManager::init(HDC hdc, RECT& rect, int cx, int cy) {
	destroy();
	graphics = new Gdiplus::Graphics(hdc);
	blockDC = CreateCompatibleDC(NULL);
	killerDC = CreateCompatibleDC(NULL);
	blockBitmap = CreateCompatibleBitmap(hdc, cx, cy);
	killerBitmap = CreateCompatibleBitmap(hdc, cx, cy);
	blockBitmapOld = (HBITMAP)SelectObject(blockDC, blockBitmap);
	killerBitmapOld = (HBITMAP)SelectObject(killerDC, killerBitmap);
	windowRect = rect;
}
// 환경 설정
void EntityManager::setPreference(Gdiplus::Color &backgroundColor){
	if(backgroundBrush != NULL){
		delete backgroundBrush;
	}
	backgroundBrush = new Gdiplus::SolidBrush(backgroundColor);
}
EntityManager::EntityManager() {
	blockDC = NULL;
	killerDC = NULL;
	blockBitmap = NULL;
	killerBitmap = NULL;
	blockBitmapOld = NULL;
	killerBitmapOld = NULL;
	windowRect.left = 0;
	windowRect.right = 0;
	windowRect.top = 0;
	windowRect.bottom = 0;
	graphics = NULL;
	backgroundBrush = NULL;
}
void EntityManager::destroy() {
	if (blockDC != NULL) {
		SelectObject(blockDC, blockBitmapOld);
		DeleteDC(blockDC);
		DeleteObject(blockBitmap);

		SelectObject(killerDC, killerBitmapOld);
		DeleteDC(killerDC);
		DeleteObject(killerBitmap);

		blockDC = NULL;
		delete graphics;
	}
}
void EntityManager::destroyPreference() {
	if (backgroundBrush != NULL) {
		delete backgroundBrush;
	}
}
EntityManager::~EntityManager() {
	destroy();
	destroyPreference();
}
void EntityManager::enterFrame(InputData& inputData) {

	inputData.preprocess();

	for (auto& c : kid) {
		c.enterFrame(inputData);
	}

	inputData.postprocess();

}

void EntityManager::draw() {
	
	// 배경
	graphics->FillRectangle(backgroundBrush, (INT)windowRect.left, (INT)windowRect.top, (INT)windowRect.right - (INT)windowRect.left, (INT)windowRect.bottom - (INT)windowRect.top);
	
	for (auto& c : block) {
		graphics->DrawImage(Block::image,
			(INT)c.x,
			(INT)c.y,
			c.imageNumber * c.imageWidth,
			c.imageState * c.imageHeight,
			c.imageWidth,
			c.imageHeight,
			Gdiplus::UnitPixel);
	}
	for (auto& c : kid) {
		if (c.left) {
			graphics->DrawImage(Kid::imageLeft,
				(INT)c.x + 2,
				(INT)c.y,
				c.image->GetWidth() - ((c.imageNumber + 1) * c.imageWidth),
				c.imageState * c.imageHeight,
				c.imageWidth,
				c.imageHeight,
				Gdiplus::UnitPixel);
		} else {
			graphics->DrawImage(Kid::image,
				(INT)c.x - 2,
				(INT)c.y,
				c.imageNumber * c.imageWidth,
				c.imageState * c.imageHeight,
				c.imageWidth,
				c.imageHeight,
				Gdiplus::UnitPixel);
		}
	}
}

void EntityManager::createKid(float y = 0.0f, float x = 0.0f) {
	Kid cKid;
	cKid.x = x;
	cKid.y = y;
	this->kid.push_back(cKid);
}

void EntityManager::createBlock(float y = 0.0f, float x = 0.0f) {
	Block cBlock;
	cBlock.x = x;
	cBlock.y = y;
	this->block.push_back(cBlock);
	for (long long yi = 0; yi < 32; yi++) {
		for (long long xi = 0; xi < 32; xi++) {
			this->blockPixel[(int)y + yi][(int)x + xi]++;
		}
	}

}

void EntityManager::createKid(Kid& c) {
	this->kid.push_back(c);
}

void EntityManager::createBlock(Block& c) {
	this->block.push_back(c);
}