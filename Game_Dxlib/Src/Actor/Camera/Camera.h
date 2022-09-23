#ifndef CAMERA_H_
#define CAMERA_H_

#include "Actor/Actor.h"

#include "Mylib/Mylib.h"

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

    void update_Tps(float delta_time, bool ball);

    void update_Fps(float delta_time);

    void ChangeMode(CamState state);

    static GSvector3 getForward();

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
    static GSvector3 forward_;
};

#endif