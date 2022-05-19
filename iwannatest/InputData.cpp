#pragma once
#include "InputData.h"
#include <Windows.h>

InputData::InputData() {

	for (int i = 0; i < realKeySize; i++) {
		key[i] = 0;
		keyUp[i] = 0;
		keyPress[i] = 0;
		keyType[i] = 0;
	}

	keyType[_keyCode_left] = _keyType_constant;
	keyType[_keyCode_right] = _keyType_constant;
	keyType[_keyCode_shoot] = _keyType_once;
	keyType[_keyCode_jump] = _keyType_once;
	keyType[_keyCode_restart] = _keyType_once;

	//keyMapping[VK_LSHIFT] = _keyCode_jump;
	keyMapping[VK_SHIFT] = _keyCode_jump;
	keyMapping['Z'] = _keyCode_shoot;
	keyMapping[VK_LEFT] = _keyCode_left;
	keyMapping[VK_RIGHT] = _keyCode_right;

}

void InputData::preprocess() {

	for (int i = 0; i < realKeySize; i++) {
		if (keyType[i] == _keyType_null) {

		} else if (keyType[i] == _keyType_constant) {
			if (keyUp[i] == 1){
				key[i] = 0;
			}
		} else if (keyType[i] == _keyType_once) {
			if (keyUp[i] == 1) {
				key[i] = 0;
				keyPress[i] = 0;
			} else if (key[i] == 1) {
				if (keyPress[i] == 1) {
					key[i] = 0;
				} else {
					keyPress[i] = 1;
				}
			}
		}
	}
}
void InputData::postprocess() {

	for (int i = 0; i < realKeySize; i++) {
		keyUp[i] = 0;
	}

}

void InputData::setKeyDown(int keyCode) {
	if (0 <= keyCode && keyCode < 256) {
		key[keyMapping[keyCode]] = 1;
	}
}
void InputData::setKeyUp(int keyCode) {
	if (0 <= keyCode && keyCode < 256) {
		keyUp[keyMapping[keyCode]] = 1;
	}
}
