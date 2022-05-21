#include "Kid.h"
#include "InputData.h"
#include <ObjIdl.h>
#include <gdiplus.h>
#include "EntityManager.h"
#pragma comment(lib, "gdiplus")

YX Kid::getCenterPosition() {
	return { y + 20.0f, x + 16.0f };
}

YX Kid::getDisplayPosition() {
	return { getCenterPosition().y + 2.0f, getCenterPosition().x };
}

bool Kid::isCollideWithBlock(float dx, float dy) {

	YX pos = getCenterPosition();
	
	for (int yi = -10; yi <= 10; yi++) {
		for (int xi = -5; xi <= 5; xi++) {
			if (EntityManager::blockPixel[(int)(pos.y + (float)yi + dy)][(int)(pos.x + (float)xi + dx)] > 0) {
				return true;
			}
		}
	}
	
	return false;
	
}

bool Kid::isCollideWithKiller() {

	YX pos = getCenterPosition();

	// 화면 밖을 넘어감
	if (pos.y <= 16.0f || pos.x <= 16.0f || pos.y >= 624.0f || pos.x >= 816.0f) {
		return true;
	}

	for (int yi = -5; yi <= 5; yi++) {
		for (int xi = -10; xi <= 10; xi++) {
			if (EntityManager::killerPixel[(int)(pos.y + (float)yi)][(int)(pos.x + (float)xi)] > 0) {
				return true;
			}
		}
	}

	return false;

}

// 1프레임마다
void Kid::enterFrame(InputData &inputData) {

	// 상하이동 vertical movement
	{
		
		if (ySpeed > 9.0f) {
			ySpeed = 9.0f;
		}

		ySpeed += 0.4f;

		if (inputData.key[inputData._keyCode_jump]) {
			inputData.key[inputData._keyCode_jump] = 0;
			if (land == 1) {
				jumpStartFrame = 0;
				land = 0;
				ySpeed = -8.0f;
			} else {
				if (jumpLeft > 0) {
					jumpLeft--;
					ySpeed = -7.0f;
				}
			}
		}

		if (ySpeed < 0.0f && inputData.keyUp[inputData._keyCode_jump]) {
			ySpeed *= 0.45f;
		}

		if (ySpeed > 0) {
			if (isCollideWithBlock(0.0f, ySpeed)) {
				land = 1;
				jumpLeft = jumpMax;
				ySpeed = 0.0f;
				while (!isCollideWithBlock(0.0f, 1.0f)) {
					y += 1.0f;
				}
			} else {
				y += ySpeed;
				// 착지 판정에서 다시 공중 판정인데 다음 프레임이 착지 판정인 경우?
				// 이렇게 처리하는게 맞나 싶음
				if (land == 1 && !isCollideWithBlock(0.0f, ySpeed + 0.4f)) {
					land = 0;
				}
			}
		}

		if (ySpeed < 0) {
			if (isCollideWithBlock(0.0f, ySpeed)) {
				ySpeed = 0.0f;
				while (!isCollideWithBlock(0.0f, -1.0f)) {
					y -= 1.0f;
				}
			} else {
				y += ySpeed;
			}
		}
		
	}

	if (inputData.key[inputData._keyCode_right]) {
		for (int i = 0; i < 3; i++) {
			if (!isCollideWithBlock(1.0f, 0.0f)) {
				x += 1.0f;
			} else {
				break;
			}
		}
		left = false;
	} else if (inputData.key[inputData._keyCode_left]) {
		for (int i = 0; i < 3; i++) {
			if (!isCollideWithBlock(-1.0f, 0.0f)) {
				x += -1.0f;
			} else {
				break;
			}
		}
		left = true;
	}

	int nextState;
	if (land) {
		if (inputData.key[inputData._keyCode_right]) {
			nextState = _KidState_Walking;
		} else if (inputData.key[inputData._keyCode_left]) {
			nextState = -_KidState_Walking;
		} else {
			nextState = _KidState_Idle;
		}
	} else {
		if (ySpeed < 0) {
			if (jumpStartFrame < 2) {
				nextState = _KidState_JumpStart;
				jumpStartFrame++;
			} else {
				nextState = _KidState_Jumping;
			}
		} else {
			nextState = _KidState_Falling;
		}
	}

	// 자동으로 이미지를 다음 프레임으로 조정
	imageFrame++;
	if (imageFrame >= imageFrameMax[imageState]) {
		imageFrame = 0;
		imageNumber++;
		if (imageNumber >= imageNumberMax[imageState]) {
			imageNumber = 0;
		}
	}

	// 상태가 바뀌어서 이미지 변환이 필요한 경우
	if (state != nextState) {
		state = nextState;
		imageState = abs(state);
		imageNumber = 0;
		imageFrame = 0;
	}

}
Gdiplus::Image* Kid::image;
Gdiplus::Image* Kid::imageLeft;