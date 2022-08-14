#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "Mylib/Mylib.h"
#include "DxLib.h"

class BoundingSphere;

//�ȈՕ������Z�N���X
class Physics {
public:
	//���̗p(���ɕK�v�Ȍ`���o�Ă����Ƃ��̓R���X�g���N�^��ʌI�[�o�[���[�h���Ă��������B)
	Physics(BoundingSphere* sphere,GStransform* transform,GSvector3 v = GSvector3{ 0.0f,0.0f,0.0f }, GSvector3 angv = GSvector3{ 0.0f,0.0f,0.0f });
	~Physics();

	void AddForce(GSvector3 power);


	//�ϐ��ݒ�A�擾�֐�
	GSvector3 GetVelocity();
	void SetVelocity(GSvector3 v);
	GSvector3 GetAngulerVelocity();
	void SetAngulerVelocity(GSvector3 v);
private:
	//�t�B�[���h�Ƃ̓����蔻��
	void CollideField();
private:
	//�g�����X�t�H�[���̃|�C���^�[(�{���������炱�����ɒu������)������̕ύX�ۑ�
	GStransform* transform_;
	//�R���C�_�[�̃|�C���^�[ ���������(�Ȃ񂾂�����܂Ƃ߂����̂���肽��)
	BoundingSphere* sphere_;
	//���x
	GSvector3 velocity_;
	//��]���x
	GSvector3 anguler_velocity_;

	bool freezePosition[3]{ false,false,false };
	bool freezeRotation[3]{ false,false,false };
};



#endif // !PHYSICS_H_
