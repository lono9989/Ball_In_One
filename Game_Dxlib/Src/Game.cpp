#include "Game.h"
#include "Scene/StartScene.h"
#include "Scene/TitleScene.h"
#include "Scene/GamePlayScene.h"
#include "Mylib/Tween/Tween.h"

Game::~Game() 
{
	//シーンの終了
	scene_manager_.end();
}


void Game::Init()
{
	// Init処理
	InputManager::Init();
	//スタートシーンの追加
	scene_manager_.add("StartScene", new StartScene());
	//タイトルシーンの追加
	scene_manager_.add("TitleScene", new TitleScene());
	//ゲームプレイシーンの追加
	scene_manager_.add("GamePlayScene", new GamePlayScene());
	//タイトルシーンから開始
	scene_manager_.change("StartScene");
}

void Game::Update(float delta_time)
{
	if (CheckHitKey(KEY_INPUT_ESCAPE) ==TRUE) {
		is_end = true;
	}
	// 更新処理
	InputManager::Update();
	//シーンの更新
	scene_manager_.update(delta_time);
	//Tweenの更新
	Tween::update(delta_time);
}

void Game::Draw()
{
	// 描画処理

	//シーンの描画
	scene_manager_.draw();
}

bool Game::IsEnd()
{
	return is_end;
}
