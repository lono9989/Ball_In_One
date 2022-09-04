#ifndef START_SCENE_H_
#define START_SCENE_H_

#include "IScene.h"
#include "World/World.h"
//�Q�[���v���C�V�[��
class StartScene :public IScene {
public:
	//�ǂݍ���
	virtual void load()override;
	//�J�n
	virtual void start()override;
	//�X�V
	virtual void update(float delta_time)override;
	//�`��
	virtual void draw()const override;
	//�I�����Ă��邩�H
	virtual bool is_end()const override;
	//���̃V�[����Ԃ�
	virtual std::string next()const override;
	//�I��
	virtual void end()override;

private:
	float timer_;
	//�I���t���O
	bool is_end_{ false };
};


#endif	// !START_SCENE_H_