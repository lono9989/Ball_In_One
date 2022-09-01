#include "GamePlayScene.h"
#include "Rendering/Field.h"
#include "Assets.h"
#include "Actor/Camera/Camera.h"
#include "Actor/Player/Player.h"
#include "Actor/Light/Light.h"
#include "Mylib/DXlib_Input/InputManager.h"

#include "Ball.h"


void GamePlayScene::load()
{

	//Assets::Mesh_Skydome = MV1LoadModel("");
	Assets::Mesh_Field = MV1LoadModel("Assets/Model/Field/room100.mv1");
	//Assets::Mesh_Player = MV1LoadModel("");
	//Assets::VShader_MMD = LoadVertexShader("");
	//Assets::PShader_MMD = LoadPixelShader("");
	//Assets::VShader_Normal = LoadVertexShader("");
	//Assets::PShader_Normal = LoadPixelShader("");
	//Assets::Texture_GradPlayer = LoadGraph("");

}

//開始
void GamePlayScene::start() {
	//マウスカーソルを非表示
	SetMouseDispFlag(FALSE);

	//スカイドームはZバッファを使わない
	MV1SetUseZBuffer(Assets::Mesh_Skydome, FALSE);
	MV1SetScale(Assets::Mesh_Field, VGet(0.1f, 0.1f, 0.1f));
	// フィールドクラスの追加
	world_.add_field(new Field{});
	//カメラクラスの追加
	world_.add_camera(new Camera{ &world_,GSvector3{0.0f,0.0f,0.0f} ,GSvector3{0.0f, 1.93f, 0.0f} });
	//ライトクラスの追加
	world_.add_light(new Light{ &world_ });
	//プレイヤの追加
	world_.add_actor(new Player{ &world_,Assets::Mesh_Player,GSvector3{2.0f,0.0f,20.0f} });

	world_.add_actor(new Ball(&world_, GSvector3{ 2.0f,10.0f,20.0f },0.8f));

	//終了フラグを初期化
	is_end_ = false;
	
}

//更新
void GamePlayScene::update(float delta_time) 
{
	//エンターキーで終了としておく
	if (InputManager::GetInputDown(InputType::KEY, KEY_INPUT_RETURN)) {
			is_end_ = true; //シーン終了
	}

	//ワールドの更新
	world_.update(delta_time);
	//スカイドームの座標をカメラ位置に
	MV1SetPosition(Assets::Mesh_Skydome, world_.camera()->transform().position().VECTOR_);
}



//描画
void GamePlayScene::draw()const {
	//スカイドームの描画
	MV1DrawModel(Assets::Mesh_Skydome);
	//シャドウマップの使用
	//SetUseShadowMap(0, Shadow_Handle);
	//ワールドの描画
	world_.draw();
	//シャドウマップの解除
	//SetUseShadowMap(0, -1);

	DrawString(80, 215, "プレイシーン（仮）", GetColor(255, 255, 255));
	
	
}

//終了しているか？
bool GamePlayScene::is_end()const {
	return is_end_; //終了フラグを返す
}

//次のシーンを返す
std::string GamePlayScene::next()const {
	return "TitleScene"; //タイトルシーンに戻る
}

//終了
void GamePlayScene::end() {
	//ワールドのクリア
	SetMouseDispFlag(TRUE);
	world_.clear();
	MV1DeleteModel(Assets::Mesh_Skydome);
	MV1DeleteModel(Assets::Mesh_Field);
	MV1DeleteModel(Assets::Mesh_Player);
	DeleteShader(Assets::VShader_MMD);
	DeleteShader(Assets::PShader_MMD);
	DeleteShader(Assets::VShader_Normal);
	DeleteShader(Assets::PShader_Normal);
	DeleteGraph(Assets::Texture_GradPlayer);

}