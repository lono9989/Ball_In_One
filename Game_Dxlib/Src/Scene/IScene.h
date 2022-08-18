#ifndef ISCENE_H_
#define ISCENE_H_

#include<string>

// �V�[�����ۃC���^�[�t�F�[�X
class IScene {
public:
	// ���z�f�X�g���N�^
	virtual ~IScene() = default;
	//�ǂݍ���
	virtual void load() = 0;
	// �J�n
	virtual void start() = 0;
	// �X�V
	virtual void update(float delta_time) = 0;
	// �`��
	virtual void draw()const = 0;
	//�V���h�E�}�b�v�̍X�V�p
	virtual void draw_shadow() = 0;
	// �I�����Ă��邩�H
	virtual bool is_end()const = 0;
	// ���̃V�[������Ԃ�
	virtual std::string next()const = 0;
	// �I��
	virtual void end() = 0;

public:
	float timer_{ 0 };
};

#endif