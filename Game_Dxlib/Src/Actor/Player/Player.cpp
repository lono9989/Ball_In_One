#include "Player.h"

#include "World/IWorld.h"
#include "Mylib/Mylib.h"
#include "Rendering/Field.h"
#include "Assets.h"

enum {
	AnimIdle = 0,
	AnimWalking = 1,
	AnimRunning = 2,
};

//歩き速度
const float WalkSpeed{ 23.0f };
//回転速度
const float RotateSpeed{ 12.0f };
// 自分の高さ
const float PlayerHeight{ 9.0f };
// 衝突判定用の半径
const float PlayerRadius{ 2.0f };
// 足元のオフセット
const float FootOffset{ 0.5f };
// 重力値
const float Gravity{ -0.98f };
//走りの倍率
const float Runningmagni{ 2.5f };


Player::Player(IWorld* world, int handle, const GSvector3& position) :
	mesh_{ handle,AnimIdle,true },
	motion_{ AnimIdle },
	motion_loop_{ true },
	state_{ State_::Moving }
{
	// ワールドを設定
	world_ = world;
	// タグ名の設定
	tag_ = "PlayerTag";
	// 名前の設定
	name_ = "Player";
	//衝突判定球の設定
	collider_ = BoundingSphere{ PlayerRadius,GSvector3{0.0f, PlayerHeight, 0.0f} };
	// 座標の初期化
	transform_.position(position);
	// メッシュの変換行列を初期化
	mesh_.TransForm(transform_.localToWorldMatrix());
}

void Player::update(float delta_time)
{
	Update_state(delta_time);

	// 重力値を更新
	velocity_.y += Gravity * delta_time;
	// 重力を加える
	transform_.translate(0.0f, velocity_.y, 0.0f);
	// フィールドとの衝突判定
	Collide_Field();

	//モーション変更
	mesh_.Change_Motion(motion_, motion_loop_);
	//メッシュの更新
	mesh_.Update(delta_time);
	//メッシュの変換行列
	mesh_.TransForm(transform_.localToWorldMatrix());
}

void Player::react(Actor& other)
{
}

void Player::draw() const
{
	/*
	MV1SetUseOrigShader(TRUE);
	SetUseTextureToShader(1, Assets::Texture_GradPlayer);
	SetUseVertexShader(Assets::VShader_MMD);
	SetUsePixelShader(Assets::PShader_MMD);
	MV1SetUseOrigShader(FALSE);
	*/

	//mesh_.Draw();
	collider().draw();
}

void Player::draw_transparent() const
{
	//mesh_.Trans_Draw();
}

void Player::draw_shadowmap1() const
{
	mesh_.Draw();
}

void Player::Collide_Field()
{
	// 壁との衝突判定（球体との判定）
	GSvector3 inter; // 衝突後の球体の中心座標
	if(world_->field()->collide(collider(),&colresdim_,&inter)) {
		// y座標は変更しない
		inter.y = transform_.position().y;
		// 補正後の座標に変更する
		transform_.position(inter);
		MV1CollResultPolyDimTerminate(colresdim_);

	}
	// 地面との衝突判定（線分との交差判定）
	GSvector3 position = transform_.position();
	Line line;
	line.start = position + collider_.center;
	line.end = position + GSvector3{ 0.0f, -FootOffset, 0.0f };
	GSvector3 intersect;  // 地面との交点
	if (world_->field()->collide(line,&colres_)) {
		// 交点の位置からy座標のみ補正する
		position.y = colres_.HitPosition.y;
		// 座標を変更する
		transform_.position(position);
		// 重力を初期化する
		velocity_.y = 0.0f;
	}
}

void Player::Collide_Actor(Actor& other)
{
}

void Player::Update_state(float delta_time)
{
	//移動処理
	switch (state_)
	{
	case Player::State_::Moving:
		Move(delta_time);
		break;
	case Player::State_::Jumping:
		Jump(delta_time);
		break;
	default:
		break;
	}
	//状態タイマの更新
	state_timer_ += delta_time;
}

void Player::Move(float delta_time)
{
	// カメラの前方向ベクトルを取得
	GSvector3 forward = world_->camera()->transform().forward();
	forward.y = 0.0f;
	forward = forward.normalized();
	// カメラの右方向ベクトルを取得
	GSvector3 right = world_->camera()->transform().right();
	right.y = 0.0f;
	right = right.normalized();
	// キーの入力値から移動ベクトルを計算
	GSvector3 velocity{ 0.0f, 0.0f, 0.0f };



	if (InputManager::GetInput(InputType::KEY,KEY_INPUT_W))velocity += forward;      // 前進
	if (InputManager::GetInput(InputType::KEY, KEY_INPUT_S))velocity -= forward;      // 後退
	if (InputManager::GetInput(InputType::KEY, KEY_INPUT_A)) velocity += right;       // 左
	if (InputManager::GetInput(InputType::KEY, KEY_INPUT_D)) velocity -= right;       // 右
	velocity = velocity.normalized() * WalkSpeed * delta_time;

	// 何もしなければアイドル状態
	int motion{ AnimIdle };
	// 移動しているか？
	if (velocity.length() != 0.0f) {
		// 向きの補間
		GSquaternion  rotation =
			GSquaternion::rotateTowards(
				transform_.rotation(),
				GSquaternion::lookRotation(-velocity), RotateSpeed * delta_time * 60.0f);
		transform_.rotation(rotation);
		// 移動中のモーションにする
		motion = AnimWalking;
		if (InputManager::GetInput(InputType::KEY, KEY_INPUT_LSHIFT)) {
			velocity*= Runningmagni;
			motion = AnimRunning;
		}
	}
	// モーションの変更
	Change_state(State_::Moving, motion);

	// 移動量のxz成分だけ更新
	velocity_.x = velocity.x;
	velocity_.z = velocity.z;
	// 平行移動する（ワールド基準）
	transform_.translate(velocity_, GStransform::Space::World);


}

void Player::Jump(float delta_time)
{
}

void Player::Change_state(State_ state,int motion, bool loop)
{
	motion_ = motion;
	motion_loop_ = loop;
	state_ = state;
	state_timer_ = 0.0f;
	
}
