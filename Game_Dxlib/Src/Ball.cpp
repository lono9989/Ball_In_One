#include "Ball.h"

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
}

void Ball::update(float delta_time)
{
	physics_.Update(delta_time);
}

void Ball::react(Actor& other)
{
}

void Ball::draw() const
{
	collider().draw();
}
