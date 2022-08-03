#pragma once
class InputData {
public:

	constexpr static int keySize = 256;

	constexpr static int _keyCode_null = 0;
	constexpr static int _keyCode_jump = 1;
	constexpr static int _keyCode_shoot = 2;
	constexpr static int _keyCode_left = 3;
	constexpr static int _keyCode_right = 4;
	constexpr static int _keyCode_restart = 5;
	constexpr static int actionSize = 6;

	constexpr static int _keyType_null = 0;
	constexpr static int _keyType_constant = 1;
	constexpr static int _keyType_once = 2;

	int keyUp[actionSize];
	int keyDown[actionSize];
	int keyType[actionSize];
	int keyMapping[keySize]; // 0~128을 실제 액션으로 변환

	void preprocess(); // enterFrame에서의 전처리
	void postprocess(); // enterFrame에서의 후처리

	InputData();

	void setKeyDown(int keyCode);
	void setKeyUp(int keyCode);
	bool isKeyDown(int actionCode);
	bool isKeyUp(int actionCode);

};

