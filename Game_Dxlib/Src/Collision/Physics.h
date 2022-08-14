#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "Mylib/Mylib.h"
#include "DxLib.h"

class BoundingSphere;

//簡易物理演算クラス
class Physics {
public:
	//球体用(他に必要な形が出てきたときはコンストラクタを別個オーバーロードしてください。)
	Physics(BoundingSphere* sphere,GStransform* transform,GSvector3 v = GSvector3{ 0.0f,0.0f,0.0f }, GSvector3 angv = GSvector3{ 0.0f,0.0f,0.0f });
	~Physics();

	void AddForce(GSvector3 power);


	//変数設定、取得関数
	GSvector3 GetVelocity();
	void SetVelocity(GSvector3 v);
	GSvector3 GetAngulerVelocity();
	void SetAngulerVelocity(GSvector3 v);
private:
	//フィールドとの当たり判定
	void CollideField();
private:
	//トランスフォームのポインター(本当だったらこっちに置きたい)←今後の変更課題
	GStransform* transform_;
	//コライダーのポインター これも同上(なんだったらまとめれるものを作りたい)
	BoundingSphere* sphere_;
	//速度
	GSvector3 velocity_;
	//回転速度
	GSvector3 anguler_velocity_;

	bool freezePosition[3]{ false,false,false };
	bool freezeRotation[3]{ false,false,false };
};



#endif // !PHYSICS_H_
