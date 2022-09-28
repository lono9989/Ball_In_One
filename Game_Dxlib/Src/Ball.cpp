#include "Ball.h"

#include "Mylib/Debug.h"
#include "Rendering/Screen.h"
#include "Actor/Camera/Camera.h"
#include "Mylib/Dxlib_Input/MouseInput.h"

bool Ball::canMoveCamera = true;

Ball::Ball(IWorld* world, const GSvector3& position, float bounciness)
{
	// ワールドを設定
	world_ = world;
	// タグ名の設定
	tag_ = "BallTag";
	// 名前の設定
	name_ = "Ball";
	//衝突判定球の設定
	collider_ = BoundingSphere{ 1.0f,GSvector3{0.0f,0.0f,0.0f} };
	// 座標の初期化
	transform_.position(position);
	//物理演算クラスの初期化
	physics_ = Physics{ world_,&collider_,&transform_ };
	//反発係数の設定
	physics_.SetBounciness(bounciness);

	count = 0;
}

void Ball::update(float delta_time)
{
	switch (state_)
	{
	case Ball::State::Start:
		Start(delta_time);
		break;
	case Ball::State::Shot:
		Shot(delta_time);
		break;
	case Ball::State::Move:
		Move(delta_time);
		break;
	default:
		break;
	}
}

void Ball::react(Actor& other)
{
}

void Ball::draw() const
{
	Debug::DrawCoordinateAxis(transform_);
	DrawSphere3D(transform_.position().VECTOR_, 1, 16, color, color, TRUE);
	//collider().draw();
	Debug::DrawData(80, 245, transform_.position());

	DrawCircle(circlePos.x, circlePos.y, 105, Gray, TRUE);
	DrawCircle(circlePos.x, circlePos.y, 100, Block, TRUE);
	DrawCircle(circlePos.x, circlePos.y, 70, Blue, TRUE);
	DrawCircle(circlePos.x, circlePos.y, 50, Green, TRUE);
	DrawCircle(circlePos.x, circlePos.y, 30, Red, TRUE);
	DrawCircle(circlePos.x, circlePos.y, rote, White, FALSE);
}

void Ball::Start(float delta_time) {

	rote -= speed;

	if (rote < 20 || rote >= 100)speed = -speed;

	if (rote >= 70) { color = Block; Power = { gsRandf(-1,1),gsRandf(-1,1),gsRandf(-1,1) }; }
	else if (rote >= 50) { color = Blue; Power = Camera::getForward() * 0.5f; }
	else if (rote >= 30) { color = Green; Power = Camera::getForward(); }
	else { color = Red; Power = Camera::getForward() * 1.5f; }

	if (InputManager::GetInputDown(InputType::MOUSE, MOUSEEVENTF_LEFTDOWN)) {
		canMoveCamera = false;
		state_ = State::Shot;
	}
}

void Ball::Shot(float delta_time) {
	int mx, my;
	GetMousePoint(&mx, &my);

	if (InputManager::GetInputDown(InputType::MOUSE, MOUSEEVENTF_LEFTDOWN)) {
		canMoveCamera = true;
		state_ = State::Start;
	}

	if (my < (Screen::Height / 2) - 100) {
		physics_.AddForce(Power);
		count++;
		Actor::setViewActorName("Ball");
		state_ = State::Move;
	}

}

void Ball::Move(float delta_time) {
	physics_.Update(delta_time);
	GSvector3 pos = physics_.GetVelocity();

	if (pos.x <= 0.005 && pos.x >= -0.005 && pos.z <= 0.005 && pos.z >= -0.005) {
		Actor::setViewActorName("Player");
		canMoveCamera = true;
		state_ = State::Start;
	}
}

bool Ball::getCanMoveCamera() {
	return canMoveCamera;
}
