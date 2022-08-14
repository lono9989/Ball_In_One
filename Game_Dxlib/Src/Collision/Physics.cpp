#include "Collision/Physics.h"
#include "Collision/BoundingSphere.h"

//èdóÕâ¡ë¨ìx
const float Gravity{ 9.80665f };


Physics::Physics(BoundingSphere* sphere, GStransform* transform, GSvector3 v, GSvector3 angv) :
	sphere_{ sphere }, transform_{transform},
	velocity_{ v }, anguler_velocity_{ angv }
{
}

Physics::~Physics()
{
}

void Physics::AddForce(GSvector3 power)
{
}

GSvector3 Physics::GetVelocity()
{
	return velocity_;
}

void Physics::SetVelocity(GSvector3 v)
{
	velocity_ = v;
}

GSvector3 Physics::GetAngulerVelocity()
{
	return anguler_velocity_;
}

void Physics::SetAngulerVelocity(GSvector3 v)
{
	anguler_velocity_ = v;
}

void Physics::CollideField()
{
	//Ç±Ç±Ç…Ç¢ÇÎÇ¢ÇÎèëÇ≠
}
