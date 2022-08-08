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
	/*      ↓{ }を.hに書くことでcppに分けて書くはずの処理ぶぶんを.hに書いてもよい */
	Game() {  }; // 初期化コンストラクタ
	~Game(); // 破棄処理デストラクタ

	void Init(); // Init処理(定義だけ)
	void Update(float delta_time); // 更新処理(定義だけ)
	void Draw();// 描画処理(定義だけ)

private:
	//シーンマネージャー
	SceneManager scene_manager_;

};
#endif