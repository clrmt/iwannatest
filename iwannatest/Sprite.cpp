#include "Sprite.h"
#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")

Sprite::Sprite() {

	sprite = NULL;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			bitmap[i][j] = NULL;
		}
	}

}