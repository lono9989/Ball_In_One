#ifndef START_SCENE_H_
#define START_SCENE_H_

#include "IScene.h"
#include "World/World.h"
//ゲームプレイシーン
class StartScene :public IScene {
public:
	//読み込み
	virtual void load()override;
	//開始
	virtual void start()override;
	//更新
	virtual void update(float delta_time)override;
	//描画
	virtual void draw()const override;
	//終了しているか？
	virtual bool is_end()const override;
	//次のシーンを返す
	virtual std::string next()const override;
	//終了
	virtual void end()override;

private:
	float timer_;
	//終了フラグ
	bool is_end_{ false };
};


#endif	// !START_SCENE_H_