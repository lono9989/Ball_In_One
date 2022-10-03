#include "Collision/Physics.h"
#include "Collision/BoundingSphere.h"
#include "Rendering/Field.h"
#include "Mylib/Debug.h"

//�d�͉����x
const float Gravity{ -0.980665f };
//�n�ʂ�]�����Ă���Ƃ��̌�����(0�����Ȃ���1���傫��)
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
	//�t�B�[���h�Ƃ̏Փˌv�Z
	CollideField(delta_time);
	//�d��
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
	//��]���x�̌v�Z
	CalcAnguler();

	//�g�����X�t�H�[�����f
	transform_->translate(velocity_, GStransform::Space::World);
	transform_->rotate(anguler_velocity_, GStransform::Space::World);

	//���x�n�v�Z(��]���ł���Α��x����������߂�)
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
	//�t�B�[���h�Ƃ̏Փ˔���
	if (world_->field()->collide(sphere_->transform(transform_->localToWorldMatrix()), &polydim)) {
		//���false�����������Ă���
		is_rolling = false;
		//���������|���S���̖@�����Ƃ肠�����܂Ƃ߂�
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

		//���˃x�N�g��(F=F+2aN)
		gsVector3Reflection(&velocity_, &velocity_, &normV);

		//�����W�������ƂɌ���
		velocity_.y *= MAX(0.001f, CLAMP(((bounciness_ + world_->field()->Bounciness) / 2), 0.0f, 1.0f));
		//����y���x���x���Ƃ��͓]����
		if (ABS(velocity_.y) > 0.1f) {
			velocity_.x *= MAX(0.001f, CLAMP(((bounciness_ + world_->field()->Bounciness) / 2), 0.0f, 1.0f));
			velocity_.z *= MAX(0.001f, CLAMP(((bounciness_ + world_->field()->Bounciness) / 2), 0.0f, 1.0f));
		}
		else {
			//�]����
			is_rolling = true;
		}
		//�����߂�
		Line l{ transform_->position(), transform_->position() - normV * (sphere_->radius + 0.1f) };
		MV1_COLL_RESULT_POLY poly;
		if (world_->field()->collide(l, &poly))
		{
			//���̈ʒu
			GSvector3 pos = transform_->position();
			//�ύX��̈ʒu
			GSvector3 position{ poly.HitPosition };
			//���������ꏊ����@�������ɔ��a������
			position += normV * (sphere_->radius);
			//���f
			transform_->position(position);
			//y���x���x��������Ζ��܂��Ă��镪�ǂ��痣��
			if (ABS(velocity_.y) > 0.01f) {
				transform_->translate(normV * (sphere_->radius - (pos - poly.HitPosition).length()),
					GStransform::Space::World);
			}
		}
	}
	//�㏈��
	DxLib::MV1CollResultPolyDimTerminate(polydim);
}

void Physics::CalcAnguler()
{
	//���x�����]���x�����߂�
	//(�~�����̑��x�Ōʂ̒����̊���������360�x�������I�C���[�@�Ŋp�x���Z�o)
	float x = velocity_.z / (2.0f * GS_PI * sphere_->radius) * 360.0f;
	float z = velocity_.x / (2.0f * GS_PI * sphere_->radius) * 360.0f;
	//���f
	anguler_velocity_ = GSvector3{ x,0.0f,-z };
}
