#ifndef DEBUG_H_
#define DEBUG_H_

#include "DxLib.h"
#include "Mylib/Mylib.h"
#include <string>
class Ray;
class Line;

//デバッグ表示用クラス(Dxlib関数仕様)
class Debug {
public:
	/// <summary>
	/// 座標軸を表示
	/// </summary>
	/// <param name="transform">トランスフォーム</param>
	static void DrawCoordinateAxis(GStransform transform);

	//ログ表示
	static void Log(const TCHAR* c);
	static void Log(std::string s);
	static void Log(int i);
	static void Log(float f);
	static void Log(GSvector3 v);
	static void Log(VECTOR v);
	static void ClearLog();

	///デバッグ用文字描画
	static void DrawData(float x,float y, const TCHAR* c, unsigned int color = GetColor(255, 255, 255));
	static void DrawData(float x,float y, std::string s, unsigned int color = GetColor(255, 255, 255));
	static void DrawData(float x,float y, int i, unsigned int color = GetColor(255, 255, 255));
	static void DrawData(float x,float y, float f, unsigned int color = GetColor(255, 255, 255));
	static void DrawData(float x,float y, GSvector3 v, unsigned int color = GetColor(255, 255, 255));
	static void DrawData(float x,float y, VECTOR v, unsigned int color = GetColor(255, 255, 255));


	/// <summary>
	/// Lineをデバッグ表示
	/// </summary>
	/// <param name="l">Line</param>
	/// <param name="color">カラー</param>
	static void DrawLine(Line l, unsigned int color = GetColor(255, 255, 255));
	/// <summary>
	/// Rayをデバッグ表示
	/// </summary>
	/// <param name="ray">Ray</param>
	/// <param name="length">最大距離</param>
	/// <param name="color">カラー</param>
	static void DrawRay(Ray ray, float length = 1000.0f, unsigned int color = GetColor(255, 255, 255));

private:
	static void DrawArrow(VECTOR from, VECTOR to, unsigned int color);
};
#endif // !DEBUG_H_