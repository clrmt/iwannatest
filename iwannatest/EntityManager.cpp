#pragma once
#include <iostream>
#include "SpriteManager.h"
#include "EntityManager.h"
#include "InputData.h"
#include "Kid.h"
#include "Killer.h"
#include <Windows.h>
#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
using namespace Gdiplus;

Bitmap* EntityManager::blockBitmap;
Bitmap* EntityManager::killerBitmap;

EntityManager::EntityManager() {
	graphics = NULL;
	backgroundBrush = NULL;
	blockBitmap = NULL;
	blockGraphics = NULL;
	killerBitmap = NULL;
	killerGraphics = NULL;
}
EntityManager::~EntityManager() {
	destroy();
	destroyPreference();
	delete blockBitmap;
	delete blockGraphics;
	delete killerBitmap;
	delete killerGraphics;
}
void EntityManager::init(Gdiplus::Graphics *graphics_) {
	destroy();
	graphics = graphics_;

	extern Rect mainWindowRect;
	blockBitmap = new Bitmap(mainWindowRect.GetRight() - mainWindowRect.GetLeft(), mainWindowRect.GetBottom() - mainWindowRect.GetTop());
	blockGraphics = new Gdiplus::Graphics(blockBitmap);
	killerBitmap = new Bitmap(mainWindowRect.GetRight() - mainWindowRect.GetLeft(), mainWindowRect.GetBottom() - mainWindowRect.GetTop());
	killerGraphics = new Gdiplus::Graphics(killerBitmap);
}
void EntityManager::destroy() {
	if (blockBitmap != NULL) {
		delete blockBitmap;
		delete blockGraphics;
		delete killerBitmap;
		delete killerGraphics;
	}
}
// 환경 설정
void EntityManager::setPreference(Color &backgroundColor){
	destroyPreference();
	backgroundBrush = new SolidBrush(backgroundColor);
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
	
	extern SolidBrush *blackBrush;
	extern SolidBrush *whiteBrush;
	extern Rect mainWindowRect;
	// 배경
	graphics->FillRectangle(backgroundBrush, mainWindowRect.GetLeft(), mainWindowRect.GetTop(), mainWindowRect.GetRight() - mainWindowRect.GetLeft(), mainWindowRect.GetBottom() - mainWindowRect.GetTop());
	killerGraphics->FillRectangle(backgroundBrush, mainWindowRect.GetLeft(), mainWindowRect.GetTop(), mainWindowRect.GetRight() - mainWindowRect.GetLeft(), mainWindowRect.GetBottom() - mainWindowRect.GetTop());
	blockGraphics->FillRectangle(backgroundBrush, mainWindowRect.GetLeft(), mainWindowRect.GetTop(), mainWindowRect.GetRight() - mainWindowRect.GetLeft(), mainWindowRect.GetBottom() - mainWindowRect.GetTop());

	extern SpriteManager sprite;

	for (auto& c : block) {
		graphics->DrawCachedBitmap(sprite.block.bitmap[0][0], (INT)c.x, (INT)c.y);
		blockGraphics->DrawCachedBitmap(sprite.block.bitmap[0][0], (INT)c.x, (INT)c.y);
	}
	for (auto& c : kid) {
		if (c.left) {
			graphics->DrawCachedBitmap(sprite.kid.bitmap[c.imageState + 6][c.imageNumber], (INT)c.x + 2, (INT)c.y);
		} else {
			graphics->DrawCachedBitmap(sprite.kid.bitmap[c.imageState][c.imageNumber], (INT)c.x - 2, (INT)c.y);
		}
	}
}

void EntityManager::drawCollision() {

	extern SolidBrush *whiteBrush;
	extern SolidBrush *blackBrush;
	extern Rect mainWindowRect;

	killerGraphics->FillRectangle(whiteBrush, mainWindowRect.GetLeft(), mainWindowRect.GetTop(), mainWindowRect.GetRight() - mainWindowRect.GetLeft(), mainWindowRect.GetBottom() - mainWindowRect.GetTop());
	blockGraphics->FillRectangle(blackBrush, mainWindowRect.GetLeft(), mainWindowRect.GetTop(), mainWindowRect.GetRight() - mainWindowRect.GetLeft(), mainWindowRect.GetBottom() - mainWindowRect.GetTop());
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
}

void EntityManager::createKid(Kid& c) {
	this->kid.push_back(c);
}

void EntityManager::createBlock(Block& c) {
	this->block.push_back(c);
}

void EntityManager::createKiller(float y = 0.0f, float x = 0.0f) {
	Killer cKiller;
	cKiller.x = x;
	cKiller.y = y;
	this->killer.push_back(cKiller);
}
