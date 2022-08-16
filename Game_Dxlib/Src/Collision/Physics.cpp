#include "Collision/Physics.h"
#include "Collision/BoundingSphere.h"

//�d�͉����x
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
	//�d��
	velocity_.y += Gravity;

	//���x�n�v�Z
	velocity_ *= 0.8f;
	anguler_velocity_ *= 0.8f;

	//�g�����X�t�H�[�����f
	transform_->translate(velocity_, GStransform::Space::World);
	transform_->rotate(
		GSvector3{ anguler_velocity_.z,0.0f,anguler_velocity_.x }
		/ (2.0f * GS_PI * sphere_->radius) * 360.0f,
		GStransform::Space::World);

	//�Փˌv�Z
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
	//�����ɂ��낢�돑��
}
