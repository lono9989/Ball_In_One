#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "Mylib/Mylib.h"
#include "DxLib.h"
#include "World/IWorld.h"

class BoundingSphere;

//簡易物理演算クラス
class Physics {
public:
	Physics();
	//球体用(他に必要な形が出てきたときはコンストラクタを別個オーバーロードしてください。)
	Physics(IWorld* world, BoundingSphere* sphere, GStransform* transform, GSvector3 v = GSvector3{ 0.0f,0.0f,0.0f }, GSvector3 angv = GSvector3{ 0.0f,0.0f,0.0f });
	~Physics();

	void Update(float delta_time);

	//力を加える
	void AddForce(GSvector3 power);


	//変数設定、取得関数
	GSvector3 GetVelocity();
	void SetVelocity(GSvector3 v);
	GSvector3 GetAngulerVelocity();
	void SetAngulerVelocity(GSvector3 v);
	float GetBounciness();
	void SetBounciness(float bounce);
	/*float GetMass();
	void SetMass(float mass);*/
private:
	//フィールドとの当たり判定
	void CollideField();
private:
	IWorld* world_{ nullptr };
	//トランスフォーム
	GStransform* transform_{nullptr};
	//コライダーのポインター (なんだったらまとめれるものを作りたい)
	BoundingSphere* sphere_{ nullptr };
	//速度
	GSvector3 velocity_;
	//回転速度
	GSvector3 anguler_velocity_;

	//反発係数
	float bounciness_{0.0f};

	//まだ反映させてない
	bool freezePosition[3]{ false,false,false };
	bool freezeRotation[3]{ false,false,false };
	////質量 
	//float mass_{1.0f};
};



#endif // !PHYSICS_H_
