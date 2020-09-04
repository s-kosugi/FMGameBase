#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cVector2.h													*/
/*  @brief		:	２次元ベクトルクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/03/04													*/
/*																				*/
/*==============================================================================*/

#include <DxLib.h>
#include <math.h>
//================================================================================================
// ベクトルクラス
class cVector2
{
public:
	float	x;
	float	y;


	cVector2(void);
	cVector2(float x, float y);
	cVector2(const cVector2& v);
	~cVector2();

	// 2点間の距離
	// pos , tpos 求めたい２点間
	// return : 距離
	inline float CalsTwoPointDist(const cVector2& pos, const cVector2& tpos) { return (float)sqrt((tpos.x - pos.x) * (tpos.x - pos.x) + (tpos.y - pos.y) * (tpos.y - pos.y)) ;};

	// 2点間の距離
	// pos : 求めたい対象の位置
	// return : 距離
	inline float CalsTwoPointDist(const cVector2& pos) { return (float)sqrt((pos.x - x) * (pos.x - x) + (pos.y - y) * (pos.y - y)) ;};
	
	// 2点間の角度
	// pos , tpos 求めたい２点間
	// return : ラジアン値
	float CalcTwoPointAngle(const cVector2& pos, const cVector2& tpos);

	// 2点間の角度(自身の位置との差)
	// pos : 求めたい対象の位置
	// return : ラジアン値
	float CalcTwoPointAngle(const cVector2& pos);

	// 内積
	// pos , tpos 内積を求める２つのベクトル
	inline float DotProduct(const cVector2& pos, const cVector2& tpos) { return pos.x * tpos.x + pos.y * tpos.y;};

	// 内積
	// pos : 自身と内積を求めるベクトル
	inline float DotProduct(const cVector2 & pos) { return pos.x * x + pos.y * y; };

	//------------------------------------------------------------------------------------
	// オペレーターオーバーロード

	// 代入
	inline  cVector2&   operator=(const cVector2& v)
	{
		x = v.x; y = v.y;
		return *this;
	};
	// 加算
	inline  cVector2&   operator+=(const cVector2& v)
	{
		x += v.x; y += v.y;
		return *this;
	};
	// 減算
	inline  cVector2&   operator-=(const cVector2& v)
	{
		x -= v.x; y -= v.y;
		return *this;
	};
	// 乗算(スカラー倍)
	inline  cVector2&	operator*=(float scalar)
	{
		x *= scalar; y *= scalar;
		return *this;
	};
	inline	bool		operator==(cVector2 v) const { return (x == v.x && y == v.y); };	// 等価
	inline	bool		operator!=(cVector2 v) const { return (x != v.x && y != v.y); };	// 不等
	// 加算
	inline	cVector2	operator+(const cVector2& v) {
		cVector2 ret;
		ret.x = x + v.x; ret.y = y + v.y;
		return ret;
	};
	// 減算
	inline	cVector2	operator-(const cVector2& v) {
		cVector2 ret;
		ret.x = x - v.x; ret.y = y - v.y;
		return ret;
	};
	// 乗算
	inline	cVector2	operator*(const cVector2& v) {
		cVector2 ret;
		ret.x = x * v.x; ret.y = y * v.y;
		return ret;
	};
	// 乗算(スカラー倍)
	inline	cVector2	operator*(float scalar) {
		cVector2 ret;
		ret.x = x * scalar; ret.y = y * scalar;
		return ret;
	};
	// 除算
	inline	cVector2	operator/(const cVector2& v) {
		cVector2 ret;
		ret.x = x / v.x; ret.y = y / v.y;
		return ret;
	};
	// 除算(スカラー)
	inline	cVector2	operator/(float scalar) {
		cVector2 ret;
		ret.x = x / scalar; ret.y = y / scalar;
		return ret;
	};
	// 負符号
	inline	cVector2	operator-(void) {
		return cVector2(-x, -y);
	};

	// キャスト演算子
	// DXLib用のベクトル構造体にキャストする
	operator VECTOR() const { return VECTOR{ x,y,0.0f }; };

	//------------------------------------------------------------------------------------
};