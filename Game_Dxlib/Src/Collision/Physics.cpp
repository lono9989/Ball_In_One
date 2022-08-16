#include "Collision/Physics.h"
#include "Collision/BoundingSphere.h"

//重力加速度
const float Gravity{ -0.980665f };


Physics::Physics(BoundingSphere* sphere, GStransform* transform, GSvector3 v, GSvector3 angv) :
	sphere_{ sphere }, transform_{ transform },
	velocity_{ v }, anguler_velocity_{ angv }
{
}

Physics::~Physics()
{
}

void Physics::Update(float delta_time)
{
	//重力
	velocity_.y += Gravity;

	//速度系計算
	velocity_ *= 0.8f;
	anguler_velocity_ *= 0.8f;

	//トランスフォーム反映
	transform_->translate(velocity_, GStransform::Space::World);
	transform_->rotate(
		GSvector3{ anguler_velocity_.z,0.0f,anguler_velocity_.x }
		/ (2.0f * GS_PI * sphere_->radius) * 360.0f,
		GStransform::Space::World);

	//衝突計算
	CollideField();
}

void Physics::AddForce(GSvector3 power)
{
	velocity_ += power;
	anguler_velocity_ += power;
}

GSvector3 Physics::GetVelocity()
{
	return velocity_;
}

void Physics::SetVelocity(GSvector3 v)
{
	velocity_ = v;
}

GSvector3 Physics::GetAngulerVelocity()
{
	return anguler_velocity_;
}

void Physics::SetAngulerVelocity(GSvector3 v)
{
	anguler_velocity_ = v;
}

//float Physics::GetMass()
//{
//	return mass_;
//}
//
//void Physics::SetMass(float mass)
//{
//	mass_ = mass;
//}

void Physics::CollideField()
{
	//ここにいろいろ書く
}
