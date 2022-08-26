#include "Collision/Physics.h"
#include "Collision/BoundingSphere.h"
#include "Rendering/Field.h"
#include "Mylib/Debug.h"

//重力加速度
const float Gravity{ -0.980665f };


Physics::Physics()
{
}

Physics::Physics(IWorld* world, BoundingSphere* sphere, GStransform* transform, GSvector3 v, GSvector3 angv) :
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
	//velocity_ = velocity_*(1-(0.925f * delta_time));
	//anguler_velocity_ = anguler_velocity_ *(1-( 0.8f * delta_time));
	
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

float Physics::GetBounciness()
{
	return bounciness_;
}

void Physics::SetBounciness(float bounce)
{
	bounciness_ = bounce;
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
	GSvector3 intersect;
	if (world_->field()->collide(sphere_->transform(transform_->localToWorldMatrix()), &polydim, &intersect)) {
		//当たったポリゴンの法線をとりあえずまとめる
		GSvector3 normV{ 0.0f,0.0f,0.0f };
		for (int i = 0; i < polydim.HitNum; i++) {
			normV.VECTOR_ = VAdd(normV.VECTOR_, polydim.Dim[i].Normal);
			normV = normV.normalized();
		}

		//デバッグ
		//Debug::Log(normV);
		//Debug::Log(velocity_);

		//反射ベクトル(F=F+2aN)
		velocity_ = velocity_-(2*GSvector3::dot(velocity_,normV)*normV);
		//反発係数をもとに減衰
		velocity_ *= MAX(0.001f,CLAMP(((bounciness_ + world_->field()->Bounciness) / 2), 0.0f, 1.0f));
		
		//押し戻し
		Line l{ transform_->position(), transform_->position()-normV*(sphere_->radius+0.1f) };
		MV1_COLL_RESULT_POLY poly;
		if (world_->field()->collide(l, &poly)) 
		{
			GSvector3 position{ poly.HitPosition };
			position += normV * (sphere_->radius);
			transform_->position(position);
		}
	}
	DxLib::MV1CollResultPolyDimTerminate(polydim);
}
