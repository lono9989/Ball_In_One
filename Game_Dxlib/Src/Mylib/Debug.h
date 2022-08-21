#ifndef DEBUG_H_
#define DEBUG_H_

#include "DxLib.h"
#include "Mylib/Mylib.h"

static class Debug {
public:
	/// <summary>
	/// ���W����\��
	/// </summary>
	/// <param name="transform">�g�����X�t�H�[��</param>
	static void DrawCoordinateAxis(GStransform transform);

private:
	void DrawArrow(VECTOR from, VECTOR to, unsigned int color);
};

#endif // !DEBUG_H_
