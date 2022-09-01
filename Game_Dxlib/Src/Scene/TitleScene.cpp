#include "TitleScene.h"
#include "Mylib/Mylib.h"
#include "DxLib.h"
#include "Mylib/DXlib_Input/InputManager.h"

void TitleScene::load()
{
}

//�J�n
void TitleScene::start() {
	//�I���t���O�̏�����
	is_end_ = false;
}

//�X�V
void TitleScene::update(float delta_time) {
	//�G���^�[�L�[��������V�[���I��
	if (InputManager::GetInputDown(InputType::KEY, KEY_INPUT_RETURN)) {
		is_end_ = true; //�V�[���I��
	}
}

//�`��
void TitleScene::draw()const {
	//gsFontParameter(0, 50, "�l�r �S�V�b�N");
	//gsTextPos(80, 215);
	DrawString(80, 215,"�^�C�g���V�[���i���j", GetColor(255, 255, 255));
	//gsFontParameter(0, 16, "�l�r �S�V�b�N");
}

//�I�����Ă��邩�H
bool TitleScene::is_end()const {
	return is_end_; //�V�[���I��
}

//���̃V�[������Ԃ�
std::string TitleScene::next()const {
	return "GamePlayScene"; //���̃V�[������Ԃ�
}

//�I��
void TitleScene::end() {
}