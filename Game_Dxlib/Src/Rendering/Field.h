#ifndef FIELD_H_
#define FIELD_H_

#include<DxLib.h>
#include"Mylib/Mylib.h"
#include "Collision/Line.h"
#include "Collision/Ray.h"
#include "Collision/BoundingSphere.h"

class Field {
public:
	//コンストラクタ
	Field(int model);
	//デストラクタ
	~Field();
	//更新
	void update(float delta_time);
	//描画
	void draw() const;
	void draw_shadow()const;
	// 線分との衝突判定
	bool collide(const Line& line, MV1_COLL_RESULT_POLY* result) const;
	// レイとの衝突判定
	bool collide(const Ray& ray, float max_distance, MV1_COLL_RESULT_POLY* result) const;
	// 球体との衝突判定
	bool collide(const BoundingSphere& sphere, MV1_COLL_RESULT_POLY_DIM* result,GSvector3* intersect) const;
	//フィールド内か
	bool is_inside(const GSvector3& position) const;
	//フィールド外か
	bool is_outside(const GSvector3& posiition) const;


	//コピー禁止
	Field(const Field& other) = default;
	Field& operator=(const Field& other) = default;

private:
	//背景画像
	GSuint bg_{ 0 };
	//スクロール位置
	float scroll_{ 0.0f };
	int field_Model{ -1 };
};

#endif;

