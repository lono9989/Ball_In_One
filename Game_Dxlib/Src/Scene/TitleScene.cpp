#include "TitleScene.h"

#include "Mylib/Mylib.h"
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
}

//更新
void TitleScene::update(float delta_time) {
	timer_ += delta_time;
	start_position_.y = 10.0f * sinf(timer_ * 4.0f)*Screen::Height/1080;
	//エンターキー押したらシーン終了
	if (InputManager::GetInputDown(InputType::KEY, KEY_INPUT_RETURN)) {
		PlaySoundMem(Assets::Sound_TitleStart,DX_PLAYTYPE_NORMAL);
		is_end_ = true; //シーン終了
	}
}

//描画
void TitleScene::draw()const {
	DrawExtendGraphF(0.0f, 0.0f, Screen::Width + 1.0f, Screen::Height + 1.0f, Assets::Texture_TitleBG, FALSE);
	DrawExtendGraphF(0.0f, 0.0f, Screen::Width + 1.0f, Screen::Height + 1.0f, Assets::Texture_TitleLogo, TRUE);
	DrawExtendGraphF(0.0f + start_position_.x, 0.0f + start_position_.y,
		start_position_.x + Screen::Width + 1.0f, start_position_.y + Screen::Height + 1.0f, Assets::Texture_TitleStart, TRUE);
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