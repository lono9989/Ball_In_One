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
	Physics(IWorld* world, BoundingSphere* sphere, GStransform* transform, GSvector3 v = GSvector3{ 0.0f,0.0f,0.0f }, GSvector3 angv = GSvector3{ 0.0f,0.0f,0.0f });
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
	/*float GetMass();
	void SetMass(float mass);*/
private:
	//�t�B�[���h�Ƃ̓����蔻��
	void CollideField();
private:
	IWorld* world_{ nullptr };
	//�g�����X�t�H�[��
	GStransform* transform_{nullptr};
	//�R���C�_�[�̃|�C���^�[ (�Ȃ񂾂�����܂Ƃ߂����̂���肽��)
	BoundingSphere* sphere_{ nullptr };
	//���x
	GSvector3 velocity_;
	//��]���x
	GSvector3 anguler_velocity_;

	//�����W��
	float bounciness_{0.0f};

	//�܂����f�����ĂȂ�
	bool freezePosition[3]{ false,false,false };
	bool freezeRotation[3]{ false,false,false };
	////���� 
	//float mass_{1.0f};
};



#endif // !PHYSICS_H_
