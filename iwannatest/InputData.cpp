#pragma once
#include "InputData.h"
#include <Windows.h>

InputData::InputData() {

	for (int i = 0; i < actionSize; i++) {
		keyUp[i] = 0;
		keyDown[i] = 0;
		keyType[i] = 0;
	}
	for (int i = 0; i < keySize; i++) {
		keyMapping[i] = 0;
	}
	
	keyType[_keyCode_left] = _keyType_constant;
	keyType[_keyCode_right] = _keyType_constant;
	keyType[_keyCode_shoot] = _keyType_once;
	keyType[_keyCode_jump] = _keyType_once;
	keyType[_keyCode_restart] = _keyType_once;

	keyMapping[VK_SHIFT] = _keyCode_jump;
	keyMapping['Z'] = _keyCode_shoot;
	keyMapping[VK_LEFT] = _keyCode_left;
	keyMapping[VK_RIGHT] = _keyCode_right;

}

void InputData::preprocess() {

}
void InputData::postprocess() {
	for (int i = 0; i < actionSize; i++) {
		if (keyType[i] == _keyType_once) {
			keyDown[i] &= ~0b1;
			keyUp[i] &= ~0b1;
		}
	}
}

void InputData::setKeyDown(int keyCode) {
	if (0 <= keyCode && keyCode < keySize) {
		int action = keyMapping[keyCode];
		if (keyType[action] == _keyType_once) {
			if (keyDown[action] < 2) {
				keyDown[action] = 0b11;
			}
		}
		if (keyType[action] == _keyType_constant) {
			keyDown[action] = 1;
		}
	}
}
void InputData::setKeyUp(int keyCode) {
	if (0 <= keyCode && keyCode < keySize) {
		int action = keyMapping[keyCode];
		if (keyType[action] == _keyType_once) {
			keyUp[action] = 1;
			keyDown[action] &= ~0b10;
		}
		if (keyType[action] == _keyType_constant) {
			keyDown[action] = 0;
		}
	}
}

bool InputData::isKeyDown(int actionCode) {
	if ((keyDown[actionCode] & 0b1) != 0) {
		return true;
	} else {
		return false;
	}
}
bool InputData::isKeyUp(int actionCode) {
	if ((keyUp[actionCode] & 0b1) != 0) {
		return true;
	} else {
		return false;
	}
}