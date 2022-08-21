#include "Ball.h"

#include "Mylib/Debug.h"

Ball::Ball(IWorld* world, const GSvector3& position)
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
	physics_.SetBounciness(0.7f);
}

void Ball::update(float delta_time)
{
	physics_.Update(delta_time);
	if (InputManager::GetInputDown(InputType::KEY, KEY_INPUT_G)) {
		physics_.AddForce(GSvector3{ 0.5f,-0.5f,0.0f });
	}
}

void Ball::react(Actor& other)
{
}

void Ball::draw() const
{
	Debug::DrawCoordinateAxis(transform_);
	collider().draw();
	std::string str = std::to_string(transform_.position().x) + "," + std::to_string(transform_.position().y) + "," + std::to_string(transform_.position().z);
	DrawString(80, 245, str.c_str(), GetColor(255, 255, 255));
}
