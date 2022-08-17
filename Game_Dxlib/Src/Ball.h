#ifndef BALL_H_
#define BALL_H_

#include "Actor/Actor.h"

class Ball :public Actor {
public:
	//コンストラクタ
	Ball(IWorld* world = nullptr, const GSvector3& position = GSvector3{ 0.0f,0.0f,0.0f });
	//更新
	virtual void update(float delta_time)override;
	//
	virtual void react(Actor& other)override;
	//描画
	virtual void draw()const override;
};


#endif // !BALL_H_
