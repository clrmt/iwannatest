#pragma once
#include "Killer.h"
#include "SpriteManager.h"
#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")

Sprite SpriteManager::kid;
Sprite SpriteManager::block;
Sprite SpriteManager::killer[Killer::_killerType_total];

SpriteManager::SpriteManager() {

	allocated = false;

}

void SpriteManager::allocate() {

	allocated = true;
	
	// img
	kid.sprite = new Gdiplus::Image(L"sprites/kid.png");
	kid.imageWidth = 32 * 6;
	kid.imageHeight = 32 * 6;
	kid.width = 32;
	kid.height = 32;
	kid.frame[0] = 5;
	kid.frame[1] = 3;
	kid.frame[2] = 4;
	kid.frame[3] = 4;
	kid.frame[4] = 4;
	kid.frame[5] = 4;
	kid.number[0] = 4;
	kid.number[1] = 6;
	kid.number[2] = 2;
	kid.number[3] = 2;
	kid.number[4] = 2;
	kid.number[5] = 2;

	// 정방향 오른쪽 키드이미지 캐싱
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < kid.number[i]; j++) {
			Gdiplus::Bitmap _bit(kid.width, kid.height);
			Gdiplus::Graphics _graphics(&_bit);
			_graphics.DrawImage(kid.sprite, 0, 0, j * kid.width, i * kid.height, kid.width, kid.height, Gdiplus::UnitPixel);
			kid.bitmap[i][j] = new Gdiplus::CachedBitmap(&_bit, &_graphics);
			//kid.bitmap[i][j] = new CachedBitmap(&_bit, mainWindowInnerGraphics);
		}
	}

	kid.sprite->RotateFlip(Gdiplus::RotateNoneFlipX);

	// 정방향 왼쪽 키드이미지 캐싱
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < kid.number[i]; j++) {
			Gdiplus::Bitmap _bit(kid.width, kid.height);
			Gdiplus::Graphics _graphics(&_bit);
			_graphics.DrawImage(kid.sprite, 0, 0, kid.imageWidth - ((j + 1) * kid.width), i * kid.height, kid.width, kid.height, Gdiplus::UnitPixel);
			kid.bitmap[i + 6][j] = new Gdiplus::CachedBitmap(&_bit, &_graphics);
		}
	}

	kid.sprite->RotateFlip(Gdiplus::RotateNoneFlipXY);

	// 역방향 오른쪽 키드이미지 캐싱
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < kid.number[i]; j++) {
			Gdiplus::Bitmap _bit(kid.width, kid.height);
			Gdiplus::Graphics _graphics(&_bit);
			_graphics.DrawImage(kid.sprite, 0, 0, j * kid.width, kid.imageHeight - ((i + 1) * kid.height), kid.width, kid.height, Gdiplus::UnitPixel);
			kid.bitmap[i + 12][j] = new Gdiplus::CachedBitmap(&_bit, &_graphics);
		}
	}

	kid.sprite->RotateFlip(Gdiplus::RotateNoneFlipX);

	// 역방향 왼쪽 키드이미지 캐싱
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < kid.number[i]; j++) {
			Gdiplus::Bitmap _bit(kid.width, kid.height);
			Gdiplus::Graphics _graphics(&_bit);
			_graphics.DrawImage(kid.sprite, 0, 0, kid.imageWidth - ((j + 1) * kid.width), kid.imageHeight - ((i + 1) * kid.height), kid.width, kid.height, Gdiplus::UnitPixel);
			kid.bitmap[i + 18][j] = new Gdiplus::CachedBitmap(&_bit, &_graphics);
		}
	}

	kid.sprite->RotateFlip(Gdiplus::RotateNoneFlipXY);



	block.sprite = new Gdiplus::Image(L"sprites/block.png");
	block.imageWidth = 32 * 1;
	block.imageHeight = 32 * 1;
	block.width = 32;
	block.height = 32;
	block.frame[0] = 1;
	block.number[0] = 1;

	{
		Gdiplus::Bitmap _bit(block.width, block.height);
		Gdiplus::Graphics _graphics(&_bit);
		_graphics.DrawImage(block.sprite, 0, 0, 0, 0, block.width, block.height, Gdiplus::UnitPixel);
		block.bitmap[0][0] = new Gdiplus::CachedBitmap(&_bit, &_graphics);
	}

}

SpriteManager::~SpriteManager() {
	free();
}

void SpriteManager::free() {
	if (allocated) {
		allocated = false;

		delete kid.sprite;
		delete block.sprite;

		for (int i = 0; i < 24; i++) {
			for (int j = 0; j < kid.number[i%6]; j++) {
				delete kid.bitmap[i][j];
			}
		}

		delete block.sprite;
		delete block.bitmap[0][0];

	}
}