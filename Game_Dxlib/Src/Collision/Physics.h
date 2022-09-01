#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "Mylib/Mylib.h"
#include "DxLib.h"
#include "World/IWorld.h"

class BoundingSphere;

//�ȈՕ������Z�N���X
class Physics {
public:
	Physics();
	//���̗p(���ɕK�v�Ȍ`���o�Ă����Ƃ��̓R���X�g���N�^��ʌI�[�o�[���[�h���Ă��������B)
	Physics(IWorld* world, BoundingSphere* sphere, GStransform* transform, GSvector3 v = GSvector3{ 0.0f,0.0f,0.0f });
	~Physics();

	void Update(float delta_time);

	//�͂�������
	void AddForce(GSvector3 power);


	//�ϐ��ݒ�A�擾�֐�
	GSvector3 GetVelocity();
	void SetVelocity(GSvector3 v);
	GSvector3 GetAngulerVelocity();
	void SetAngulerVelocity(GSvector3 v);
	float GetBounciness();
	void SetBounciness(float bounce);
	void SetFreezePosition(bool x = false, bool y = false , bool z=false);
	/*float GetMass();
	void SetMass(float mass);*/
private:
	//�t�B�[���h�Ƃ̓����蔻��
	void CollideField(float delta_time);
	//��]���x�̌v�Z(velocity����̌v�Z)
	void CalcAnguler();
private:
	IWorld* world_{ nullptr };
	//�g�����X�t�H�[��
	GStransform* transform_{nullptr};
	//�R���C�_�[�̃|�C���^�[ (�Ȃ񂾂�����܂Ƃ߂����̂���肽��)
	BoundingSphere* sphere_{ nullptr };
	
	//���[���h���W�n�x�N�g���ł�
	//���x
	GSvector3 velocity_;
	//��]���x
	GSvector3 anguler_velocity_{0.0f,0.0f,0.0f};

	//�����W��
	float bounciness_{0.0f};

	//�ʒu�̌Œ艻
	bool freezePosition[3]{ false,false,false };

	//��]�͂ǂ�����Ĕ��f�����悤
	//bool freezeRotation[3]{ false,false,false };

	////���� 
	//float mass_{1.0f};

	bool is_rolling{ false };
};



#endif // !PHYSICS_H_
