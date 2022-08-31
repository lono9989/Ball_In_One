#include "Collision/Physics.h"
#include "Collision/BoundingSphere.h"
#include "Rendering/Field.h"
#include "Mylib/Debug.h"

//重力加速度
const float Gravity{ -0.980665f };


Physics::Physics()
{
}

Physics::Physics(IWorld* world, BoundingSphere* sphere, GStransform* transform, GSvector3 v) :
	velocity_{ v }
{
	world_ = world;
	sphere_ = sphere;
	transform_ = transform;
	CalcAnguler();
}

Physics::~Physics()
{
}

void Physics::Update(float delta_time)
{
	//フィールドとの衝突計算
	CollideField(delta_time);
	//重力
	velocity_.y += Gravity * delta_time;
	//回転速度の計算
	CalcAnguler();

	//トランスフォーム反映
	transform_->translate(velocity_, GStransform::Space::World);
	transform_->rotate(anguler_velocity_,GStransform::Space::World);

	//速度系計算
	if (is_rolling) {
	velocity_ *= (1-(0.2f * delta_time));
	}
}

void Physics::AddForce(GSvector3 power)
{
	velocity_ += power;
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

void Physics::CollideField(float delta_time)
{
	MV1_COLL_RESULT_POLY_DIM polydim;
	//フィールドとの衝突判定
	if (world_->field()->collide(sphere_->transform(transform_->localToWorldMatrix()), &polydim)) {
		is_rolling = false;
		//当たったポリゴンの法線をとりあえずまとめる
		GSvector3 normV{ 0.0f,0.0f,0.0f };
		for (int i = 0; i < polydim.HitNum; i++) {
			if (GSvector3::angle(velocity_, polydim.Dim[i].Normal) < 10.0f) {
				return;
			}
			normV += polydim.Dim[i].Normal;
			normV = normV.normalized();
		}

		//反射ベクトル(F=F+2aN)
		velocity_ -= (2.0f * GSvector3::dot(velocity_, normV) * normV);

		//反発係数をもとに減衰
		velocity_.y *= MAX(0.001f, CLAMP(((bounciness_ + world_->field()->Bounciness) / 2), 0.0f, 1.0f));
		if (ABS(velocity_.y) > 0.1f) {
			velocity_.x *= MAX(0.001f, CLAMP(((bounciness_ + world_->field()->Bounciness) / 2), 0.0f, 1.0f));
			velocity_.z *= MAX(0.001f, CLAMP(((bounciness_ + world_->field()->Bounciness) / 2), 0.0f, 1.0f));
		}
		else {
			is_rolling = true;
		}
		//押し戻し
		Line l{ transform_->position(), transform_->position() - normV * (sphere_->radius + 0.1f) };
		MV1_COLL_RESULT_POLY poly;
		if (world_->field()->collide(l, &poly))
		{
			GSvector3 pos = transform_->position();
			GSvector3 position{ poly.HitPosition };
			position += normV * (sphere_->radius);
			transform_->position(position);
			//
			if (ABS(velocity_.y) > 0.01f) {
				transform_->translate(GSvector3{ 0.0f,sphere_->radius - ABS(pos.y - poly.HitPosition.y),0.0f },
									  GStransform::Space::World);
			}
		}
	}
	//後処理
	DxLib::MV1CollResultPolyDimTerminate(polydim);
}

void Physics::CalcAnguler()
{
	float x = velocity_.z / (2.0f * GS_PI * sphere_->radius) * 360.0f;
	float z = velocity_.x / (2.0f * GS_PI * sphere_->radius) * 360.0f;
	anguler_velocity_ = GSvector3{ x,0.0f,-z };
}
