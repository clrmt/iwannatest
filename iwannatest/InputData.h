#pragma once
class InputData {
public:

	constexpr static int keySize = 256;
	constexpr static int realKeySize = 10;

	constexpr static int _keyCode_null = 0;
	constexpr static int _keyCode_jump = 1;
	constexpr static int _keyCode_shoot = 2;
	constexpr static int _keyCode_left = 3;
	constexpr static int _keyCode_right = 4;
	constexpr static int _keyCode_restart = 5;

	constexpr static int _keyType_null = 0;
	constexpr static int _keyType_constant = 1;
	constexpr static int _keyType_once = 2;

	int key[realKeySize];
	int keyPress[realKeySize];
	int keyUp[realKeySize];

	int keyType[realKeySize];

	int keyMapping[keySize];
	
	void preprocess(); // enterFrame에서의 전처리
	void postprocess(); // enterFrame에서의 후처리

	InputData();

	// public 입출력
	void setKeyDown(int keyCode);
	void setKeyUp(int keyCode);

};

