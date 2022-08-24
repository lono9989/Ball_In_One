#include "Mylib/Debug.h"
#include "Collision/Line.h"
#include "Collision/Ray.h"

void Debug::DrawCoordinateAxis(GStransform transform)
{
	//x
	DrawArrow(transform.position().VECTOR_, (transform.position() + transform.right() * 10).VECTOR_, GetColor(255, 0, 0));
	//y
	DrawArrow(transform.position().VECTOR_, (transform.position() + transform.up() * 10).VECTOR_, GetColor(0, 255, 0));
	//z
	DrawArrow(transform.position().VECTOR_, (transform.position() + transform.forward() * 10).VECTOR_, GetColor(0, 0, 255));
}

void Debug::Log(const TCHAR* c)
{
	printfDx(c);
}

void Debug::Log(std::string s)
{
	
	Log((s+"\n").c_str());
}

void Debug::Log(int i)
{
	Log(std::to_string(i));
}

void Debug::Log(float f)
{
	Log(std::to_string(f));
}

void Debug::Log(GSvector3 v)
{
	Log(std::to_string(v.x)+"," + std::to_string(v.y) + ","+ std::to_string(v.z));
}

void Debug::Log(VECTOR v)
{
	Log(std::to_string(v.x) + "," + std::to_string(v.y) + "," + std::to_string(v.z));
}

void Debug::DrawLine(Line l,unsigned int color)
{
	DrawLine3D(l.start.VECTOR_, l.end.VECTOR_, color);
}

void Debug::DrawRay(Ray ray,float length, unsigned int color)
{
	DrawLine(Line{ ray.position,ray.position + ray.direction.normalized() * length },color);
}

void Debug::DrawArrow(VECTOR from, VECTOR to, unsigned int color)
{
	SetUseLighting(FALSE);
	DrawLine(Line{ from,to }, color);
	DrawCone3D(to, VSub(to,VScale(VSub(to, from), VSize(VSub(to, from))*0.01f)), VSize(VSub(to, from)) * 0.05f, 16, color, color, TRUE);
	SetUseLighting(TRUE);
}
