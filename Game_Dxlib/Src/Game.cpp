#include "Game.h"
#include "Scene/TitleScene.h"
#include "Scene/GamePlayScene.h"

Game::~Game() 
{
	//シーンの終了
	scene_manager_.end();
}


void Game::Init()
{
	// Init処理
	InputManager::Init();
	//タイトルシーンの追加
	scene_manager_.add("TitleScene", new TitleScene());
	//ゲームプレイシーンの追加
	scene_manager_.add("GamePlayScene", new GamePlayScene());
	scene_manager_.load("TitleScene");
	//タイトルシーンから開始
	scene_manager_.change("TitleScene");
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
