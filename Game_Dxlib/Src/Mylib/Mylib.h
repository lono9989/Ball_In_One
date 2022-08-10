#ifndef MYLIB_H_
#define MYLIB_H_

#include "GSlib/GStype.h"
#include "GSlib/GScollision.h"
#include "GSlib/GSmath.h"
#include "GSlib/GSmathf.h"
//#include "GSlib/GSmatrix3.h"
//#include "GSlib/GSmatrix4.h"
//#include "GSlib/GSplane.h"
//#include "GSlib/GSquaternion.h"
#include "GSlib/GStransform.h"
//#include "GSlib/GSvector2.h"
//#include "GSlib/GSvector3.h"
//#include "GSlib/GSvector4.h"
#include "DXlib_Input/InputManager.h"

static VECTOR	Get_Triangle_Point_MinPosition(VECTOR Point, VECTOR TrianglePos1, VECTOR TrianglePos2, VECTOR TrianglePos3)
{
	VECTOR Line12, Line23, Line31, Line1P, Line2P, Line3P, Result;
	float Dot1P2, Dot1P3, Dot2P1, Dot2P3, Dot2PH, Dot3P1, Dot3P2, Dot3PH, OPA, OPB, OPC, Div, t, v, w;

	VectorSub(&Line12, &TrianglePos2, &TrianglePos1);
	VectorSub(&Line31, &TrianglePos1, &TrianglePos3);
	VectorSub(&Line1P, &Point, &TrianglePos1);
	Dot1P2 = VectorInnerProduct(&Line12, &Line1P);
	Dot1P3 = VectorInnerProduct(&Line31, &Line1P);
	if (Dot1P2 <= 0.0f && Dot1P3 >= 0.0f) return TrianglePos1;

	VectorSub(&Line23, &TrianglePos3, &TrianglePos2);
	VectorSub(&Line2P, &Point, &TrianglePos2);
	Dot2P1 = VectorInnerProduct(&Line12, &Line2P);
	Dot2P3 = VectorInnerProduct(&Line23, &Line2P);
	if (Dot2P1 >= 0.0f && Dot2P3 <= 0.0f) return TrianglePos2;

	Dot2PH = VectorInnerProduct(&Line31, &Line2P);
	OPC = Dot1P2 * -Dot2PH - Dot2P1 * -Dot1P3;	// ←ラグランジュ恒等式
	if (OPC <= 0.0f && Dot1P2 >= 0.0f && Dot2P1 <= 0.0f)
	{
		t = Dot1P2 / (Dot1P2 - Dot2P1);
		Result.x = TrianglePos1.x + Line12.x * t;
		Result.y = TrianglePos1.y + Line12.y * t;
		Result.z = TrianglePos1.z + Line12.z * t;
		return Result;
	}

	VectorSub(&Line3P, &Point, &TrianglePos3);
	Dot3P1 = VectorInnerProduct(&Line31, &Line3P);
	Dot3P2 = VectorInnerProduct(&Line23, &Line3P);
	if (Dot3P1 <= 0.0f && Dot3P2 >= 0.0f) return TrianglePos3;

	Dot3PH = VectorInnerProduct(&Line12, &Line3P);
	OPB = Dot3PH * -Dot1P3 - Dot1P2 * -Dot3P1;	// ←ラグランジュ恒等式
	if (OPB <= 0.0f && Dot1P3 <= 0.0f && Dot3P1 >= 0.0f)
	{
		t = Dot3P1 / (Dot3P1 - Dot1P3);
		Result.x = TrianglePos3.x + Line31.x * t;
		Result.y = TrianglePos3.y + Line31.y * t;
		Result.z = TrianglePos3.z + Line31.z * t;
		return Result;
	}

	OPA = Dot2P1 * -Dot3P1 - Dot3PH * -Dot2PH;	// ←ラグランジュ恒等式
	if (OPA <= 0.0f && (-Dot2PH - Dot2P1) >= 0.0f && (Dot3PH + Dot3P1) >= 0.0f)
	{
		t = (-Dot2PH - Dot2P1) / ((-Dot2PH - Dot2P1) + (Dot3PH + Dot3P1));
		Result.x = TrianglePos2.x + Line23.x * t;
		Result.y = TrianglePos2.y + Line23.y * t;
		Result.z = TrianglePos2.z + Line23.z * t;
		return Result;
	}

	Div = 1.0f / (OPA + OPB + OPC);
	v = OPB * Div;
	w = OPC * Div;
	Result.x = TrianglePos1.x + Line12.x * v - Line31.x * w;
	Result.y = TrianglePos1.y + Line12.y * v - Line31.y * w;
	Result.z = TrianglePos1.z + Line12.z * v - Line31.z * w;
	return Result;
}


#endif // !MYLIB_H_
