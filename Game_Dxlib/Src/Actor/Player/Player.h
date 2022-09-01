#ifndef PLAYER_H_
#define PLAYER_H_

#include "Actor/Actor.h"
#include "Rendering/AnimatedMesh.h"

class Player :public Actor {
public:
	//���
	enum class State_ {
		Moving,
		//Running,
		Jumping,
	};

	//�R���X�g���N�^
	Player(IWorld* world = nullptr,int handle=-1, const GSvector3& position = GSvector3{ 0.0f,0.0f,0.0f });
	//�X�V
	virtual void update(float delta_time)override;
	//
	virtual void react(Actor& other)override;
	//�`��
	virtual void draw()const override;
	//�������`��
	virtual void draw_transparent()const override;

	// �t�B�[���h�Ƃ̏Փˏ���
	void Collide_Field();
	// �A�N�^�[�Ƃ̏Փˏ���
	void Collide_Actor(Actor& other);
private:

	void Update_state(float delta_time);

	//�ړ����
	void Move(float delta_time);
	//�W�����v��
	void Jump(float delta_time);

	void Change_state(State_ state, int motion,bool loop = true);
private:


	//�����蔻�茋�ʗp
	MV1_COLL_RESULT_POLY colres_;
	MV1_COLL_RESULT_POLY_DIM colresdim_;
	//�A�j���[�V�������b�V��
	AnimatedMesh mesh_;
	//���[�V�����ԍ�
	int motion_;
	//���[�V�������[�v
	bool motion_loop_;
	//�^�C�}
	float state_timer_;
	//���
	State_ state_;
};

#endif // !PLAYER_H_
