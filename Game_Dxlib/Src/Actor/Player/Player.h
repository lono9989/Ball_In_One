#ifndef PLAYER_H_
#define PLAYER_H_

#include "Actor/Actor.h"
#include "Rendering/AnimatedMesh.h"

class Player :public Actor {
public:
	//状態
	enum class State_ {
		Moving,
		//Running,
		Jumping,
	};

	//コンストラクタ
	Player(IWorld* world = nullptr,int handle=-1, const GSvector3& position = GSvector3{ 0.0f,0.0f,0.0f });
	//更新
	virtual void update(float delta_time)override;
	//
	virtual void react(Actor& other)override;
	//描画
	virtual void draw()const override;
	//半透明描画
	virtual void draw_transparent()const override;

	// フィールドとの衝突処理
	void Collide_Field();
	// アクターとの衝突処理
	void Collide_Actor(Actor& other);
private:

	void Update_state(float delta_time);

	//移動状態
	void Move(float delta_time);
	//ジャンプ中
	void Jump(float delta_time);

	void Change_state(State_ state, int motion,bool loop = true);
private:


	//当たり判定結果用
	MV1_COLL_RESULT_POLY colres_;
	MV1_COLL_RESULT_POLY_DIM colresdim_;
	//アニメーションメッシュ
	AnimatedMesh mesh_;
	//モーション番号
	int motion_;
	//モーションループ
	bool motion_loop_;
	//タイマ
	float state_timer_;
	//状態
	State_ state_;
};

#endif // !PLAYER_H_
