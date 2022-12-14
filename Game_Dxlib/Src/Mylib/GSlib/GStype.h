/******************************************************************************
* File Name : GStype.h                              Ver : 1.00  Date : 98-10-22
*
* Description :
*
*       ゲームシステム 基本データ型定義ファイル．
*
* Author : Moriharu Ohzu.
*
******************************************************************************/
#ifndef		_GSTYPE_H_
#define		_GSTYPE_H_

//#include	<windows.h>
//#include	<GL/gl.h>
#include "DxLib.h"

#undef max
#undef min

#pragma warning(push)
#pragma warning(disable:4201) // 無名構造体の使用
#pragma warning(disable:4458) // クラスメンバの隠蔽


/****** データ型宣言 *********************************************************/

/*----- 基本データ型 --------------------------------------------------------*/

typedef	unsigned int	GSenum;
typedef	unsigned char	GSboolean;
typedef	unsigned int	GSbitfield;
typedef	signed char		GSbyte;
typedef	short			GSshort;
typedef	int				GSint;
typedef	int				GSsizei;
typedef	unsigned char	GSubyte;
typedef	unsigned short	GSushort;
typedef	unsigned int	GSuint;
typedef	float			GSfloat;
typedef	float			GSclampf;
typedef	double			GSdouble;
typedef	double			GSclampd;
typedef	void			GSvoid;

#define	GS_TRUE			1				/* 真 */
#define	GS_FALSE		0				/* 偽 */


/* インライン関数の定義 */
#ifdef __cplusplus
#define	GSINLINE	inline				/* Ｃ＋＋ */
#else
#define	GSINLINE	static _inline		/* Ｃ言語 */
#endif

/* Ｃ＋＋前方参照 */
#ifdef __cplusplus
struct GSvector2;
struct GSvector3;
struct GSvector4;
struct GSquaternion;
struct GSplane;
struct GSmatrix3;
struct GSmatrix4;
#endif

/*----- ２次元座標・２次元ベクトル構造体 ------------------------------------*/

typedef struct GSvector2
{
	union
	{
		struct
		{
			GSfloat		x;				/* ｘ座標                   */
			GSfloat		y;				/* ｙ座標                   */
		};
		struct
		{
			GSfloat		s;				/* ｓ座標                   */
			GSfloat		t;				/* ｔ座標                   */
		};
		GSfloat			v[2];			/* ｘｙ座標                 */
		
	};

#ifdef __cplusplus

	/** コンストラクタ */
	GSvector2() {}
	GSvector2( GSfloat X, GSfloat Y );
	explicit GSvector2( const GSvector3& v3 );
	explicit GSvector2( const GSvector4& v4 );
	explicit GSvector2( const GSfloat* p );

	/** 正規化 */
	GSvector2& normalize();

	/** 正規化したベクトルを取得する */
	GSvector2 getNormalized() const;

	/** 長さを求める */
	GSfloat length() const;

	/** 長さを求める (２乗和のみ）*/
	GSfloat lengthSq() const;

	/** 距離を求める */
	GSfloat distance( const GSvector2& V ) const;

	/** 内積を求める */
	GSfloat dot( const GSvector2& V ) const;

	/** 外積を求める */
	GSfloat CCW( const GSvector2& V ) const;

	/** 小さい要素を求める */
	GSvector2 minimize( const GSvector2& V ) const;

	/** 大きい要素を求める */
	GSvector2 maximize( const GSvector2& V ) const;

	/** クランプする */
	GSvector2 clamp( const GSvector2& l, const GSvector2& h ) const;

	/** 線形補間を行う */
	GSvector2 lerp( const GSvector2& V, GSfloat t ) const;

	/** ２次補間を行う */
	GSvector2 quadratic( const GSvector2& V2, const GSvector2& V3, GSfloat t ) const;

	/** 反射ベクトルを求める */
	GSvector2 reflect( const GSvector2& N ) const;

	/** 屈折ベクトルを求める */
	GSvector2 refract( const GSvector2& N, GSfloat Eta ) const;

	/** ２つベクトルのなす角度を求める */
	GSfloat degree( const GSvector2& V ) const;

	/** 方位角を求める */
	GSfloat getDirection() const;

	/** 方位角からベクトルを求める */
	GSvector2& fromDirection(GSfloat direction);

	/** 方位角からベクトルを求める */
	static GSvector2 createFromDirection(GSfloat direction);

	/** 二つのベクトルのなす角度を求める */
	GSfloat innerDegree(const GSvector2& other) const;

	/** キャスト演算子オーバーロード */
	operator GSfloat* () const;
	operator const GSfloat* () const;

	/** 単項演算子オーバーロード */
	GSvector2  operator + () const;
	GSvector2  operator - () const;

	/** 代入演算子オーバーロード */
	GSvector2&  operator += ( const GSvector2& v );
	GSvector2&  operator -= ( const GSvector2& v );
	GSvector2&  operator *= ( const GSvector2& v );
	GSvector2&  operator /= ( const GSvector2& v );
	GSvector2&  operator *= ( GSfloat s );
	GSvector2&  operator /= ( GSfloat s );

	/** ２項演算子オーバーロード */
	friend const GSvector2 operator + ( const GSvector2& v1, const GSvector2& v2 );
	friend const GSvector2 operator - ( const GSvector2& v1, const GSvector2& v2 );
	friend const GSvector2 operator * ( const GSvector2& v, const GSfloat s );
	friend const GSvector2 operator * ( const GSfloat s, const GSvector2& v );
	friend const GSvector2 operator * ( const GSmatrix3& m, const GSvector2& v );
	friend const GSvector2 operator * ( const GSvector2& v, const GSmatrix3& m );
	friend const GSvector2 operator / ( const GSvector2& v, const GSfloat s );
	friend bool operator == ( const GSvector2& v1, const GSvector2& v2 );
	friend bool operator != ( const GSvector2& v1, const GSvector2& v2 );
	friend bool operator < ( const GSvector2& v1, const GSvector2& v2 );
	friend bool operator > ( const GSvector2& v1, const GSvector2& v2 );
	friend bool operator <= ( const GSvector2& v1, const GSvector2& v2 );
	friend bool operator >= ( const GSvector2& v1, const GSvector2& v2 );

	// --- Unity互換インターフェースの追加 2020/04/13 

	// GSvector2(0, 0) と同じ意味
	static GSvector2 zero();
	// GSvector2(1, 1) と同じ意味
	static GSvector2 one();
	// GSvector2(0, 1) と同じ意味
	static GSvector2 up();
	// GSvector2(0, -1) と同じ意味
	static GSvector2 down();
	// GSvector2(-1, 0) と同じ意味
	static GSvector2 left();
	// GSvector2(1, 0) と同じ意味
	static GSvector2 right();

	// ベクトルの長さ（読み取り専用）
	float magnitude() const;
	// magnitude を 1 としたベクトル（読み取り専用）
	GSvector2 normalized() const;
	//　ベクトルの 2 乗の長さを返します（読み取り専用）
	float sqrMagnitude() const;

	// [0] や[1] を使用して x や y 成分にアクセスします
	float operator[](int index) const;
	float& operator[](int index);

	// 既存の GSvector2 に x と y の成分を設定します
	void set(float x, float y);

	// 2つのベクトルのなす角を返します
	static float angle(const GSvector2& from, const GSvector2& to);
	// 大きさを maxLength までに制限した vector のコピーを返します
	static GSvector2 clampMagnitude(const GSvector2& vector, float max_length);
	// a と b の間の距離を返します
	static float distance(const GSvector2& a, const GSvector2& b);
	// 2 つのベクトルの内積
	static float dot(const GSvector2& lhs, const GSvector2& rhs);

	// 2つベクトルaとbの線形補間します。
	static GSvector2 lerp(const GSvector2& a, const GSvector2& b, float t);
	// 2つベクトルa と b の線形補間します。
	static GSvector2 lerpUnclamped(const GSvector2& a, const GSvector2& b, float t);
	// 2つのベクトルで各成分の一番大きな値を使用してベクトルを作成します
	static GSvector2 max(const GSvector2& lhs, const GSvector2& rhs);
	// 2 つのベクトルで各成分の一番小さな値を使用してベクトルを作成します
	static GSvector2 min(const GSvector2& lhs, const GSvector2& rhs);
	// 現在の位置 current から target に向けて移動します
	static GSvector2 moveTowards(const GSvector2& current, const GSvector2& target,
		float max_distance_delta);
	// この2Dベクトルに垂直な2Dベクトルを返します。
	// 正のY軸が上がる2D座標系では、結果は常に反時計回りに90度回転します。
	static GSvector2 perpendicular(const GSvector2& inDirection);
	// 法線を基準にしてベクトルの反射したベクトルを取得します
	static GSvector2 reflect(const GSvector2& inDirection, const GSvector2& inNormal);
	// 2つのベクトルの各成分を乗算します
	static GSvector2 scale(const GSvector2& a, const GSvector2& b);
	// Returns the signed angle in degrees between from and to.
	static float signedAngle(const GSvector2& from, const GSvector2& to);
	// 目的地に向かって時間の経過とともに徐々にベクトルを変化させます
	GSvector2 smoothDamp(const GSvector2& current, const GSvector2& target,
		GSvector2& currentVelocity, float smooth_time, float max_speed, float delta_time);
#endif

} GSvector2;

