#pragma once
#include "EntityManager.h"
#include "InputData.h"
#include "Kid.h"
#include <Windows.h>
#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
using namespace Gdiplus;

char EntityManager::blockPixel[(1 + 19 + 1) * 32][(1 + 25 + 1) * 32];
char EntityManager::killerPixel[(1 + 19 + 1) * 32][(1 + 25 + 1) * 32];

EntityManager::EntityManager() {
	graphics = NULL;
	cachedBitmap = NULL;
	backgroundBrush = NULL;
}
EntityManager::~EntityManager() {
	destroy();
	destroyPreference();
}
void EntityManager::init(Graphics *graphics_, CachedBitmap *cachedBitmap_) {
	destroy();
	graphics = graphics_;
	cachedBitmap = cachedBitmap_;
}
void EntityManager::destroy() {

}
// 환경 설정
void EntityManager::setPreference(Gdiplus::Color &backgroundColor){
	destroyPreference();
	backgroundBrush = new Gdiplus::SolidBrush(backgroundColor);
}
void EntityManager::destroyPreference() {
	if (backgroundBrush != NULL) {
		delete backgroundBrush;
	}
}
void EntityManager::enterFrame(InputData& inputData) {

	inputData.preprocess();

	for (auto& c : kid) {
		c.enterFrame(inputData);
	}

	inputData.postprocess();

}

void EntityManager::draw() {
	
	extern Gdiplus::SolidBrush *blackBrush;
	extern Gdiplus::SolidBrush *whiteBrush;
	extern Rect mainWindowRect;
	// 배경
	graphics->FillRectangle(backgroundBrush, mainWindowRect.GetLeft(), mainWindowRect.GetTop(), mainWindowRect.GetRight() - mainWindowRect.GetLeft(), mainWindowRect.GetBottom() - mainWindowRect.GetTop());
	
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