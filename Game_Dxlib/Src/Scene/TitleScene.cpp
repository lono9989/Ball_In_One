#include "TitleScene.h"
#include "Mylib/Mylib.h"
#include "DxLib.h"
#include "Mylib/DXlib_Input/InputManager.h"

void TitleScene::load()
{
}

//開始
void TitleScene::start() {
	//終了フラグの初期化
	is_end_ = false;
}

//更新
void TitleScene::update(float delta_time) {
	//エンターキー押したらシーン終了
	if (InputManager::GetInputDown(InputType::KEY, KEY_INPUT_RETURN)) {
		is_end_ = true; //シーン終了
	}
}

//描画
void TitleScene::draw()const {
	//gsFontParameter(0, 50, "ＭＳ ゴシック");
	//gsTextPos(80, 215);
	DrawString(80, 215,"タイトルシーン（仮）", GetColor(255, 255, 255));
	//gsFontParameter(0, 16, "ＭＳ ゴシック");
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
}