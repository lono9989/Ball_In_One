#ifndef BALL_H_
#define BALL_H_

#include "Actor/Actor.h"

class Ball :public Actor {
public:
	//コンストラクタ
	Ball(IWorld* world = nullptr, const GSvector3& position = GSvector3{ 0.0f,0.0f,0.0f },float bounciness=0.7f);
	//更新
	virtual void update(float delta_time)override;
	//
	virtual void react(Actor& other)override;
	//描画
	virtual void draw()const override;

private:
	int color;

	int rote;
	int speed;

	GSvector3 Power;
};


#endif // !BALL_H_
