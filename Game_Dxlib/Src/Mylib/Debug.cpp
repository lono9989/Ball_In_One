#include "Mylib/Debug.h"

void Debug::DrawCoordinateAxis(GStransform transform)
{
	//x
	DrawLine3D(transform.position().VECTOR_, (transform.position() + transform.right() * 10).VECTOR_, GetColor(255, 0, 0));
	//y
	DrawLine3D(transform.position().VECTOR_, (transform.position() + transform.up() * 10).VECTOR_, GetColor(0, 255, 0));
	//z
	DrawLine3D(transform.position().VECTOR_, (transform.position() + transform.forward() * 10).VECTOR_, GetColor(0, 0, 255));
}

void Debug::DrawArrow(VECTOR from, VECTOR to, unsigned int color)
{


}
