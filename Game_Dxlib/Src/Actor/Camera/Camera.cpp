#include "Camera.h"
#include "DxLib.h"
#include "Rendering/Screen.h"
#include "World/IWorld.h"
#include "Collision/Line.h"
#include "Rendering/Field.h"
#include "Mylib/Dxlib_Input/MouseInput.h"
#include "Ball.h"

#include <string>


// カメラの注視点の補正値
const GSvector3 ReferencePointOffset{ 0.0f, 11.0f, 0.0f };
const GSvector3 ReferenceBallPointOffset{ 0.0f, 3.0f, 0.0f };

const float RotateSpeed{ 50.0f };
const float ZoomSpeed{ 2.0f };

Camera* Camera::camera{ nullptr };
GSvector3 Camera::forward_{ 0,0,0 };

Camera::Camera(IWorld* world, const GSvector3& position, const GSvector3& at)
{
	camera = this;
	// ワールドを設定
	world_ = world;
	// タグの設定
	tag_ = "CamaraTag";
	// 名前の設定
	name_ = "Camera";
	// 視点の位置を設定
	transform_.position(position);
	// 注視点を設定
	transform_.lookAt(at);
	// ｘ軸周りの回転角度の初期化
	pitch_ = 0.0f;
	// ｙ軸周りの回転角度の初期化
	yaw_ = (at - position).getYaw();
	MouseInput::GetMouseDif_and_SetPos(Screen::Width / 2, Screen::Height / 2);
	SetupCamera_Perspective(DEG_TO_RAD(Fov_));

	Actor::setViewActorName("Player");
}

void Camera::update(float delta_time)
{
	switch (state_)
	{
	case CamState::Ortho:
		break;
	case CamState::TPS:
		update_Tps(delta_time);
		break;
	case CamState::FPS:
		update_Fps(delta_time);
		break;
	default:
		break;
	}
}

void Camera::draw() const
{
	// 視点の位置
	GSvector3 eye = transform_.position();
	// 注視点の位置
	GSvector3 at = eye + transform_.forward();
	// 視点の上方向
	GSvector3 up = transform_.up();

	SetCameraPositionAndTargetAndUpVec(eye.VECTOR_, at.VECTOR_, up.VECTOR_);
}

void Camera::update_Tps(float delta_time)
{
	// プレーヤーを検索
	Actor* actor = world_->find_actor(view_actor_name_);

	if (actor == nullptr) return;
	VECTOR vec = MouseInput::GetMouseDif_and_SetPos(Screen::Width / 2, Screen::Height / 2);

	if (Ball::getCanMoveCamera()) {
		// y軸まわりにカメラを回転させる
		yaw_ += vec.x * RotateSpeed * delta_time;
		// x軸まわりにカメラを回転させる
		pitch_ -= vec.y * RotateSpeed * delta_time;
		// x軸まわりの回転角度の制限をする
		pitch_ = CLAMP(pitch_, -75.0f, 85.0f);

		PlayerOffset.z -= ZoomSpeed * GetMouseWheelRotVolF();
		PlayerOffset.z = CLAMP(PlayerOffset.z, 5.0f, 40.0f);
		if (PlayerOffset.z < 10.0f) {
			pitch_ = CLAMP(pitch_, -75.0f, 85.0f - (10.0f - PlayerOffset.z) * 5.0f);
		}
	}
	//注視点の座標を求める
	GSvector3 at = actor->transform().position() + (view_actor_name_ != "Ball" ? ReferencePointOffset : ReferenceBallPointOffset);
	// カメラの座標を求める
	GSvector3 position = at + GSquaternion::euler(pitch_, yaw_, 0.0f) * PlayerOffset;

	// フィールドとの衝突判定
	Line line{ at, position };
	MV1_COLL_RESULT_POLY res;
	if (world_->field()->collide(line, &res)) {
		position.VECTOR_ = VAdd(res.HitPosition, VScale(VNorm(VSub(res.HitPosition, position.VECTOR_)), 0.8f));
	}

	forward_ = transform_.forward();

	// 座標の設定
	transform_.position(position);
	// 注視点の方向を見る
	transform_.lookAt(at);
}

void Camera::update_Fps(float delta_time)
{
}


void Camera::ChangeMode(CamState state)
{
	state_ = state;
}

GSvector3 Camera::getForward() {
	return forward_;
}
