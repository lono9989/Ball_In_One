#include "Ball.h"

#include "Mylib/Debug.h"

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
	physics_.SetBounciness(0.7f);
}

void Ball::update(float delta_time)
{
	physics_.Update(delta_time);
	if (InputManager::GetInputDown(InputType::KEY, KEY_INPUT_G)) {
		physics_.AddForce(GSvector3{ 0.5f,-0.5f,0.0f });
	}
}

void Ball::react(Actor& other)
{
}

void Ball::draw() const
{
	Debug::DrawCoordinateAxis(transform_);
	collider().draw();
	std::string str = std::to_string(transform_.position().x) + "," + std::to_string(transform_.position().y) + "," + std::to_string(transform_.position().z);
	DrawString(80, 245, str.c_str(), GetColor(255, 255, 255));
}
