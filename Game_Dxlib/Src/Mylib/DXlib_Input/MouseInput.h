#ifndef MOUSE_INPUT_H_
#define MOUSE_INPUT_H_

#include "DxLib.h"
class MouseInput {
public:
	MouseInput() = default;
	~MouseInput() = default;
	static void Init();
	static void Update();
	/// <summary>
	/// マウスの入力状態を判定
	/// </summary>
	/// <param name="mouse">マウスのボタン(Dxlibのキーコード)</param>
	/// <returns>押されているか</returns>
	static bool GetMouse(int mouse);
	/// <summary>
	/// マウスが押されたかを判定
	/// </summary>
	/// <param name="mouse">マウスのボタン(Dxlibのキーコード)</param>
	/// <returns>押された瞬間</returns>
	static bool GetMouseDown(int mouse);
	/// <summary>
	/// マウスが離されたかを判定
	/// </summary>
	/// <param name="mouse">マウスのボタン(Dxlibのキーコード)</param>
	/// <returns>離した瞬間</returns>
	static bool GetMouseUp(int mouse);
	/// <summary>
	/// マウスのx座標を求める
	/// </summary>
	/// <returns>x座標</returns>
	static int GetMouseX();
	/// <summary>
	/// マウスのy座標を求める
	/// </summary>
	/// <returns>y座標</returns>
	static int GetMouseY();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	static VECTOR GetMouseDif_and_SetPos(int x, int y);
	
private:
	static int xBuf;
	static int yBuf;
	static int mouseState[256];
	static int resultState[256];

};

#endif // !MOUSE_INPUT_H_
