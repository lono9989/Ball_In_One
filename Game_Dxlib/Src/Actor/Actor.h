#ifndef ACTOR_H_
#define ACTOR_H_

#include <Dxlib.h>
#include"Mylib/Mylib.h"
#include<string>
#include"Collision/BoundingSphere.h"
#include "Collision/Physics.h"

#include "Mylib/Tween/Tween.h"

class IWorld; //ワールド抽象インターフェイスの前方宣言

//アクタークラス
class Actor {
public:
	//コンストラクタ
	Actor() = default;
	//仮想デストラクタ
	virtual ~Actor() = default;
	//更新
	virtual void update(float delta_time);
	//遅延更新
	virtual void late_update(float delta_time);
	//描画
	virtual void draw()const;
	//半透明の描画
	virtual void draw_transparent()const;
	//GUIの描画
	virtual void draw_gui()const;


	//衝突リアクション
	virtual void react(Actor& other);
	//メッセージ処理
	virtual void handle_message(const std::string& message, void* param);
	//衝突判定
	void collide(Actor& other);
	//死亡する
	void die();
	//衝突しているか？
	bool is_collider(const Actor& other)const;
	//死亡しているか？
	bool is_dead()const;
	//名前を所得
	const std::string& name()const;
	//タグ名を所得
	const std::string& tag()const;
	//
	const void setViewActorName(std::string viewActorName);
	//タグ名を所得
	const std::string& view_actor_name()const;
	//トランスフォームを所得(const版)
	const GStransform& transform()const;
	//トランスフォームを所得
	GStransform& transform();
	//移動量を所得
	GSvector3 velocity()const;
	//衝突判定データを所得
	BoundingSphere collider()const;
	// 指定された場所までTweenで移動する
	TweenUnit& move_to(const GSvector3& to, float duration);

	//コピー禁止
	Actor(const Actor& other) = delete;
	Actor& operator=(const Actor& other) = delete;

protected:
	//ワールド
	IWorld* world_{ nullptr };
	//タグ名
	std::string tag_;
	//名前
	std::string name_;

	//ennzann
	Physics physics_;
	//トランスフォーム
	GStransform transform_;
	//移動量
	GSvector3 velocity_{ 0.f,0.f,0.f };
	//衝突判定が有効か？
	bool enable_collider_{ true };
	//衝突判定
	BoundingSphere collider_;
	//死亡フラグ
	bool dead_{ false };

	static std::string view_actor_name_;
};

enum class CamState {
	Ortho,  //正射影(シャドウマップ書き出し用)
	TPS,    //三人称視点
	FPS,    //一人称視点
};
struct CameraOptionData
{
public :
	float Near;
	float Far;
	float FOV;
	bool Perspective;
	float Size;
};

#endif // !ACTOR_H_

