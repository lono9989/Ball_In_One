#include "Player.h"

#include "World/IWorld.h"
#include "Mylib/Mylib.h"
#include "Rendering/Field.h"
#include "Assets.h"

enum {
	AnimIdle = 0,
	AnimWalking = 1,
	AnimRunning = 2,
};

//�������x
const float WalkSpeed{ 23.0f };
//��]���x
const float RotateSpeed{ 12.0f };
// �����̍���
const float PlayerHeight{ 9.0f };
// �Փ˔���p�̔��a
const float PlayerRadius{ 2.0f };
// �����̃I�t�Z�b�g
const float FootOffset{ 0.5f };
// �d�͒l
const float Gravity{ -0.98f };
//����̔{��
const float Runningmagni{ 2.5f };


Player::Player(IWorld* world, int handle, const GSvector3& position) :
	mesh_{ handle,AnimIdle,true },
	motion_{ AnimIdle },
	motion_loop_{ true },
	state_{ State_::Moving }
{
	// ���[���h��ݒ�
	world_ = world;
	// �^�O���̐ݒ�
	tag_ = "PlayerTag";
	// ���O�̐ݒ�
	name_ = "Player";
	//�Փ˔��苅�̐ݒ�
	collider_ = BoundingSphere{ PlayerRadius,GSvector3{0.0f, PlayerHeight, 0.0f} };
	// ���W�̏�����
	transform_.position(position);
	// ���b�V���̕ϊ��s���������
	mesh_.TransForm(transform_.localToWorldMatrix());
}

void Player::update(float delta_time)
{
	Update_state(delta_time);

	// �d�͒l���X�V
	velocity_.y += Gravity * delta_time;
	// �d�͂�������
	transform_.translate(0.0f, velocity_.y, 0.0f);
	// �t�B�[���h�Ƃ̏Փ˔���
	Collide_Field();

	//���[�V�����ύX
	mesh_.Change_Motion(motion_, motion_loop_);
	//���b�V���̍X�V
	mesh_.Update(delta_time);
	//���b�V���̕ϊ��s��
	mesh_.TransForm(transform_.localToWorldMatrix());
}

void Player::react(Actor& other)
{
}

void Player::draw() const
{
	/*
	MV1SetUseOrigShader(TRUE);
	SetUseTextureToShader(1, Assets::Texture_GradPlayer);
	SetUseVertexShader(Assets::VShader_MMD);
	SetUsePixelShader(Assets::PShader_MMD);
	MV1SetUseOrigShader(FALSE);
	*/

	//mesh_.Draw();
	collider().draw();
}

void Player::draw_transparent() const
{
	//mesh_.Trans_Draw();
}

void Player::draw_shadowmap1() const
{
	mesh_.Draw();
}

void Player::Collide_Field()
{
	// �ǂƂ̏Փ˔���i���̂Ƃ̔���j
	GSvector3 inter; // �Փˌ�̋��̂̒��S���W
	if(world_->field()->collide(collider(),&colresdim_,&inter)) {
		// y���W�͕ύX���Ȃ�
		inter.y = transform_.position().y;
		// �␳��̍��W�ɕύX����
		transform_.position(inter);
		MV1CollResultPolyDimTerminate(colresdim_);

	}
	// �n�ʂƂ̏Փ˔���i�����Ƃ̌�������j
	GSvector3 position = transform_.position();
	Line line;
	line.start = position + collider_.center;
	line.end = position + GSvector3{ 0.0f, -FootOffset, 0.0f };
	GSvector3 intersect;  // �n�ʂƂ̌�_
	if (world_->field()->collide(line,&colres_)) {
		// ��_�̈ʒu����y���W�̂ݕ␳����
		position.y = colres_.HitPosition.y;
		// ���W��ύX����
		transform_.position(position);
		// �d�͂�����������
		velocity_.y = 0.0f;
	}
}

void Player::Collide_Actor(Actor& other)
{
}

void Player::Update_state(float delta_time)
{
	//�ړ�����
	switch (state_)
	{
	case Player::State_::Moving:
		Move(delta_time);
		break;
	case Player::State_::Jumping:
		Jump(delta_time);
		break;
	default:
		break;
	}
	//��ԃ^�C�}�̍X�V
	state_timer_ += delta_time;
}

void Player::Move(float delta_time)
{
	// �J�����̑O�����x�N�g�����擾
	GSvector3 forward = world_->camera()->transform().forward();
	forward.y = 0.0f;
	forward = forward.normalized();
	// �J�����̉E�����x�N�g�����擾
	GSvector3 right = world_->camera()->transform().right();
	right.y = 0.0f;
	right = right.normalized();
	// �L�[�̓��͒l����ړ��x�N�g�����v�Z
	GSvector3 velocity{ 0.0f, 0.0f, 0.0f };



	if (InputManager::GetInput(InputType::KEY,KEY_INPUT_W))velocity += forward;      // �O�i
	if (InputManager::GetInput(InputType::KEY, KEY_INPUT_S))velocity -= forward;      // ���
	if (InputManager::GetInput(InputType::KEY, KEY_INPUT_A)) velocity += right;       // ��
	if (InputManager::GetInput(InputType::KEY, KEY_INPUT_D)) velocity -= right;       // �E
	velocity = velocity.normalized() * WalkSpeed * delta_time;

	// �������Ȃ���΃A�C�h�����
	int motion{ AnimIdle };
	// �ړ����Ă��邩�H
	if (velocity.length() != 0.0f) {
		// �����̕��
		GSquaternion  rotation =
			GSquaternion::rotateTowards(
				transform_.rotation(),
				GSquaternion::lookRotation(-velocity), RotateSpeed * delta_time * 60.0f);
		transform_.rotation(rotation);
		// �ړ����̃��[�V�����ɂ���
		motion = AnimWalking;
		if (InputManager::GetInput(InputType::KEY, KEY_INPUT_LSHIFT)) {
			velocity*= Runningmagni;
			motion = AnimRunning;
		}
	}
	// ���[�V�����̕ύX
	Change_state(State_::Moving, motion);

	// �ړ��ʂ�xz���������X�V
	velocity_.x = velocity.x;
	velocity_.z = velocity.z;
	// ���s�ړ�����i���[���h��j
	transform_.translate(velocity_, GStransform::Space::World);


}

void Player::Jump(float delta_time)
{
}

void Player::Change_state(State_ state,int motion, bool loop)
{
	motion_ = motion;
	motion_loop_ = loop;
	state_ = state;
	state_timer_ = 0.0f;
	
}
