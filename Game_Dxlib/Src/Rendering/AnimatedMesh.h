#ifndef ANIMATED_MESH_H_
#define ANIMATED_MESH_H_

#include "DxLib.h"
#include "Mylib/Mylib.h"

class AnimatedMesh {
public:
	//コンストラクタ
	AnimatedMesh(int pass, int motion = 0, bool loop = true, int AnimSrcMHandle=-1, int NameCheck=TRUE);
	//更新
	void Update(float delta_time);
	//描画
	void Draw()const;
	//半透明の描画
	void Trans_Draw()const;
	//モーションの切り替え
	void Change_Motion(int motion, bool loop = true, int AnimSrcMHandle_=-1, int NameCheck_=TRUE);
	//トランスフォーム
	void TransForm(const GSmatrix4& matrix);
	//モーションが終わっているか
	bool Is_End_Motion()const;
	//モーションの時間を取得
	float Motion_Time()const;
	//モーションの時間を設定
	void Motion_Time(float time);
	//モーションの総再生時間を取得
	float Motion_End_Time()const;
	//ブレンド
	void blend(int nowanim, int recentanim, float rate);
private:
	//モデルID
	int pass_;
	// アセットID
	int motion_;
	// モーション番号
	int attachanim_;
	//モーションの割り当てられているモデルのハンドル
	int AnimSrcMHandle_;
	//フレームの名前が違う場合にアタッチするか
	int NameCheck_;
	// モーションタイマ
	float motion_timer_;
	// モーションループフラグ
	bool motion_loop_;
	// 変換行列
	GSmatrix4 transform_;
	// 前回再生したモーション番号
	int      prev_motion_;
	// 前回再生した最終アニメーションタイマ
	float     prev_motion_timer_;
	// 補間タイマ
	float     lerp_timer_;
	//アニメーションのブレンド率
	float blendrate{ 0.0f };
	//ブレンド中	
	bool blending{ false };
};

#endif // !ANIMATED_MESH_H_
