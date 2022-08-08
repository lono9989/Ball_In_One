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
	/// �}�E�X�̓��͏�Ԃ𔻒�
	/// </summary>
	/// <param name="mouse">�}�E�X�̃{�^��(Dxlib�̃L�[�R�[�h)</param>
	/// <returns>������Ă��邩</returns>
	static bool GetMouse(int mouse);
	/// <summary>
	/// �}�E�X�������ꂽ���𔻒�
	/// </summary>
	/// <param name="mouse">�}�E�X�̃{�^��(Dxlib�̃L�[�R�[�h)</param>
	/// <returns>�����ꂽ�u��</returns>
	static bool GetMouseDown(int mouse);
	/// <summary>
	/// �}�E�X�������ꂽ���𔻒�
	/// </summary>
	/// <param name="mouse">�}�E�X�̃{�^��(Dxlib�̃L�[�R�[�h)</param>
	/// <returns>�������u��</returns>
	static bool GetMouseUp(int mouse);
	/// <summary>
	/// �}�E�X��x���W�����߂�
	/// </summary>
	/// <returns>x���W</returns>
	static int GetMouseX();
	/// <summary>
	/// �}�E�X��y���W�����߂�
	/// </summary>
	/// <returns>y���W</returns>
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