/*----- ３次元座標・３次元ベクトル構造体 ------------------------------------*/

typedef struct GSvector3
{
	union
	{
		struct
		{
			GSfloat		x;				/* ｘ座標                   */
			GSfloat		y;				/* ｙ座標                   */
			GSfloat		z;				/* ｚ座標                   */
		};
		struct
		{
			GSfloat		s;				/* ｓ座標                   */
			GSfloat		t;				/* ｔ座標                   */
			GSfloat		p;				/* ｐ座標                   */
		};
		struct
		{
			GSfloat		r;				/* 赤成分                   */
			GSfloat		g;				/* 緑成分                   */
			GSfloat		b;				/* 青成分                   */
		};
		struct
		{
			GSvector2	xy;				/* ｘｙ座標                 */
		};
		VECTOR VECTOR_;
		GSfloat			v[3];			/* ｘｙｚ座標               */
	};

#ifdef __cplusplus

	/** コンストラクタ */
	GSvector3() {}
	GSvector3( GSfloat X, GSfloat Y, GSfloat Z );
	GSvector3( const GSvector2& v2, GSfloat Z = 0.0f );
	GSvector3(const VECTOR& v);
	explicit GSvector3( const GSvector4& v4 );
	explicit GSvector3( const GSfloat* p );

	/** 正規化 */
	GSvector3& normalize();

	/** 正規化したベクトルを取得する */
	GSvector3 getNormalized() const;

	/** 長さを求める */
	GSfloat length() const;

	/** 長さを求める (２乗和のみ）*/
	GSfloat lengthSq() const;

	/** 距離を求める */
	GSfloat distance( const GSvector3& V ) const;

	/** 内積を求める */
	GSfloat dot( const GSvector3& V ) const;

	/** 外積を求める */
	GSvector3 cross( const GSvector3& V ) const;

	/** 小さい要素を求める */
	GSvector3 minimize( const GSvector3& V ) const;

	/** 大きい要素を求める */
	GSvector3 maximize( const GSvector3& V ) const;

	/** クランプする */
	GSvector3 clamp( const GSvector3& l, const GSvector3& h ) const;

	/** 線形補間を行う */
	GSvector3 lerp( const GSvector3& V, GSfloat t ) const;

	/** ２次補間を行う */
	GSvector3 quadratic( const GSvector3& V2, const GSvector3& V3, GSfloat t ) const;

	/** 反射ベクトルを求める */
	GSvector3 reflect( const GSvector3& N ) const;

	/** 屈折ベクトルを求める */
	GSvector3 refract( const GSvector3& N, GSfloat Eta ) const;

	/** ２つベクトルのなす角度を求める */
	GSfloat degree( const GSvector3& V ) const;

	/** ヨーを求める */
	GSfloat getYaw() const;

	/** ピッチを求める */
	GSfloat getPitch() const;

	/** ピッチ・ヨーからベクトルを求める */
	GSvector3& fromPitchYaw( GSfloat picth, GSfloat yow );

	/** ピッチ・ヨーからベクトルを求める */
	static GSvector3 createFromPitchYaw(GSfloat picth, GSfloat yow);

	/** 法線ベクトルを求める */
	GSvector3 calculateNormal( const GSvector3& V1, const GSvector3& V2 ) const;

	/** 二つのベクトルのなす角度を求める */
	GSfloat innerDegree( const GSvector3& other ) const;

	/** キャスト演算子オーバーロード */
	operator GSfloat* () const;
	operator const GSfloat* () const;

	/** 単項演算子オーバーロード */
	GSvector3  operator + () const;
	GSvector3  operator - () const;

	/** 代入演算子オーバーロード */
	GSvector3&  operator += ( const GSvector3& v );
	GSvector3&  operator -= ( const GSvector3& v );
	GSvector3&  operator *= ( const GSvector3& v );
	GSvector3&  operator /= ( const GSvector3& v );
	GSvector3&  operator *= ( GSfloat s );
	GSvector3&  operator /= ( GSfloat s );

	/** ２項演算子オーバーロード */
	friend const GSvector3 operator + ( const GSvector3& v1, const GSvector3& v2 );
	friend const GSvector3 operator - ( const GSvector3& v1, const GSvector3& v2 );
	friend const GSvector3 operator * ( const GSvector3& v, const GSfloat s );
	friend const GSvector3 operator * ( const GSfloat s, const GSvector3& v );
	friend const GSvector3 operator * ( const GSmatrix4& m, const GSvector3& v );
	friend const GSvector3 operator * ( const GSvector3& v, const GSmatrix4& m );
	friend const GSvector3 operator * ( const GSmatrix3& m, const GSvector3& v );
	friend const GSvector3 operator * ( const GSvector3& v, const GSmatrix3& m );
	friend const GSvector3 operator / ( const GSvector3& v, const GSfloat s );
	friend bool operator == ( const GSvector3& v1, const GSvector3& v2 );
	friend bool operator != ( const GSvector3& v1, const GSvector3& v2 );
	friend bool operator < ( const GSvector3& v1, const GSvector3& v2 );
	friend bool operator > ( const GSvector3& v1, const GSvector3& v2 );
	friend bool operator <= ( const GSvector3& v1, const GSvector3& v2 );
	friend bool operator >= ( const GSvector3& v1, const GSvector3& v2 );

	// --- Unity互換インターフェースの追加 2020/04/13 

	// ベクトルの長さ
	float magnitude() const;
	// magnitude を 1 としたベクトル
	GSvector3 normalized() const;
	// ベクトルの2乗の長さ
	float sqrMagnitude() const;
	// [0] や[1] を使用して x や y 成分にアクセスします
	float operator[](int index) const;
	float& operator[](int index);

	// 2つのベクトルの各成分を乗算します
	void scale(const GSvector3& v);
	// 既存の Vector3 に x、y、z の成分を設定します
	void set(float new_x, float new_y, float new_z);

	// 2点間（from と to）の角度を返します
	static float angle(const GSvector3& from, const GSvector3& to);
	// 大きさをmax_lengthまでに制限した vector のコピーを返します
	static GSvector3 clampMagnitude(const GSvector3& vector, float max_length);
	// 2つのベクトルの外積
	static GSvector3 cross(const GSvector3& lhs, const GSvector3& rhs);
	// a と b の間の距離を返します
	static float distance(const GSvector3& a, const GSvector3& b);
	// 2つのベクトルの内積
	static float dot(const GSvector3& lhs, const GSvector3& rhs);

	// 直線上にある 2 つのベクトル間を補間します
	static GSvector3 lerp(const GSvector3& a, const GSvector3& b, float t);
	// 直線上にある 2 つのベクトル間を補間します
	static GSvector3 lerpUnclamped(const GSvector3& a, const GSvector3& b, float t);
	// 2つのベクトルで各成分の一番大きな値を使用してベクトルを作成します
	static GSvector3 max(const GSvector3& lhs, const GSvector3& rhs);
	// 2つのベクトルで各成分の一番小さな値を使用してベクトルを作成します
	static GSvector3 min(const GSvector3& lhs, const GSvector3& rhs);

	// 現在の位置 current から target に向けて移動します
	static GSvector3 moveTowards(const GSvector3& current, const GSvector3& target, float max_distance_delta);
	// magnitude を 1 としたベクトルを作成します
	static GSvector3 normalize(const GSvector3& value);
	// ベクトルが正規化され他のベクトルと直交するようにします
	static void orthoNormalize(GSvector3& normal, GSvector3& tangent, GSvector3& binormal);

	// ベクトルを別のベクトルに投影します
	static GSvector3 project(const GSvector3& vector, const GSvector3& onNormal);
	// 平面に垂直な法線ベクトルによって定義される平面上にベクトルを射影します
	static GSvector3 projectOnPlane(const GSvector3& vector, const GSvector3& planeNormal);
	// 法線で定義された平面でベクトルを反射します
	static GSvector3 reflect(const GSvector3& inDirection, const GSvector3& inNormal);
	// 現在の位置 current から target に向けてベクトルを回転します。
	static GSvector3 rotateTowards(const GSvector3& current, const GSvector3& target, float max_radian_delta, float max_magnitude_delta);
	// 2つのベクトルの各成分を乗算します
	static GSvector3 scale(const GSvector3& a, const GSvector3& b);
	// 2点間（from と to）の符号付き角度を返します
	static float signed_angle(const GSvector3& from, const GSvector3& to, const GSvector3& axis = up());
    // 2点間（from と to）の符号付き角度を返します
    static float signedAngle(const GSvector3& from, const GSvector3& to, const GSvector3& axis = up());
    // 球状に 2 つのベクトル間を補間します
	static GSvector3 slerp(const GSvector3& a, const GSvector3& b, float t);
	// 球状に 2 つのベクトル間を補間します
	static GSvector3 slerpUnclamped(const GSvector3& a, const GSvector3& b, float t);

	// 目的地に向かって時間の経過とともに徐々にベクトルを変化させます
	static GSvector3 smoothDamp(const GSvector3& current, const GSvector3& target, GSvector3& current_velocity, float smooth_time, float max_speed, float delta_time);

	// Vector3(0, 0, 0) と同じ意味
	static GSvector3 zero();
	// Vector3(1, 1, 1) と同じ意味
	static GSvector3 one();
	// Vector3(0, 1, 0) と同じ意味
	static GSvector3 up();
	// Vector3(0, -1, 0) と同じ意味
	static GSvector3 down();
	// Vector3(1, 0, 0) と同じ意味
	static GSvector3 left();
	// Vector3(-1, 0, 0) と同じ意味
	static GSvector3 right();
	// Vector3(0, 0, 1) と同じ意味
	static GSvector3 forward();
	// Vector3(0, 0, -1) と同じ意味
	static GSvector3 back();
	// 正の無限大
	static GSvector3 positiveInfinity();
	// 負の無限大
	static GSvector3 negativeInfinity();
#endif

} GSvector3;

