#ifndef LIGHT_H_
#define LIGHT_H_

#include "Actor/Actor.h"
#include <unordered_map>

// 標準ライトクラス
class Light : public Actor {
public:
    // コンストラクタ
    Light(IWorld* world, const GSvector3& position = GSvector3{100.0f,100.0f,100.0f},
        const COLOR_F& amb = GetColorF(0.4f, 0.4f, 0.4f, 1.0f),
        const COLOR_F& dif = GetColorF(1.0f, 1.0f, 1.0f, 1.0f),
        const COLOR_F& spc = GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
    // 描画
    virtual void draw() const override;

};

#endif