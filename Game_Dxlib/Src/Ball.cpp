#include "Ball.h"

#include "Mylib/Debug.h"
#include "Rendering/Screen.h"
#include "Actor/Camera/Camera.h"

bool Ball::camera = false;

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

	color = GetColor(255, 255, 255);

	speed = 1;
	rote = 100;
	count = 0;

	Power = { 0,0,0 };
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
	DrawSphere3D(VECTOR{ transform_.position().x,transform_.position().y ,transform_.position().z }, 1, 16, color, color, TRUE);
	//collider().draw();
	Debug::DrawData(80, 245, transform_.position());

	DrawCircle(110, 400, 105, GetColor(128, 128, 128), TRUE);
	DrawCircle(110, 400, 100, GetColor(0, 0, 0), TRUE);
	DrawCircle(110, 400, 70, GetColor(0, 0, 255), TRUE);
	DrawCircle(110, 400, 50, GetColor(0, 255, 0), TRUE);
	DrawCircle(110, 400, 30, GetColor(255, 0, 0), TRUE);
	DrawCircle(110, 400, rote, GetColor(255, 255, 255), FALSE);
}

void Ball::Start(float delta_time) {

	rote -= speed;

	if (rote < 20 || rote >= 100)speed = -speed;

	if (rote >= 70) { color = GetColor(0, 0, 0); Power = { gsRandf(-1,1),gsRandf(-1,1),gsRandf(-1,1) }; }
	else if (rote >= 50) { color = GetColor(0, 0, 255); Power = Camera::getForward() * 0.5f; }
	else if (rote >= 30) { color = GetColor(0, 255, 0); Power = Camera::getForward(); }
	else { color = GetColor(255, 0, 0); Power = /*{ -1,1,0 };*/	Camera::getForward() * 1.5f; }

	if (InputManager::GetInputDown(InputType::MOUSE, MOUSEEVENTF_LEFTDOWN)) {
		camera = true;
		state_ = State::Shot;
	}
}

void Ball::Shot(float delta_time) {
	int mx, my;
	GetMousePoint(&mx, &my);

	if (my < (Screen::Height / 2) - 100 && count == 0) {
		physics_.AddForce(Power);
		count++;
		state_ = State::Move;
	}

}

void Ball::Move(float delta_time) {
	physics_.Update(delta_time);
	count = 0;

	GSvector3 pos = physics_.GetVelocity();

	if (pos.x <= 0.005 && pos.x >= -0.005 && pos.z <= 0.005 && pos.z >= -0.005) {
		camera = false;
		state_ = State::Start;
	}
}

bool Ball::getCamera() {
	return camera;
}