/*----- ４次元座標・４次元ベクトル構造体 ------------------------------------*/

typedef struct GSvector4
{
	union
	{
		struct
		{
			GSfloat		x;				/* ｘ座標                   */
			GSfloat		y;				/* ｙ座標                   */
			GSfloat		z;				/* ｚ座標                   */
			GSfloat		w;				/* ｗ座標                   */
		};
		struct
		{
			GSfloat		s;				/* ｓ座標                   */
			GSfloat		t;				/* ｔ座標                   */
			GSfloat		p;				/* ｐ座標                   */
			GSfloat		q;				/* ｑ座標                   */
		};
		struct
		{
			GSfloat		r;				/* 赤成分                   */
			GSfloat		g;				/* 緑成分                   */
			GSfloat		b;				/* 青成分                   */
			GSfloat		a;				/* アルファ成分             */
		};
		struct
		{
			GSvector2	xy;				/* ｘｙ座標                 */
		};
		struct
		{
			GSvector3	xyz;			/* ｘｙｚ座標               */
		};
		struct {
			VECTOR VECTOR_;
		};
		struct
		{
			GSvector3	rgb;			/* ＲＧＢ                   */
		};
		GSfloat			v[4];			/* ｘｙｚｗ座標             */
	};

#ifdef __cplusplus

	/** コンストラクタ */
	GSvector4() {}
	GSvector4( GSfloat X, GSfloat Y, GSfloat Z, GSfloat W );
	GSvector4( const GSvector2& v2, GSfloat Z = 0.0f, GSfloat W = 0.0f );
	GSvector4( const GSvector3& v3, GSfloat W = 0.0f );
	explicit GSvector4( const GSfloat* p );

	/** 正規化したベクトルを取得する */
	GSvector4& normalize();

	/** 正規化したベクトルを取得する */
	GSvector4 getNormalized() const;

	/** 長さを求める */
	GSfloat length() const;

	/** 長さを求める (２乗和のみ）*/
	GSfloat lengthSq() const;

	/** 距離を求める */
	GSfloat distance( const GSvector4& V ) const;

	/** 内積を求める */
	GSfloat dot( const GSvector4& V ) const;

	/** 小さい要素を求める */
	GSvector4 minimize( const GSvector4& V ) const;

	/** 大きい要素を求める */
	GSvector4 maximize( const GSvector4& V ) const;

	/** クランプする */
	GSvector4 clamp( const GSvector4& l, const GSvector4& h ) const;

	/** 線形補間を行う */
	GSvector4 lerp( const GSvector4& V, GSfloat t ) const;

	/** ２次補間を行う */
	GSvector4 quadratic( const GSvector4& V2, const GSvector4& V3, GSfloat t ) const;

	/** キャスト演算子オーバーロード */
	operator GSfloat* () const;
	operator const GSfloat* () const;

	/** 単項演算子オーバーロード */
	GSvector4 operator + () const;
	GSvector4 operator - () const;

	/** 代入演算子オーバーロード */
	GSvector4& operator += ( const GSvector4& v );
	GSvector4& operator -= ( const GSvector4& v );
	GSvector4& operator *= ( const GSvector4& v );
	GSvector4& operator /= ( const GSvector4& v );
	GSvector4& operator *= ( GSfloat s );
	GSvector4& operator /= ( GSfloat s );

	/** ２項演算子オーバーロード */
	friend const GSvector4 operator + ( const GSvector4& v1, const GSvector4& v2 );
	friend const GSvector4 operator - ( const GSvector4& v1, const GSvector4& v2 );
	friend const GSvector4 operator * ( const GSvector4& v, const GSfloat s );
	friend const GSvector4 operator * ( const GSfloat s, const GSvector4& v );
	friend const GSvector4 operator * ( const GSmatrix4& m, const GSvector4& v );
	friend const GSvector4 operator * ( const GSvector4& v, const GSmatrix4& m );
	friend const GSvector4 operator / ( const GSvector4& v, const GSfloat s );
	friend bool operator == ( const GSvector4& v1, const GSvector4& v2 );
	friend bool operator != ( const GSvector4& v1, const GSvector4& v2 );
	friend bool operator < ( const GSvector4& v1, const GSvector4& v2 );
	friend bool operator > ( const GSvector4& v1, const GSvector4& v2 );
	friend bool operator <= ( const GSvector4& v1, const GSvector4& v2 );
	friend bool operator >= ( const GSvector4& v1, const GSvector4& v2 );

    // 直線上にある 2 つのベクトル間を補間します
    static GSvector4 lerp(const GSvector4& a, const GSvector4& b, float t);
    // 直線上にある 2 つのベクトル間を補間します
    static GSvector4 lerpUnclamped(const GSvector4& a, const GSvector4& b, float t);

#endif

} GSvector4;

