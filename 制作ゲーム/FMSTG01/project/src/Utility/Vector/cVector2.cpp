/*==============================================================================*/
/*																				*/
/*	@file title	:	cVector2.cpp												*/
/*  @brief		:	２次元ベクトルクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/03/04													*/
/*																				*/
/*==============================================================================*/

#include "cVector2.h"
#include "..\utility.h"

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cVector2::cVector2(void) :
	x(0.0f), y(0.0f)
{
}
//==========================================================================================
//  コンストラクタ
//  x : x成分
//  y : y成分
//==========================================================================================
cVector2::cVector2(float x, float y) :
	x(x), y(y)
{
}
//==========================================================================================
//  コンストラクタ
//  v : ベクトル
//==========================================================================================
cVector2::cVector2(const cVector2 & v) :
	x(v.x), y(v.y)
{
}
//==========================================================================================
//  デストラクタ
//==========================================================================================
cVector2::~cVector2()
{
}
//==========================================================================================
//  ２点間の角度
//  pos , tpos 求めたい２点間
//  return : ラジアン値
//==========================================================================================
float cVector2::CalcTwoPointAngle(const cVector2& pos, const cVector2& tpos)
{
	float r = (float)atan2((double)tpos.y - pos.y, (double)tpos.x - pos.x);
	if (r < 0) r = r + 2 * 3.1415f;
	return RAD_TO_DEG(r);
}
//==========================================================================================
//  ２点間の角度
// pos : 求めたい対象の位置
//  return : ラジアン値
//==========================================================================================
float cVector2::CalcTwoPointAngle(const cVector2& pos)
{
	float r = (float)atan2(pos.y - y, pos.x - x);
	if (r < 0) r = r + 2 * 3.1415f;
	return RAD_TO_DEG(r);
}
