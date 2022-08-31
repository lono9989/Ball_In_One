#include "Ball.h"

#include "Mylib/Debug.h"

Ball::Ball(IWorld* world, const GSvector3& position,float bounciness)
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
	physics_ = Physics{ world_,&collider_,&transform_ };
	physics_.SetBounciness(bounciness);

	color = GetColor(255, 255, 255);

	speed = 1.f;
	rote = 100.f;

	Power = { 0,0,0 };
}

void Ball::update(float delta_time)
{
	physics_.Update(delta_time);
	if (InputManager::GetInputDown(InputType::KEY, KEY_INPUT_G)) {
		physics_.AddForce(Power);
	}

	rote -= speed;

	if (rote < 20.f || rote >= 100.f)speed = -speed;

	if (rote >= 70) { color = GetColor(0, 0, 0); Power = { gsRandf(-1,1),gsRandf(-1,1),gsRandf(-1,1) }; }
	else if (rote >= 50) { color = GetColor(0, 0, 255); Power = { -0.2f,0.2f,0 }; }
	else if (rote >= 30) { color = GetColor(0, 255, 0); Power = { -0.5f,0.5f,0 }; }
	else { color = GetColor(255, 0, 0); Power = { -1,1,0 }; }
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
