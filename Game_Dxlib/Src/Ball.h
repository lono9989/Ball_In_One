#ifndef BALL_H_
#define BALL_H_

#include "Actor/Actor.h"

class Ball :public Actor {
public:
	enum class State {
		Start,
		Shot,
		Move,
	};
public:
	//コンストラクタ
	Ball(IWorld* world = nullptr, const GSvector3& position = GSvector3{ 0.0f,0.0f,0.0f },float bounciness=0.7f);
	//更新
	virtual void update(float delta_time)override;
	//
	virtual void react(Actor& other)override;
	//描画
	virtual void draw()const override;

	void Start(float delta_time);
	void Shot(float delta_time);
	void Move(float delta_time);

	static bool getCamera();

private:
	int color;

	int rote;
	int speed;

	GSvector3 Power;

	State state_;
	int count;
	static bool camera;
};


#endif // !BALL_H_
