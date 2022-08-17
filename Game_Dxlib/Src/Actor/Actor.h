#ifndef ACTOR_H_
#define ACTOR_H_

#include <Dxlib.h>
#include"Mylib/Mylib.h"
#include<string>
#include"Collision/BoundingSphere.h"
#include "Collision/Physics.h"

class IWorld; //���[���h���ۃC���^�[�t�F�C�X�̑O���錾

//�A�N�^�[�N���X
class Actor {
public:
	//�R���X�g���N�^
	Actor() = default;
	//���z�f�X�g���N�^
	virtual ~Actor() = default;
	//�X�V
	virtual void update(float delta_time);
	//�x���X�V
	virtual void late_update(float delta_time);
	//�`��
	virtual void draw()const;
	//�������̕`��
	virtual void draw_transparent()const;
	//GUI�̕`��
	virtual void draw_gui()const;
	//�V���h�E�}�b�v�`��p
	virtual void draw_shadowmap1()const;
	virtual void draw_shadowmap1(int a);
	virtual void draw_shadowmap2()const;
	virtual void draw_shadowmap2(int a);
	virtual void draw_shadowmap3()const;
	virtual void draw_shadowmap3(int a);


	//�Փ˃��A�N�V����
	virtual void react(Actor& other);
	//���b�Z�[�W����
	virtual void handle_message(const std::string& message, void* param);
	//�Փ˔���
	void collide(Actor& other);
	//���S����
	void die();
	//�Փ˂��Ă��邩�H
	bool is_collider(const Actor& other)const;
	//���S���Ă��邩�H
	bool is_dead()const;
	//���O������
	const std::string& name()const;
	//�^�O��������
	const std::string& tag()const;
	//�g�����X�t�H�[��������(const��)
	const GStransform& transform()const;
	//�g�����X�t�H�[��������
	GStransform& transform();
	//�ړ��ʂ�����
	GSvector3 velocity()const;
	//�Փ˔���f�[�^������
	BoundingSphere collider()const;

	//�R�s�[�֎~
	Actor(const Actor& other) = delete;
	Actor& operator=(const Actor& other) = delete;

protected:
	//���[���h
	IWorld* world_{ nullptr };
	//�^�O��
	std::string tag_;
	//���O
	std::string name_;

	//ennzann
	Physics physics_;
	//�g�����X�t�H�[��
	GStransform transform_;
	//�ړ���
	GSvector3 velocity_{ 0.f,0.f,0.f };
	//�Փ˔��肪�L�����H
	bool enable_collider_{ true };
	//�Փ˔���
	BoundingSphere collider_;
	//���S�t���O
	bool dead_{ false };
};

#endif // !ACTOR_H_

