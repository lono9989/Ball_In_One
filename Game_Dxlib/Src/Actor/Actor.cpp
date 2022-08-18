#include"Actor.h"

//�X�V
void Actor::update(float) {};

//�x���X�V
void Actor::late_update(float) {};

//�`��
void Actor::draw()const {};

//�������I�u�W�F�N�g�̕`��
void Actor::draw_transparent()const {};

//GUI�̕`��
void Actor::draw_gui()const {};
//�V���h�E�}�b�v�`��p
void Actor::draw_shadowmap1() const {}
void Actor::draw_shadowmap1(int a) {};
void Actor::draw_shadowmap2() const {}
void Actor::draw_shadowmap2(int a) {};
void Actor::draw_shadowmap3() const {};
void Actor::draw_shadowmap3(int a){};

//�Փ˃��A�N�V����
void Actor::react(Actor&) {};

//���b�Z�[�W����
void Actor::handle_message(const std::string& message, void* param) {};

//�Փ˔���
void Actor::collide(Actor& other) {
	//�ǂ���̃A�N�^�[���Փ˔��肪�L�����H
	if (enable_collider_ && other.enable_collider_) {
		//�Փ˔��������
		if (is_collider(other)) {
			//�Փ˂����ꍇ�́A���݂��ɏՓ˔��������
			react(other);
			other.react(*this);
		}
	}
}

//���S����
void Actor::die() {
	dead_ = true;
}

//�Փ˂��Ă��邩�H
bool Actor::is_collider(const Actor& other)const {
	return collider().intersects(other.collider());
}

//���S���Ă��邩
bool Actor::is_dead()const {
	return dead_;
}

//���O�̏���
const std::string& Actor::name()const {
	return name_;
}

//�^�O��������
const std::string& Actor::tag()const {
	return tag_;
}

//�g�����X�t�H�[��������(const��)
const GStransform& Actor::transform()const {
	return transform_;
}

//�g�����X�t�H�[��������
GStransform& Actor::transform() {
	return transform_;
}

//�ړ��ʂ�����
GSvector3 Actor::velocity()const {
	return velocity_;
}

//�Փ˔���f�[�^������
BoundingSphere Actor::collider()const {
	return collider_.transform(transform_.localToWorldMatrix());
}