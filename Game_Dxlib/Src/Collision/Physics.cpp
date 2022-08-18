#include "Collision/Physics.h"
#include "Collision/BoundingSphere.h"
#include "Rendering/Field.h"

//重力加速度
const float Gravity{ -0.980665f };


Physics::Physics()
{
}

Physics::Physics(IWorld* world, BoundingSphere* sphere, GStransform* transform,GSvector3 v, GSvector3 angv) :
	velocity_{ v }, anguler_velocity_{ angv }
{
	world_ = world;
	sphere_ = sphere;
	transform_ = transform;
}

Physics::~Physics()
{
}

void Physics::Update(float delta_time)
{
	//重力
	velocity_.y += Gravity * delta_time;

	//速度系計算
	//velocity_ *= 0.8f * delta_time;
	//anguler_velocity_ *= 0.8f * delta_time;
	//衝突計算
	CollideField();

	//トランスフォーム反映
	transform_->translate(velocity_, GStransform::Space::World);
	transform_->rotate(
		GSvector3{ anguler_velocity_.z,0.0f,anguler_velocity_.x }
		/ (2.0f * GS_PI * sphere_->radius) * 360.0f,
		GStransform::Space::World);
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
	MV1_COLL_RESULT_POLY_DIM polydim;
	if (world_->field()->collide(sphere_->transform(transform_->localToWorldMatrix()), &polydim)) {
		//速度を保持
		GSvector3 Vvec = velocity_;
		//大きさ
		float scale = VSize(Vvec.VECTOR_);

		GSvector3 normV{ 0.0f,0.0f,0.0f };
		for (int i = 0; i < polydim.HitNum; i++) {
			normV.VECTOR_=VAdd(normV.VECTOR_, polydim.Dim[i].Normal);
			normV=normV.normalized();
		}
		Ray ray{ transform_->position(),normV };
		MV1_COLL_RESULT_POLY res;
		world_->field()->collide(ray, 100.0f, &res);

		
		GSvector3 dis = res.HitPosition-(-normV * sphere_->radius);

		velocity_ = transform_->position() - polydim.Dim[0].HitPosition;
		velocity_ = (velocity_ + 2 * dis).normalized() * scale;
		transform_->translate(dis * 2, GStransform::Space::World);

	}
	MV1CollResultPolyDimTerminate(polydim);
}
