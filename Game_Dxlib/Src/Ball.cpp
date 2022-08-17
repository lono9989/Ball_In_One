#include "Ball.h"

Ball::Ball(IWorld* world, const GSvector3& position)
{
	// ���[���h��ݒ�
	world_ = world;
	// �^�O���̐ݒ�
	tag_ = "BallTag";
	// ���O�̐ݒ�
	name_ = "Ball";
	//�Փ˔��苅�̐ݒ�
	collider_ = BoundingSphere{ 1.0f,GSvector3{0.0f,0.0f,0.0f} };
	// ���W�̏�����
	transform_.position(position);
	physics_ = Physics{ world_,&collider_,&transform_ };
}

void Ball::update(float delta_time)
{
	physics_.Update(delta_time);
}

void Ball::react(Actor& other)
{
}

void Ball::draw() const
{
	collider().draw();
}
