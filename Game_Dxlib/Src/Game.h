#ifndef GAME_H_
#define GAME_H_

#include "Rendering/Screen.h"
#include "Scene/SceneManager.h"
#include "Mylib/DXlib_Input/InputManager.h"
#include"World/World.h"

#include <vector>
#include <math.h>
#include <string>

class Game
{
public:
	/*      ��{ }��.h�ɏ������Ƃ�cpp�ɕ����ď����͂��̏����ԂԂ��.h�ɏ����Ă��悢 */
	Game() {  }; // �������R���X�g���N�^
	~Game(); // �j�������f�X�g���N�^

	void Init(); // Init����(��`����)
	void Update(float delta_time); // �X�V����(��`����)
	void Draw();// �`�揈��(��`����)

private:
	//�V�[���}�l�[�W���[
	SceneManager scene_manager_;

};
#endif