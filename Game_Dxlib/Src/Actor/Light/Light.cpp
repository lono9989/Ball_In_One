#include "Light.h"

#include <typeinfo>

Light::Light(IWorld* world, const GSvector3& position, const COLOR_F& amb, const COLOR_F& dif, const COLOR_F& spc)
{
	world_ = world;
	name_ = "Light";
	tag_ = "LightTag";


	SetLightAmbColor(amb);
	SetLightDifColor(dif);
	SetLightSpcColor(spc);
	SetLightPosition(position.VECTOR_);
	SetLightDirection(VGet(45.0f, -60.0f, 20.0f));
}

void Light::draw() const
{

}