/*----- カラー構造体 --------------------------------------------------------*/

typedef	struct GSvector4	GScolor;		/* カラー型			*/

/*----- 平面構造体 ----------------------------------------------------------*/

typedef struct GSplane
{
	union
	{
		struct
		{
			GSfloat			a;			/* 面法線ｘ成分             */
			GSfloat			b;			/* 面法線ｙ成分             */
			GSfloat			c;			/* 面法線ｚ成分             */
			GSfloat			d;			/* 原点からの距離           */
		};
		struct
		{
			GSvector3		normal;		/* 面法線ベクトル           */
		};
		struct
		{
			VECTOR		normalV;		/* 面法線ベクトル           */
		};
	};

#ifdef __cplusplus

	GSplane() {}
	GSplane( GSfloat A, GSfloat B, GSfloat C, GSfloat D );
	GSplane( const GSvector3& N, GSfloat D );
	GSplane( const GSvector3& P, const GSvector3& N );
	GSplane( const GSvector3& V1, const GSvector3& V2, const GSvector3& V3 );

	/** 正規化する */
	GSplane& normalize();

	/** 正規化後の平面を得る */
	GSplane getNormalized();

	/** 平面上の位置を取得 */
	GSvector3 getPoint() const;

	/** 平面とベクトルの内積を求める */
	GSfloat dot( const GSvector3& v ) const;

	/** 平面と点の距離を求める */
	GSfloat distance( const GSvector3& v ) const;

	/** 平面と線分が交差するか調べる */
	bool isIntersectLine( const GSvector3& Line0,  const GSvector3& Line1 ) const;

	/** 平面と線分の交点を取得する */
	GSvector3 getIntersectLine( const GSvector3& Line0,  const GSvector3& Line1 ) const;

	/** 平面と線分の交点を取得する */
	bool isIntersectRay( const GSvector3& Line0,  const GSvector3& Line1 ) const;

	/** 平面と線分の交点を取得する */
	GSvector3 getIntersectRay( const GSvector3& Line0,  const GSvector3& Line1 ) const;

	/** 平面と座標の距離を求める */
	GSfloat getDistance( const GSvector3& p ) const;

	/** 平面と座標の位置関係を返す */
	GSenum getClassifyPoint( const GSvector3& p ) const;

	/** 平面と球体の位置関係を返す */
	GSenum getClassifyShpere( const GSvector3& center, GSfloat Radius ) const;

	/** 線形補間を行う */
	GSplane lerp( const GSplane& V, GSfloat t ) const;

	/** ２次補間を行う */
	GSplane quadratic( const GSplane& V2, const GSplane& V3, GSfloat t ) const;

	/** 単項演算子オーバーロード */
	GSplane  operator + () const;
	GSplane  operator - () const;

	/** ２項演算子オーバーロード */
	friend const GSplane operator * ( const GSmatrix3& m, const GSplane& p );
	friend const GSplane operator * ( const GSplane& p, const GSmatrix3& m );
	friend const GSplane operator * ( const GSmatrix4& m, const GSplane& p );
	friend const GSplane operator * ( const GSplane& p, const GSmatrix4& m );

#endif

} GSplane;

