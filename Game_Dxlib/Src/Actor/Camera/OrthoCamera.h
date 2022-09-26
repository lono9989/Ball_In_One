#ifndef ORTHOCAMERA_H_
#define ORTHOCAMERA_H_

#include "Actor/Actor.h"
#include "Mylib/Mylib.h"

class OrthoCamera:public Actor
{
public:
    // �R���X�g���N�^
    OrthoCamera(IWorld* world, const GSvector3& position, const GSvector3& at);
    // �X�V
    virtual void update(float delta_time) override;
    // �`��
    virtual void draw() const override;
};

#endif // !ORTHOCAMERA_H_