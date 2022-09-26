#ifndef ORTHOCAMERA_H_
#define ORTHOCAMERA_H_

#include "Actor/Actor.h"
#include "Mylib/Mylib.h"

class OrthoCamera:public Actor
{
public:
    // コンストラクタ
    OrthoCamera(IWorld* world, const GSvector3& position, const GSvector3& at);
    // 更新
    virtual void update(float delta_time) override;
    // 描画
    virtual void draw() const override;
};

#endif // !ORTHOCAMERA_H_