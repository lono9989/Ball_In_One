#ifndef ANIMATED_MESH_H_
#define ANIMATED_MESH_H_

#include "DxLib.h"
#include "Mylib/Mylib.h"

class AnimatedMesh {
public:
	//�R���X�g���N�^
	AnimatedMesh(int pass, int motion = 0, bool loop = true, int AnimSrcMHandle=-1, int NameCheck=TRUE);
	//�X�V
	void Update(float delta_time);
	//�`��
	void Draw()const;
	//�������̕`��
	void Trans_Draw()const;
	//���[�V�����̐؂�ւ�
	void Change_Motion(int motion, bool loop = true, int AnimSrcMHandle_=-1, int NameCheck_=TRUE);
	//�g�����X�t�H�[��
	void TransForm(const GSmatrix4& matrix);
	//���[�V�������I����Ă��邩
	bool Is_End_Motion()const;
	//���[�V�����̎��Ԃ��擾
	float Motion_Time()const;
	//���[�V�����̎��Ԃ�ݒ�
	void Motion_Time(float time);
	//���[�V�����̑��Đ����Ԃ��擾
	float Motion_End_Time()const;
	//�u�����h
	void blend(int nowanim, int recentanim, float rate);
private:
	//���f��ID
	int pass_;
	// �A�Z�b�gID
	int motion_;
	// ���[�V�����ԍ�
	int attachanim_;
	//���[�V�����̊��蓖�Ă��Ă��郂�f���̃n���h��
	int AnimSrcMHandle_;
	//�t���[���̖��O���Ⴄ�ꍇ�ɃA�^�b�`���邩
	int NameCheck_;
	// ���[�V�����^�C�}
	float motion_timer_;
	// ���[�V�������[�v�t���O
	bool motion_loop_;
	// �ϊ��s��
	GSmatrix4 transform_;
	// �O��Đ��������[�V�����ԍ�
	int      prev_motion_;
	// �O��Đ������ŏI�A�j���[�V�����^�C�}
	float     prev_motion_timer_;
	// ��ԃ^�C�}
	float     lerp_timer_;
	//�A�j���[�V�����̃u�����h��
	float blendrate{ 0.0f };
	//�u�����h��	
	bool blending{ false };
};

#endif // !ANIMATED_MESH_H_
