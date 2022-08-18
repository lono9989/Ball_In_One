#ifndef CAMERA_H_
#define CAMERA_H_

#include "Actor/Actor.h"

// �O�l�̃J�����N���X
class Camera : public Actor {
public :
    enum CamState{
        Ortho,  //���ˉe(�V���h�E�}�b�v�����o���p)
        TPS,    //�O�l�̎��_
        FPS,    //��l�̎��_
    };
public:
    // �R���X�g���N�^
    Camera(IWorld* world, const GSvector3& position, const GSvector3& at);
    // �X�V
    virtual void update(float delta_time) override;
    // �`��
    virtual void draw() const override;

    void update_Tps(float delta_time);

    void update_Fps(float delta_time);

    virtual void draw_shadowmap1(int a)override;
    virtual void draw_shadowmap2(int a)override;

    void ChangeMode(CamState state);

private:
    GSvector3 rotate_{0.0f,0.0f,0.0f};
    // y������̉�]�p�x
    float yaw_{ 0.0f };
    // x������̉�]�p�x
    float pitch_{ 0.0f };
    // �v���[���[����̑��Έʒu�iz���W�̂݁j
    GSvector3 PlayerOffset{ 0.0f, 0.0f, 25.0f };
    
    CamState state_{CamState::TPS};
    CamState restate_{ CamState::TPS };
    float Fov_{60.0f};
    VECTOR pop_angle_{0.0f,0.0f,0.0f};
    static Camera* camera;

};

#endif