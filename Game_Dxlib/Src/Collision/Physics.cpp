#include "Collision/Physics.h"
#include "Collision/BoundingSphere.h"
#include "Rendering/Field.h"
#include "Mylib/Debug.h"

//重力加速度
const float Gravity{ -0.980665f };
//地面を転がっているときの減衰率(0が少ない→1が大きい)
const float Attenuation{ 0.4f };

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
	if (freezePosition[0]) {
		velocity_.x = 0.0f;
	}
	if (freezePosition[1]) {
		velocity_.y = 0.0f;
	}
	if (freezePosition[2]) {
		velocity_.z = 0.0f;
	}
	//回転速度の計算
	CalcAnguler();

	//トランスフォーム反映
	transform_->translate(velocity_, GStransform::Space::World);
	transform_->rotate(anguler_velocity_, GStransform::Space::World);

	//速度系計算(回転中であれば速度を少しずつ弱める)
	if (is_rolling) {
		velocity_ *= (1 - (Attenuation * delta_time));
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

void Physics::SetFreezePosition(bool x, bool y, bool z)
{
	freezePosition[0] = x;
	freezePosition[1] = y;
	freezePosition[2] = z;
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
		//先にfalse判定を乗っけておく
		is_rolling = false;
		//当たったポリゴンの法線をとりあえずまとめる
		GSvector3 normV{ 0.0f,0.0f,0.0f };
		for (int i = 0; i < polydim.HitNum; i++) {
			float f = GSvector3::angle(velocity_, polydim.Dim[i].Normal);
			if (f < 90.0f) {
				normV -= polydim.Dim[i].Normal;
			}
			else if (f ==90.0f) {
				break;
			}
			else {
				normV += polydim.Dim[i].Normal;
			}
			normV = normV.normalized();
		}

		//反射ベクトル(F=F+2aN)
		gsVector3Reflection(&velocity_, &velocity_, &normV);

		//反発係数をもとに減衰
		velocity_.y *= MAX(0.001f, CLAMP(((bounciness_ + world_->field()->Bounciness) / 2), 0.0f, 1.0f));
		//もしy速度が遅いときは転がす
		if (ABS(velocity_.y) > 0.1f) {
			velocity_.x *= MAX(0.001f, CLAMP(((bounciness_ + world_->field()->Bounciness) / 2), 0.0f, 1.0f));
			velocity_.z *= MAX(0.001f, CLAMP(((bounciness_ + world_->field()->Bounciness) / 2), 0.0f, 1.0f));
		}
		else {
			//転がす
			is_rolling = true;
		}
		//押し戻し
		Line l{ transform_->position(), transform_->position() - normV * (sphere_->radius + 0.1f) };
		MV1_COLL_RESULT_POLY poly;
		if (world_->field()->collide(l, &poly))
		{
			//元の位置
			GSvector3 pos = transform_->position();
			//変更後の位置
			GSvector3 position{ poly.HitPosition };
			//当たった場所から法線方向に半径分離す
			position += normV * (sphere_->radius);
			//反映
			transform_->position(position);
			//y速度が遅く無ければ埋まっている分壁から離す
			if (ABS(velocity_.y) > 0.01f) {
				transform_->translate(normV * (sphere_->radius - (pos - poly.HitPosition).length()),
					GStransform::Space::World);
			}
		}
	}
	//後処理
	DxLib::MV1CollResultPolyDimTerminate(polydim);
}

void Physics::CalcAnguler()
{
	//速度から回転速度を求める
	//(円周分の速度で弧の長さの割合を求め360度をかけオイラー法で角度を算出)
	float x = velocity_.z / (2.0f * GS_PI * sphere_->radius) * 360.0f;
	float z = velocity_.x / (2.0f * GS_PI * sphere_->radius) * 360.0f;
	//反映
	anguler_velocity_ = GSvector3{ x,0.0f,-z };
}
