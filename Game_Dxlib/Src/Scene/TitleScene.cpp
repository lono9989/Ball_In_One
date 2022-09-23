#include "TitleScene.h"

#include "Mylib/DXlib_Input/InputManager.h"

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

//開始
void TitleScene::start() {
	//終了フラグの初期化
	is_end_ = false;
	PlaySoundMem(Assets::Sound_TitleBGM, DX_PLAYTYPE_LOOP);

	logo_position = { 0.0f,-800.0f * Screen::Height / 1080,0.0f };
	Tween::vector3(logo_position, GSvector3{ 0.0f,0.0f,0.0f }, 1.0f, [=](GSvector3 pos) {logo_position = pos; })
		.ease(EaseType::EaseOutBack)
		.overshoot(1.5f)
		.name("logopos")
		.delay(0.2f);
}

//更新
void TitleScene::update(float delta_time) {
	start_timer_ += delta_time;

	//エンターキー押したらシーン終了
	if (InputManager::GetInputDown(InputType::KEY, KEY_INPUT_RETURN)) {
		PlaySoundMem(Assets::Sound_TitleStart,DX_PLAYTYPE_NORMAL);
		is_end_ = true; //シーン終了
	}
}

//描画
void TitleScene::draw()const {

	DrawExtendGraphF(0.0f, 0.0f, Screen::Width + 1.0f, Screen::Height + 1.0f, Assets::Texture_TitleBG, FALSE);

	DrawExtendGraphF(0.0f+logo_position.x, 0.0f + logo_position.y, Screen::Width + 1.0f + logo_position.x, Screen::Height + 1.0f + logo_position.y, Assets::Texture_TitleLogo, TRUE);

	DrawExtendGraphF(0.0f, 0.0f,Screen::Width + 1.0f, Screen::Height + 1.0f, Assets::Texture_TitleStart, TRUE);
}

//終了しているか？
bool TitleScene::is_end()const {
	return is_end_; //シーン終了
}

//次のシーン名を返す
std::string TitleScene::next()const {
	return "GamePlayScene"; //次のシーン名を返す
}

//終了
void TitleScene::end() {
	StopSoundMem(Assets::Sound_TitleBGM);
	DeleteGraph(Assets::Texture_TitleBG);
	DeleteGraph(Assets::Texture_TitleLogo);
	DeleteGraph(Assets::Texture_TitleStart);
	DeleteSoundMem(Assets::Sound_TitleBGM);
	DeleteSoundMem(Assets::Sound_TitleStart);
}