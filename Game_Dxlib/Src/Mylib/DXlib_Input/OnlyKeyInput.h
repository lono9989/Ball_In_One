#ifndef ONLY_KEY_INPUT_H_
#define ONLY_KEY_INPUT_H_

#include"DxLib.h"
#include <array>

class OnlyKeyInput {
public:
	OnlyKeyInput() = default;
	~OnlyKeyInput() = default;
	static void Init();
	static void Update();
	static bool GetKey(int buttonID);
	static bool GetKeyDown(int buttonID);
	static bool GetKeyUp(int buttonID);
public:
	static char KeyBuf[256];
	static int resultBuf[256];
};

#endif // !ONLY_KEY_INPUT_H_