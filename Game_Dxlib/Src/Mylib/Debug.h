#ifndef DEBUG_H_
#define DEBUG_H_

#include "DxLib.h"
#include "Mylib/Mylib.h"
#include <string>
class Ray;
class Line;

static class Debug {
public:
	/// <summary>
	/// ���W����\��
	/// </summary>
	/// <param name="transform">�g�����X�t�H�[��</param>
	static void DrawCoordinateAxis(GStransform transform);

	//���O�\��
	static void Log(const TCHAR* c);
	static void Log(std::string s);
	static void Log(int i);
	static void Log(float f);
	static void Log(GSvector3 v);
	static void Log(VECTOR v);


	/// <summary>
	/// Line���f�o�b�O�\��
	/// </summary>
	/// <param name="l">Line</param>
	/// <param name="color">�J���[</param>
	static void DrawLine(Line l,unsigned int color = GetColor(255,255,255));
	/// <summary>
	/// Ray���f�o�b�O�\��
	/// </summary>
	/// <param name="ray">Ray</param>
	/// <param name="length">�ő勗��</param>
	/// <param name="color">�J���[</param>
	static void DrawRay(Ray ray,float length=1000.0f,unsigned int color = GetColor(255, 255, 255));

private:
	static void DrawArrow(VECTOR from, VECTOR to, unsigned int color);
};

#endif // !DEBUG_H_