/*----- クォータニオン構造体 -------------------------------------------------*/

typedef struct GSquaternion
{
	GSfloat			x;					/* ｘ軸						*/
	GSfloat			y;					/* ｙ軸						*/
	GSfloat			z;					/* ｘ軸						*/
	GSfloat			w;					/* 角度						*/

#ifdef __cplusplus

	GSquaternion() {}
	GSquaternion( GSfloat X, GSfloat Y, GSfloat Z, GSfloat W );
	GSquaternion( GSfloat angle, const GSvector3& axis );
	explicit GSquaternion( const GSmatrix3& m );
	explicit GSquaternion( const GSmatrix4& m );
	GSquaternion( const GSvector3& xAxis, const GSvector3& yAxis, const GSvector3& zAxis );


	/** 内積 */
	GSfloat dot( const GSquaternion& q ) const;

	/** 長さを求める */
	GSfloat length() const;

	/** 正規化を行う */
	GSquaternion& normalize();

	/** 逆クォータニオン化する */
	GSquaternion& inverse();

	/** 正規化後のクォータニオンを取得 */
	GSquaternion getNormalized() const;

	/** 逆クォータニオン化を取得 */
	GSquaternion getInverse () const;

	/** 回転角度からクォータニオンを設定 */
	GSquaternion& setRotate( GSfloat angle, GSfloat x, GSfloat y, GSfloat z );
	GSquaternion& setRotate( GSfloat angle, const GSvector3& axis );

	/** 回転角度からクォータニオンを設定 */
	GSquaternion& setRotateYawPitchRoll( GSfloat yaw, GSfloat pitch, GSfloat roll );

	/** 回転行列を設定 */
	GSquaternion& setMatrix( const GSmatrix3& m );
	GSquaternion& setMatrix( const GSmatrix4& m );

	/** 軸と角度を取得 */
	GSvector3 getAxis() const;
	GSfloat   getAngle() const;

	/** ヨー，ピッチ，ロールの取得 */
	GSfloat getYaw() const;
	GSfloat getPitch() const;
	GSfloat getRoll() const;

	/** 球面線形補間 */
	GSquaternion slerp( const GSquaternion& q, GSfloat t ) const;

	/** 線形補間 */
	GSquaternion lerp( const GSquaternion& q, GSfloat t ) const;

	/** 単項演算子オーバーロード */
	GSquaternion operator + () const;
	GSquaternion operator - () const;

	/** 代入演算子オーバーロード */
	GSquaternion& operator += ( const GSquaternion& v );
	GSquaternion& operator -= ( const GSquaternion& v );
	GSquaternion& operator *= ( const GSquaternion& v );
	GSquaternion& operator *= ( GSfloat s );
	GSquaternion& operator /= ( GSfloat s );

	/** ２項演算子オーバーロード */
	friend const GSquaternion operator + ( const GSquaternion& q1, const GSquaternion& q2 );
	friend const GSquaternion operator - ( const GSquaternion& q1, const GSquaternion& q2 );
	friend const GSquaternion operator * ( const GSquaternion& q1, const GSquaternion& q2 );
	friend const GSquaternion operator * ( const GSquaternion& q, const GSfloat s );
	friend const GSquaternion operator * ( const GSfloat s, const GSquaternion& q );
	friend bool operator == ( const GSquaternion& q1, const GSquaternion& q2 );
	friend bool operator != ( const GSquaternion& q1, const GSquaternion& q2 );

	// --- Unity互換インターフェースの追加 2020/04/13

	// 単位クォータニオン
	static GSquaternion identity();
	// 回転をオイラー角の値で返します
	GSvector3 eulerAngles() const;
	void eulerAngles(const GSvector3 & value);
	// 正規化
	GSquaternion normalized() const;
	// [0] や[1] を使用して x や y 成分にアクセスします
	float operator[](int index) const;
	float& operator[](int index);

	// 既存の Quaternion に x、y、z、w の成分を設定します
	void set(float newX, float newY, float newZ, float newW);
	// fromDirection から toDirection への回転を作成します
	void setFromToRotation(const GSvector3& fromDirection, const GSvector3& toDirection);
	// 指定された forward と upwards 方向に回転します
	void setLookRotation(const GSvector3& view, const GSvector3& up = GSvector3::up());
	// 回転を座標に対する角度の値 (AngleAxis) に変換します。
	void toAngleAxis(float& angle, GSvector3& axis);

	// 2 つの回転 a と b 間の角度を返します。
	static float angle(const GSquaternion& a, const GSquaternion& b);
	// axis の周りを angle 度回転する回転を作成します。
	static GSquaternion angleAxis(float angle, const GSvector3 & axis);
	// 2 つの回転の内積を返します。
	static float dot(const GSquaternion& a, const GSquaternion& b);
	// z軸を中心にz度、x軸を中心にx度、y軸を中心にy度回転する回転を返します。
	static GSquaternion euler(float x, float y, float z);
	static GSquaternion euler(const GSvector3& euler);
	// fromDirection から toDirection への回転を作成します。
	static GSquaternion fromToRotation(const GSvector3& fromDirection, const GSvector3& toDirection);
	// 逆クォータニオンを返します
	static GSquaternion inverse(const GSquaternion& rotation);
	// 指定された forward と upwards 方向に回転します
	static GSquaternion lookRotation(const GSvector3& view, const GSvector3& up = GSvector3::up());
	// 正規化したクォータニオンを返します
	static GSquaternion normalize(const GSquaternion& q);
	// from から to への回転を得ます
	static GSquaternion rotateTowards(const GSquaternion& from, const GSquaternion& to, float maxDegreesDelta);
	//　a と b の間を t で線形に補間します。パラメーター t は、[0, 1] の範囲です。
	static GSquaternion lerp(const GSquaternion& a, const GSquaternion& b, float t);
	// a と b の間を t で線形に補間します。パラメーター t は、限られていません。
	static GSquaternion lerpUnclamped(const GSquaternion& a, const GSquaternion& b, float t);
	//　a と b の間を t で球状に補間します。パラメーター t は、[0, 1] の範囲です。
	static GSquaternion slerp(const GSquaternion& a, const GSquaternion& b, float t);
	// a と b の間を t で球状に補間します。パラメーター t は、限られていません。
	static GSquaternion slerpUnclamped(const GSquaternion& a, const GSquaternion& b, float t);
	// 座標変換
	friend GSvector3 operator * (const GSquaternion& rotation, const GSvector3& point);

#endif

} GSquaternion;

