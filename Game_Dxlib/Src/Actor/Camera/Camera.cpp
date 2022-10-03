#include "Camera.h"
#include "DxLib.h"
#include "Rendering/Screen.h"
#include "World/IWorld.h"
#include "Collision/Line.h"
#include "Rendering/Field.h"
#include "Mylib/Dxlib_Input/MouseInput.h"
#include "Ball.h"

#include <string>


// �J�����̒����_�̕␳�l
const GSvector3 ReferencePointOffset{ 0.0f, 11.0f, 0.0f };
const GSvector3 ReferenceBallPointOffset{ 0.0f, 3.0f, 0.0f };

const float RotateSpeed{ 50.0f };
const float ZoomSpeed{ 2.0f };

Camera* Camera::camera{ nullptr };
GSvector3 Camera::forward_{ 0,0,0 };

Camera::Camera(IWorld* world, const GSvector3& position, const GSvector3& at)
{
	camera = this;
	// ���[���h��ݒ�
	world_ = world;
	// �^�O�̐ݒ�
	tag_ = "CamaraTag";
	// ���O�̐ݒ�
	name_ = "Camera";
	// ���_�̈ʒu��ݒ�
	transform_.position(position);
	// �����_��ݒ�
	transform_.lookAt(at);
	// ��������̉�]�p�x�̏�����
	pitch_ = 0.0f;
	// ��������̉�]�p�x�̏�����
	yaw_ = (at - position).getYaw();
	MouseInput::GetMouseDif_and_SetPos(Screen::Width / 2, Screen::Height / 2);
	SetupCamera_Perspective(DEG_TO_RAD(Fov_));

	Actor::setViewActorName("Player");
}

void Camera::update(float delta_time)
{
	switch (state_)
	{
	case CamState::Ortho:
		break;
	case CamState::TPS:
		update_Tps(delta_time);
		break;
	case CamState::FPS:
		update_Fps(delta_time);
		break;
	default:
		break;
	}
}

void Camera::draw() const
{
	// ���_�̈ʒu
	GSvector3 eye = transform_.position();
	// �����_�̈ʒu
	GSvector3 at = eye + transform_.forward();
	// ���_�̏����
	GSvector3 up = transform_.up();

	SetCameraPositionAndTargetAndUpVec(eye.VECTOR_, at.VECTOR_, up.VECTOR_);
}

void Camera::update_Tps(float delta_time)
{
	// �v���[���[������
	Actor* actor = world_->find_actor(view_actor_name_);

	if (actor == nullptr) return;
	VECTOR vec = MouseInput::GetMouseDif_and_SetPos(Screen::Width / 2, Screen::Height / 2);

	if (Ball::getCanMoveCamera()) {
		// y���܂��ɃJ��������]������
		yaw_ += vec.x * RotateSpeed * delta_time;
		// x���܂��ɃJ��������]������
		pitch_ -= vec.y * RotateSpeed * delta_time;
		// x���܂��̉�]�p�x�̐���������
		pitch_ = CLAMP(pitch_, -75.0f, 85.0f);

		PlayerOffset.z -= ZoomSpeed * GetMouseWheelRotVolF();
		PlayerOffset.z = CLAMP(PlayerOffset.z, 5.0f, 40.0f);
		if (PlayerOffset.z < 10.0f) {
			pitch_ = CLAMP(pitch_, -75.0f, 85.0f - (10.0f - PlayerOffset.z) * 5.0f);
		}
	}
	//�����_�̍��W�����߂�
	GSvector3 at = actor->transform().position() + (view_actor_name_ != "Ball" ? ReferencePointOffset : ReferenceBallPointOffset);
	// �J�����̍��W�����߂�
	GSvector3 position = at + GSquaternion::euler(pitch_, yaw_, 0.0f) * PlayerOffset;

	// �t�B�[���h�Ƃ̏Փ˔���
	Line line{ at, position };
	MV1_COLL_RESULT_POLY res;
	if (world_->field()->collide(line, &res)) {
		position.VECTOR_ = VAdd(res.HitPosition, VScale(VNorm(VSub(res.HitPosition, position.VECTOR_)), 0.8f));
	}

	forward_ = transform_.forward();

	// ���W�̐ݒ�
	transform_.position(position);
	// �����_�̕���������
	transform_.lookAt(at);
}

void Camera::update_Fps(float delta_time)
{
}


void Camera::ChangeMode(CamState state)
{
	state_ = state;
}

GSvector3 Camera::getForward() {
	return forward_;
}
