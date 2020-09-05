#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cVector3.h													*/
/*  @brief		:	２次元ベクトルクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/03/04													*/
/*																				*/
/*==============================================================================*/

#include <DxLib.h>
//================================================================================================
// ベクトルクラス
class cVector3
{
public:
	float	x;
	float	y;
	float	z;

	
	cVector3(void);
	cVector3(float x, float y);
	cVector3(float x, float y,float z);
	cVector3(const cVector3& v );
	~cVector3();

	//------------------------------------------------------------------------------------
	// オペレーターオーバーロード

	// 代入
	inline  cVector3&   operator=(const cVector3& v)
	{
		x = v.x; y = v.y; z = v.z;
		return *this;
	};
	// 加算
	inline  cVector3&   operator+=(const cVector3& v)
	{
		x += v.x; y += v.y; z += v.z;
		return *this;
	};
	// 減算
	inline  cVector3&   operator-=(const cVector3& v)
	{
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	};
	// 乗算(スカラー倍)
	inline  cVector3&	operator*=(float scalar)
	{
		x *= scalar; y *= scalar; z *= scalar;
		return *this;
	};
	// 等価
	inline	bool		operator==(cVector3 v) const { return ( x == v.x && y == v.y && z == v.z); };
	// 不等
	inline	bool		operator!=(cVector3 v) const { return (x != v.x && y != v.y && z != v.z); };
	// 加算
	inline	cVector3	operator+(const cVector3& v) { 
		cVector3 ret;
		ret.x = x + v.x; ret.y = y + v.y; ret.z = z + v.z;
		return ret;
	};
	// 減算
	inline	cVector3	operator-(const cVector3& v) {
		cVector3 ret;
		ret.x = x - v.x; ret.y = y - v.y; ret.z = z - v.z;
		return ret;
	};
	// 乗算
	inline	cVector3	operator*(const cVector3& v) {
		cVector3 ret;
		ret.x = x * v.x; ret.y = y * v.y; ret.z = z * v.z;
		return ret;
	};
	// 乗算(スカラー倍)
	inline	cVector3	operator*(float scalar) {
		cVector3 ret;
		ret.x = x * scalar; ret.y = y * scalar; ret.z = z * scalar;
		return ret;
	};
	// 除算
	inline	cVector3	operator/(const cVector3& v) {
		cVector3 ret;
		ret.x = x / v.x; ret.y = y / v.y; ret.z = z / v.z;
		return ret;
	};
	// 除算(スカラー)
	inline	cVector3	operator/(float scalar) {
		cVector3 ret;
		ret.x = x / scalar; ret.y = y / scalar; ret.z = z / scalar;
		return ret;
	};
	// 負符号
	inline	cVector3	operator-( void ) {
		return cVector3(-x,-y,-z);
	};

	// キャスト演算子
	// DXLib用のベクトル構造体にキャストする
	operator VECTOR() const { return VECTOR{ x,y,z }; };
	
	//------------------------------------------------------------------------------------
};