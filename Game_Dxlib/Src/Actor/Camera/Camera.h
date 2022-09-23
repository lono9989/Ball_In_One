#ifndef CAMERA_H_
#define CAMERA_H_

#include "Actor/Actor.h"

#include "Mylib/Mylib.h"

// 三人称カメラクラス
class Camera : public Actor {
public :
    enum CamState{
        Ortho,  //正射影(シャドウマップ書き出し用)
        TPS,    //三人称視点
        FPS,    //一人称視点
    };
public:
    // コンストラクタ
    Camera(IWorld* world, const GSvector3& position, const GSvector3& at);
    // 更新
    virtual void update(float delta_time) override;
    // 描画
    virtual void draw() const override;

    void update_Tps(float delta_time, bool ball);

    void update_Fps(float delta_time);

    void ChangeMode(CamState state);

    static GSvector3 getForward();

private:
    GSvector3 rotate_{0.0f,0.0f,0.0f};
    // y軸周りの回転角度
    float yaw_{ 0.0f };
    // x軸周りの回転角度
    float pitch_{ 0.0f };
    // プレーヤーからの相対位置（z座標のみ）
    GSvector3 PlayerOffset{ 0.0f, 0.0f, 25.0f };
    
    CamState state_{CamState::TPS};
    CamState restate_{ CamState::TPS };
    float Fov_{60.0f};
    VECTOR pop_angle_{0.0f,0.0f,0.0f};
    static Camera* camera;
    static GSvector3 forward_;
};

#endif