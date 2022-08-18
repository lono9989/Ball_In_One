#pragma once

#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

#include"IScene.h"

//�^�C�g���V�[��
class TitleScene :public IScene {
public:
	//�ǂݍ���
	virtual void load()override;
	//�J�n
	virtual void start()override;
	//�X�V
	virtual void update(float delta_time)override;
	//�`��
	virtual void draw()const override;
	//
	virtual void draw_shadow()override;
	//�I�����Ă��邩�H
	virtual bool is_end()const override;
	//���̃V�[����Ԃ�
	virtual std::string next()const override;
	//�I��
	virtual void end()override;

private:
	//�I���t���O
	bool is_end_{ false };
};

#endif // !TITLE_SCENE_H_