/*----- ３行３列座標変換マトリクス構造体 ------------------------------------*/

typedef struct GSmatrix3
{
	union
	{
		/* ３行３列の行列           */
		GSfloat		m[3][3];
		struct
		{
			GSfloat	_11, _12, _13;
			GSfloat	_21, _22, _23;
			GSfloat	_31, _32, _33;
		};
		GSfloat		v[9];
	};

#ifdef __cplusplus

	/** コンストラクタ */
	GSmatrix3() {}
	GSmatrix3(
		GSfloat	m11, GSfloat m12, GSfloat m13,
		GSfloat	m21, GSfloat m22, GSfloat m23,
		GSfloat	m31, GSfloat m32, GSfloat m33 );
	GSmatrix3( const GSvector3& axisX,
						const GSvector3& axisY,
						const GSvector3& axisZ );
	explicit GSmatrix3( const GSfloat* V );
	explicit GSmatrix3( const GSmatrix4& M );
	explicit GSmatrix3( const GSquaternion& q );

	/** 単位行列化する */
	GSmatrix3& identity();

	/** 行列の正規化　*/
	GSmatrix3& normalize();
	/** 行列の正規化　*/
	GSmatrix3 getNormalized() const;

	/** 拡大縮小行列を乗算 */
	GSmatrix3& scale( GSfloat x, GSfloat y, GSfloat z );
	GSmatrix3& scale( const GSvector3& scaleFactor );
	GSmatrix3& scale( GSfloat scaleFactor );

	/** 回転を乗算 */
	GSmatrix3& rotate( GSfloat angle, GSfloat axisX, GSfloat axisY, GSfloat axisZ );
	GSmatrix3& rotate( GSfloat angle, const GSvector3& axis );
	GSmatrix3& rotate( const GSquaternion& q );
	GSmatrix3& rotateX( GSfloat angle );
	GSmatrix3& rotateY( GSfloat angle );
	GSmatrix3& rotateZ( GSfloat angle );
	GSmatrix3& rotateYawPitchRoll( GSfloat yaw, GSfloat pitch, GSfloat roll );

	/** 平行移動を乗算 */
	GSmatrix3& translate( GSfloat x, GSfloat y );
	GSmatrix3& translate( const GSvector2& translation );

	/** 逆行列にする */
	GSmatrix3& inverse();

	/** 転置行列にする */
	GSmatrix3& transpose();

	/** 転置逆行列にする */
	GSmatrix3& inverseTranspose();

	/** 逆行列を取得 */
	GSmatrix3 getInverse() const;

	/** 転置行列を取得 */
	GSmatrix3 getTranspose() const;

	/** 転置逆行列を取得 */
	GSmatrix3 getInverseTranspose() const;

	/** スケール値の設定 */
	GSmatrix3& setScale( GSfloat x, GSfloat y, GSfloat z );
	GSmatrix3& setScale( const GSvector3& scaleFactor );
	GSmatrix3& setScale( GSfloat scaleFactor );

	/** 回転角度の設定 */
	GSmatrix3& setRotation( GSfloat angle, GSfloat axisX, GSfloat axisY, GSfloat axisZ );
	GSmatrix3& setRotation( GSfloat angle, const GSvector3& axis );
	GSmatrix3& setRotation( const GSquaternion& q );
	GSmatrix3& setRotationX( GSfloat angle );
	GSmatrix3& setRotationY( GSfloat angle );
	GSmatrix3& setRotationZ( GSfloat angle );
	GSmatrix3& setRotationYawPitchRoll( GSfloat yaw, GSfloat pitch, GSfloat roll );

	/** 平行移動量の設定 */
	GSmatrix3& setTranslation( GSfloat x, GSfloat y );
	GSmatrix3& setTranslation( const GSvector2& translation );

	/** 座標変換 */
	GSvector2 transform( const GSvector2& v ) const;
	GSvector3 transform( const GSvector3& v ) const;
	GSplane   transform( const GSplane& p ) const;
	GSvector2 transformNormal( const GSvector2& v ) const;

	/** 軸，位置の設定 */
	GSmatrix3& setAxisX( const GSvector3& axisX );
	GSmatrix3& setAxisY( const GSvector3& axisY );
	GSmatrix3& setAxisZ( const GSvector3& axisZ );

	/** ロール・ピッチ・ヨーの取得 */
	GSfloat getRoll() const;
	GSfloat getPitch() const;
	GSfloat getYaw() const;
	void setPosition( const GSvector2& position );

	/** クォータニオンを取得 */
	GSquaternion getQuaternion() const;

	/** 軸，位置の取得 */
	GSvector3 getAxisX() const;
	GSvector3 getAxisY() const;
	GSvector3 getAxisZ() const;
	GSvector2 getPosition() const;
	GSvector3 getScale() const;

	/** 行列の補間 */
	GSmatrix3 lerp(const GSmatrix3& other, float t) const;

	/** キャスト演算子オーバーロード */
	operator GSfloat* () const;
	operator const GSfloat* () const;

	/** 単項演算子オーバーロード */
	GSmatrix3 operator + () const;
	GSmatrix3 operator - () const;

	/** 代入演算子オーバーロード */
	GSmatrix3& operator += ( const GSmatrix3& v );
	GSmatrix3& operator -= ( const GSmatrix3& v );
	GSmatrix3& operator *= ( const GSmatrix3& v );
	GSmatrix3& operator *= ( GSfloat s );
	GSmatrix3& operator /= ( GSfloat s );

	/** ２項演算子オーバーロード */
	friend const GSmatrix3 operator + ( const GSmatrix3& m1, const GSmatrix3& m2 );
	friend const GSmatrix3 operator - ( const GSmatrix3& m1, const GSmatrix3& m2 );
	friend const GSmatrix3 operator * ( const GSmatrix3& m1, const GSmatrix3& m2 );
	friend const GSmatrix3 operator * ( const GSmatrix3& m, const GSfloat s );
	friend const GSmatrix3 operator * ( const GSfloat s, const GSmatrix3& m );
	friend bool operator == ( const GSmatrix3& v1, const GSmatrix3& v2 );
	friend bool operator != ( const GSmatrix3& v1, const GSmatrix3& v2 );

#endif

} GSmatrix3;

