#include "Mylib/Debug.h"
#include "Collision/Line.h"
#include "Collision/Ray.h"

void Debug::DrawCoordinateAxis(GStransform transform)
{
#if _DEBUG
	//x
	DrawArrow(transform.position().VECTOR_, (transform.position() + transform.right() * 10).VECTOR_, GetColor(255, 0, 0));
	//y
	DrawArrow(transform.position().VECTOR_, (transform.position() + transform.up() * 10).VECTOR_, GetColor(0, 255, 0));
	//z
	DrawArrow(transform.position().VECTOR_, (transform.position() + transform.forward() * 10).VECTOR_, GetColor(0, 0, 255));
#endif
}

void Debug::Log(const TCHAR* c)
{
#if _DEBUG
	printfDx(c);
#endif
}

void Debug::Log(std::string s)
{
#if _DEBUG
	Log((s+"\n").c_str());
#endif	
}

void Debug::Log(int i)
{
#if _DEBUG
	Log(std::to_string(i));
#endif
}

void Debug::Log(float f)
{
#if _DEBUG
	Log(std::to_string(f));
#endif
}

void Debug::Log(GSvector3 v)
{
#if _DEBUG
	Log(std::to_string(v.x)+"," + std::to_string(v.y) + ","+ std::to_string(v.z));
#endif
}

void Debug::Log(VECTOR v)
{
#if _DEBUG
	Log(std::to_string(v.x) + "," + std::to_string(v.y) + "," + std::to_string(v.z));
#endif
}

void Debug::ClearLog()
{
#if _DEBUG
	clsDx();
#endif
}

void Debug::DrawData(float x, float y, const TCHAR* c, unsigned int color)
{
#if _DEBUG
	DrawString(x,y, c, color);
#endif
}

void Debug::DrawData(float x, float y, std::string s, unsigned int color)
{
#if _DEBUG
	DrawData(x, y, s.c_str(), color);
#endif
}

void Debug::DrawData(float x, float y, int i, unsigned int color)
{
#if _DEBUG
	DrawData(x, y, std::to_string(i), color);
#endif
}

void Debug::DrawData(float x, float y, float f, unsigned int color)
{
#if _DEBUG
	DrawData(x, y, std::to_string(f), color);
#endif
}

void Debug::DrawData(float x, float y, GSvector3 v, unsigned int color)
{
#if _DEBUG
	DrawData(x, y, std::to_string(v.x) + "," + std::to_string(v.y) + "," + std::to_string(v.z), color);
#endif
}

void Debug::DrawData(float x, float y, VECTOR v, unsigned int color)
{
#if _DEBUG
	DrawData(x, y, std::to_string(v.x) + "," + std::to_string(v.y) + "," + std::to_string(v.z), color);
#endif
}

void Debug::DrawLine(Line l,unsigned int color)
{
#if _DEBUG
	DrawLine3D(l.start.VECTOR_, l.end.VECTOR_, color);
#endif
}

void Debug::DrawRay(Ray ray,float length, unsigned int color)
{
#if _DEBUG
	DrawLine(Line{ ray.position,ray.position + ray.direction.normalized() * length },color);
#endif
}

void Debug::DrawArrow(VECTOR from, VECTOR to, unsigned int color)
{
#if _DEBUG
	SetUseLighting(FALSE);
	DrawLine(Line{ from,to }, color);
	DrawCone3D(to, VSub(to,VScale(VSub(to, from), VSize(VSub(to, from))*0.01f)), VSize(VSub(to, from)) * 0.05f, 16, color, color, TRUE);
	SetUseLighting(TRUE);
#endif
}
