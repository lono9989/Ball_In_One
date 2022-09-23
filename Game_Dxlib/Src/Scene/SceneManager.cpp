#include "SceneManager.h"
#include "SceneNull.h"

#include "DxLib.h"

#include "Mylib/Tween/Tween.h"

static SceneNull scene_null;// nullシーン（何もしないダミーシーン）

// コンストラクタ
SceneManager::SceneManager() :
	current_scene_{ &scene_null } {
}

// デストラクタ
SceneManager::~SceneManager() {
	clear();
}

// 更新
void SceneManager::update(float delta_time) {
	// シーンの更新
	current_scene_->update(delta_time);

	// シーンが終了しているか？
	if (current_scene_->is_end()) {

		if (!change_load) {
		// シーンを変更する
		load(current_scene_->next());
		}
		else if (GetASyncLoadNum() == 0) {
			Tween::clear();
			change(current_scene_->next());
		}
		if (GetASyncLoadNum() != 0) {
			str += ".";
			if (str == "Now Loading.......") {
				str = "Now Loading";
			}
		}
	}
}

// 描画
void SceneManager::draw()const {
	
	// 現在のシーンを描画
	current_scene_->draw();
	
	if (GetASyncLoadNum() != 0) {

		// 非同期読み込みの数を描画
		DrawFormatString(200, 0, GetColor(255, 255, 255), "非同期読み込みの数 %d", GetASyncLoadNum());
		DrawFormatString(0, 50, GetColor(255, 255, 255), str.c_str());
	}
}

// 終了
void SceneManager::end() {
	// 現在のシーンを終了
	current_scene_->end();
	// nullシーンにしておく
	current_scene_ = &scene_null;
}

// シーンの追加
void SceneManager::add(const std::string& name, IScene* scene) {
	scenes_[name] = scene;
}

// シーンの変更
void SceneManager::change(const std::string& name) {
	// 現在のシーンを終了
	end();
	// 現在のシーンを変更
	current_scene_ = scenes_[name];
	// 現在のシーンを開始
	current_scene_->start();
	change_load = false;
}

void SceneManager::load(const std::string& name)
{
	change_load = true;
	// 非同期読み込み設定に変更
	SetUseASyncLoadFlag(TRUE);
	scenes_[name]->load();
	// 同期読み込み設定に変更
	SetUseASyncLoadFlag(FALSE);
}

// シーンの消去
void SceneManager::clear() {
	// 念のためシーンの終了を呼び出す
	end();
	// unordered_map内のシーンをすべて削除
	for (auto& pair : scenes_) {
		// シーンの削除
		delete pair.second;
	}
	// unordered_mapを消去
	scenes_.clear();
}