/*----- ４行４列座標変換マトリクス構造体 ------------------------------------*/

typedef struct GSmatrix4
{
	union
	{
		/* ４行４列の行列           */
		GSfloat		m[4][4];
		struct
		{
			GSfloat	_11, _12, _13, _14;
			GSfloat	_21, _22, _23, _24;
			GSfloat	_31, _32, _33, _34;
			GSfloat	_41, _42, _43, _44;
		};
		GSfloat		v[16];
		struct
		{
			MATRIX MATRIX_;
		};
	};

#ifdef __cplusplus

	/** コンストラクタ */
	GSmatrix4() {}
	GSmatrix4(
		GSfloat	m11, GSfloat m12, GSfloat m13, GSfloat m14,
		GSfloat	m21, GSfloat m22, GSfloat m23, GSfloat m24,
		GSfloat	m31, GSfloat m32, GSfloat m33, GSfloat m34,
		GSfloat	m41, GSfloat m42, GSfloat m43, GSfloat m44  );
	GSmatrix4(
		const GSvector4& axisX,
		const GSvector4& axisY,
		const GSvector4& axisZ,
		const GSvector4& position );
	explicit GSmatrix4( const GSfloat* V );
	explicit GSmatrix4( const GSmatrix3& M );
	explicit GSmatrix4( const GSquaternion& q );

	/** 単位行列化する */
	GSmatrix4& identity();
	
	/** 行列の正規化　*/
	GSmatrix4& normalize();
	/** 行列の正規化　*/
	GSmatrix4 getNormalized() const;

	/** 拡大縮小行列を乗算 */
	GSmatrix4& scale( GSfloat x, GSfloat y, GSfloat z );

	/** 回転を乗算 */
	GSmatrix4& rotate( GSfloat angle, GSfloat axisX, GSfloat axisY, GSfloat axisZ );
	GSmatrix4& rotateYawPitchRoll( GSfloat yaw, GSfloat pitch, GSfloat roll );

	/** 平行移動を乗算 */
	GSmatrix4& translate( GSfloat x, GSfloat y, GSfloat z );

	/** 逆行列にする */
	GSmatrix4& inverse();

	/** 逆行列にする */
	GSmatrix4& inverseFast();

	/** 転置行列にする */
	GSmatrix4& transpose();

	/** 転置逆行列にする */
	GSmatrix4& inverseTranspose();

	/** 逆行列を取得 */
	GSmatrix4 getInverse() const;

	/** 逆行列を取得 */
	GSmatrix4 getInverseFast() const;

	/** 転置行列を取得 */
	GSmatrix4 getTranspose() const;

	/** 転置逆行列を取得 */
	GSmatrix4 getInverseTranspose() const;

	/** スケール値の設定 */
	GSmatrix4& setScale( GSfloat x, GSfloat y, GSfloat z );
	GSmatrix4& setScale( const GSvector3& scaleFactor );
	GSmatrix4& setScale( GSfloat scaleFactor );

	/** 回転角度の設定 */
	GSmatrix4& setRotation( GSfloat angle, GSfloat axisX, GSfloat axisY, GSfloat axisZ );
	GSmatrix4& setRotation( GSfloat angle, const GSvector3& axis );
	GSmatrix4& setRotation( const GSquaternion& q );
	GSmatrix4& setRotationX( GSfloat angle );
	GSmatrix4& setRotationY( GSfloat angle );
	GSmatrix4& setRotationZ( GSfloat angle );
	GSmatrix4& setRotationYawPitchRoll( GSfloat yaw, GSfloat pitch, GSfloat roll );

	/** 平行移動量の設定 */
	GSmatrix4& setTranslation( GSfloat x, GSfloat y, GSfloat z );
	GSmatrix4& setTranslation( const GSvector3& translation );

	/** 透視変換行列の設定 */
	GSmatrix4& setPerspectiveRH( GSfloat fovy, GSfloat aspect, GSfloat n, GSfloat f );
	GSmatrix4& setPerspectiveLH( GSfloat fovy, GSfloat aspect, GSfloat n, GSfloat f );
	GSmatrix4& setFrustumRH( GSfloat left, GSfloat right, GSfloat bottom, GSfloat top, GSfloat n, GSfloat f );
	GSmatrix4& setFrustumLH( GSfloat left, GSfloat right, GSfloat bottom, GSfloat top, GSfloat n, GSfloat f );
	GSmatrix4& setOrthoRH( GSfloat left, GSfloat right, GSfloat bottom, GSfloat top, GSfloat n = -1.0f, GSfloat f = 1.0f );
	GSmatrix4& setOrthoLH( GSfloat left, GSfloat right, GSfloat bottom, GSfloat top, GSfloat n = -1.0f, GSfloat f = 1.0f );

	/** 視野変換行列の設定 */
	GSmatrix4& setLookAtRH( GSfloat fromX, GSfloat formY, GSfloat formZ,
						    GSfloat atX,   GSfloat atY,   GSfloat atZ,
						    GSfloat upX,   GSfloat upY,   GSfloat upZ );
	GSmatrix4& setLookAtRH( const GSvector3& from, const GSvector3& at, const GSvector3& up );
	GSmatrix4& setLookAtLH( GSfloat fromX, GSfloat formY, GSfloat formZ,
						    GSfloat atX,   GSfloat atY,   GSfloat atZ,
						    GSfloat upX,   GSfloat upY,   GSfloat upZ );
	GSmatrix4& setLookAtLH( const GSvector3& from, const GSvector3& at, const GSvector3& up );

	/** 視野変換行列に変換する */
	GSmatrix4& convertViewRH();
	GSmatrix4& convertViewLH();

	/** 地平面シャドウマトリクスの設定 */
	GSmatrix4& setShadow( const GSplane& plane, const GSvector3& lightPosition );

	/** 座標変換 */
	GSvector2 transform( const GSvector2& v ) const;
	GSvector3 transform( const GSvector3& v ) const;
	GSvector4 transform( const GSvector4& v ) const;
	GSplane   transform( const GSplane& p ) const;
	GSvector2 transformCoord( const GSvector2& v ) const;
	GSvector3 transformCoord( const GSvector3& v ) const;
	GSvector4 transformCoord( const GSvector4& v ) const;
	GSvector3 transformNormal( const GSvector3& v ) const;

	/** 軸，位置の設定 */
	GSmatrix4& setAxisX( const GSvector3& axisX );
	GSmatrix4& setAxisY( const GSvector3& axisY );
	GSmatrix4& setAxisZ( const GSvector3& axisZ );
	GSmatrix4& setPosition( const GSvector3& position );

	/** ロール・ピッチ・ヨーの取得 */
	GSfloat getRoll() const;
	GSfloat getPitch() const;
	GSfloat getYaw() const;

	/** クォータニオンを取得 */
	GSquaternion getQuaternion() const;

	/** 軸，位置，スケール，回転の取得 */
	GSvector3 getAxisX() const;
	GSvector3 getAxisY() const;
	GSvector3 getAxisZ() const;
	GSvector3 getPosition() const;
	GSvector3 getScale() const;
	GSmatrix4 getRotateMatrix() const;

	/** 前向きベクトル優先で正規化 */
	GSmatrix4& nomalizeAxisZ();
	/** 上向きベクトル優先で正規化 */
	GSmatrix4& nomalizeAxisY();
	/** 左向きベクトル優先で正規化 */
	GSmatrix4& nomalizeAxisX();

	/** 行列の線形補間　*/
	GSmatrix4 lerp(const GSmatrix4& other, float t) const;

	/** キャスト演算子オーバーロード */
	operator GSfloat* () const;
	operator const GSfloat* () const;

	/** 単項演算子オーバーロード */
	GSmatrix4 operator + () const;
	GSmatrix4 operator - () const;

	/** 代入演算子オーバーロード */
	GSmatrix4& operator += ( const GSmatrix4& v );
	GSmatrix4& operator -= ( const GSmatrix4& v );
	GSmatrix4& operator *= ( const GSmatrix4& v );
	GSmatrix4& operator *= ( GSfloat s );
	GSmatrix4& operator /= ( GSfloat s );

	/** ２項演算子オーバーロード */
	friend const GSmatrix4 operator + ( const GSmatrix4& m1, const GSmatrix4& m2 );
	friend const GSmatrix4 operator - ( const GSmatrix4& m1, const GSmatrix4& m2 );
	friend const GSmatrix4 operator * ( const GSmatrix4& m1, const GSmatrix4& m2 );
	friend const GSmatrix4 operator * ( const GSmatrix4& m, const GSfloat s );
	friend const GSmatrix4 operator * ( const GSfloat s, const GSmatrix4& m );
	friend bool operator == ( const GSmatrix4& v1, const GSmatrix4& v2 );
	friend bool operator != ( const GSmatrix4& v1, const GSmatrix4& v2 );

	// --- Unity互換インターフェースの追加 2020/04/13

	// 拡大・縮小
	static GSmatrix4 scale(const GSvector3& v);
	// 回転
	static GSmatrix4 rotate(const GSquaternion& q);
	// 回転
	static GSmatrix4 rotateX(float degree);
	// 回転
	static GSmatrix4 rotateY(float degree);
	// 回転
	static GSmatrix4 rotateZ(float degree);
	// 平行移動
	static GSmatrix4 translate(const GSvector3& v);
	// この行列を移動、回転やスケーリングする行列に設定します。
	static GSmatrix4 TRS(const GSvector3& pos, const GSquaternion& q, const GSvector3& s);

	// 視野変換行列
	static GSmatrix4 lookAt(const GSvector3& eye, const GSvector3& at, const GSvector3& up);
	// 透視変換行列
	static GSmatrix4 perspective(float fov, float aspect, float zn, float zf);

	// 座標変換（通常）
	GSvector3 multiplyPoint(const GSvector3& point) const;
	// 座標変換（高速）
	GSvector3 multiplyPoint4x3(const GSvector3& point) const;
	// ベクトル変換（平行移動なし）
	GSvector3 multiplyVector(const GSvector3& point) const;

	// スケール値を取得
	GSvector3 scale() const;
	// 座標を取得
	GSvector3 position() const;
	// 回転の取得
	GSquaternion rotation() const;
	// 前方向ベクトルを取得
	GSvector3 forward() const;
	// 上方向ベクトルを取得
	GSvector3 up() const;
	// 左方向ベクトルを取得
	GSvector3 left() const;

	// この行列の逆行列
	// GSmatrix4 inverse() const;
	// この行列の転置行列
	// GSmatrix4 transpose() const;
	// この行列を移動、回転やスケーリングする行列に設定します。
	void setTRS(const GSvector3& pos, const GSquaternion& q, const GSvector3& s);

#endif

} GSmatrix4;

/*----- 矩形構造体 ----------------------------------------------------------*/

typedef struct GSrect
{
	GSfloat			left;			/* 左上隅のｘ座標           */
	GSfloat			top;			/* 左上隅のｙ座標           */
	GSfloat			right;			/* 右下隅のｘ座標           */
	GSfloat			bottom;			/* 右下隅のｙ座標           */

#ifdef __cplusplus
	/** コンストラクタ */
	GSrect( GSfloat l = 0, GSfloat t = 0, GSfloat r = 0, GSfloat b = 0 ) :
		left( l ), top( t ), right( r ), bottom( b )
	{}
#endif

} GSrect;

/*----- カラー型 ------------------------------------------------------------*/

typedef	GSvector4	GScolor4;

#pragma warning(pop)

#endif

/********** End of File ******************************************************/
