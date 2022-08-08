#ifndef LIGHT_H_
#define LIGHT_H_

#include "Actor/Actor.h"
#include <unordered_map>

// �W�����C�g�N���X
class Light : public Actor {
public:
    // �R���X�g���N�^
    Light(IWorld* world, const GSvector3& position = GSvector3{100.0f,100.0f,100.0f},
        const COLOR_F& amb = GetColorF(0.4f, 0.4f, 0.4f, 1.0f),
        const COLOR_F& dif = GetColorF(1.0f, 1.0f, 1.0f, 1.0f),
        const COLOR_F& spc = GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
    // �`��
    virtual void draw() const override;

};

#endif