#include "AnimatedMesh.h"

const float LerpTime{ 10.0f };

AnimatedMesh::AnimatedMesh(int pass, int motion, bool loop, int AnimSrcMHandle, int NameCheck) :
	pass_{ pass },
	motion_{ motion },
	attachanim_{ -1 },
	motion_timer_{ 0.0f },
	motion_loop_{ loop },
	transform_{ GS_MATRIX4_IDENTITY },
	prev_motion_{ -1 },
	prev_motion_timer_{ 0.0f },
	lerp_timer_{ 0.0f },
	AnimSrcMHandle_{ AnimSrcMHandle },
	NameCheck_{ NameCheck }
{
	attachanim_ = MV1AttachAnim(pass_, motion_, AnimSrcMHandle_, NameCheck_);
}

void AnimatedMesh::Update(float delta_time)
{
	// モーションタイマの更新
	motion_timer_ += delta_time * 40.0f;
	// ループアニメーションか？
	if (motion_loop_) {
		// モーションタイマをループさせる
		motion_timer_ = std::fmod(motion_timer_, Motion_End_Time());
	}
	else {
		// モーションタイマをクランプする
		motion_timer_ = std::min(motion_timer_, Motion_End_Time());
	}


	//アニメーションブレンド
	if (blendrate < 1.0f) {
		blending = true;
		blendrate += 8 * delta_time;
	}
	else
	{
		blending = false;
		blendrate = 1.0f;
	}
	MV1SetAttachAnimTime(pass_, attachanim_, motion_timer_);
	blend(attachanim_, prev_motion_, blendrate);

}

void AnimatedMesh::Draw() const
{

	MV1SetPosition(pass_, transform_.position().VECTOR_);
	MV1SetRotationMatrix(pass_, transform_.MATRIX_);
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_NOT_SEMITRANS_ONLY);
	MV1DrawModel(pass_);
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_ALWAYS);
}

void AnimatedMesh::Trans_Draw() const
{
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_SEMITRANS_ONLY);
	MV1DrawModel(pass_);
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_ALWAYS);
}

void AnimatedMesh::Change_Motion(int motion, bool loop, int AnimSrcMHandle_, int NameCheck_)
{
	if (motion_ == motion)return;
	MV1DetachAnim(pass_, prev_motion_);
	prev_motion_ = attachanim_;
	motion_ = motion;
	motion_timer_ = 0.0f;
	motion_loop_ = loop;
	blendrate = 0.0f;
	blending = false;
	attachanim_ = MV1AttachAnim(pass_, motion_, AnimSrcMHandle_, NameCheck_);
}

void AnimatedMesh::TransForm(const GSmatrix4& matrix)
{
	transform_ = matrix;
}

bool AnimatedMesh::Is_End_Motion() const
{
	if (motion_loop_)return false;
	return motion_timer_ >= Motion_End_Time();
}

float AnimatedMesh::Motion_Time() const
{
	return motion_timer_;
}

void AnimatedMesh::Motion_Time(float time)
{
	motion_timer_ = time;
}

float AnimatedMesh::Motion_End_Time() const
{
	return MV1GetAttachAnimTotalTime(pass_, attachanim_);
}
//ブレンド値設定
void AnimatedMesh::blend(int nowanim, int recentanim, float rate) {
	MV1SetAttachAnimBlendRate(pass_, recentanim, 1.0f - rate);
	MV1SetAttachAnimBlendRate(pass_, nowanim, rate);
}