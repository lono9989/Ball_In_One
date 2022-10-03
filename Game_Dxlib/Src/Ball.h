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
	Ball(IWorld* world = nullptr, const GSvector3& position = GSvector3{ 0.0f,0.0f,0.0f }, float bounciness = 0.7f);
	//更新
	virtual void update(float delta_time)override;
	//
	virtual void react(Actor& other)override;
	//描画
	virtual void draw()const override;

	void Start(float delta_time);
	void Shot(float delta_time);
	void Move(float delta_time);

	static bool getCanMoveCamera();

private:
	int color;

	int White = GetColor(255, 255, 255);
	int Block = GetColor(0, 0, 0);
	int Red = GetColor(255, 0, 0);
	int Green = GetColor(0, 255, 0);
	int Blue = GetColor(0, 0, 255);
	int Gray = GetColor(128, 128, 128);

	int rote{ 100 };
	int speed{ 1 };
	int count;
	GSvector3 Power;
	State state_;
	GSvector2 circlePos{ 110, 400 };
	static bool canMoveCamera;
};


#endif // !BALL_H_