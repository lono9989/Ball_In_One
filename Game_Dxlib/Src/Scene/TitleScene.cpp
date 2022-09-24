#include "TitleScene.h"

#include "Mylib/DXlib_Input/InputManager.h"
#include "Mylib/Debug.h"

#include "Assets.h"
#include "Rendering/Screen.h"



void TitleScene::load()
{
	Assets::Texture_TitleBG = LoadGraph("Assets/Texture/Title.jpg");
	Assets::Texture_TitleLogo = LoadGraph("Assets/Texture/TitleLogo.png");
	Assets::Texture_TitleStart = LoadGraph("Assets/Texture/Start.png");
	Assets::Sound_TitleBGM = LoadSoundMem("Assets/Sound/title.mp3");
	Assets::Sound_TitleStart = LoadSoundMem("Assets/Sound/keybotton.mp3");
}

//�J�n
void TitleScene::start() {
	//�I���t���O�̏�����
	is_end_ = false;
	start_timer_ = 0.0f;
	start_alpha_ = 0;
	logoanim_end = false;

	PlaySoundMem(Assets::Sound_TitleBGM, DX_PLAYTYPE_LOOP);

	logo_position = { 0.0f,-800.0f * Screen::Height / 1080,0.0f };
	Tween::vector3(logo_position, GSvector3{ 0.0f,0.0f,0.0f }, 1.0f, [=](GSvector3 pos) {logo_position = pos; })
		.ease(EaseType::EaseOutBack)
		.overshoot(1.5f)
		.name("logopos")
		.delay(0.2f)
		.on_complete([=] {logoanim_end = true; });
}

//�X�V
void TitleScene::update(float delta_time) {

	if (logoanim_end) {
		start_timer_ += delta_time;
		start_alpha_ = ABS(std::sinf(start_timer_ /0.6f * DX_PI)) * 255;
	}

	//�G���^�[�L�[��������V�[���I��
	if (InputManager::GetInputDown(InputType::KEY, KEY_INPUT_RETURN)) {
		PlaySoundMem(Assets::Sound_TitleStart, DX_PLAYTYPE_NORMAL);
		is_end_ = true; //�V�[���I��
	}
}

//�`��
void TitleScene::draw()const {

	DrawExtendGraphF(0.0f, 0.0f, Screen::Width + 1.0f, Screen::Height + 1.0f, Assets::Texture_TitleBG, FALSE);

	DrawExtendGraphF(0.0f + logo_position.x, 0.0f + logo_position.y, Screen::Width + 1.0f + logo_position.x, Screen::Height + 1.0f + logo_position.y, Assets::Texture_TitleLogo, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, start_alpha_);
	DrawExtendGraphF(0.0f, 0.0f, Screen::Width + 1.0f, Screen::Height + 1.0f, Assets::Texture_TitleStart, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
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
	StopSoundMem(Assets::Sound_TitleBGM);
	DeleteGraph(Assets::Texture_TitleBG);
	DeleteGraph(Assets::Texture_TitleLogo);
	DeleteGraph(Assets::Texture_TitleStart);
	DeleteSoundMem(Assets::Sound_TitleBGM);
	DeleteSoundMem(Assets::Sound_TitleStart);
}