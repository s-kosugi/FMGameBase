#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cRedFairyDead.h												*/
/*  @brief		:	赤妖精死亡エフェクト										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/04/05													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\cSpriteObject.h"

//================================================================================================
// 赤妖精死亡エフェクトクラス
class cRedFairyDead : public cSpriteObject
{
public:
	cRedFairyDead( IBaseObject* parent );
	~cRedFairyDead( void );

	void Initialize( const cVector2& pos );
	void Update( void );

private:

	// 移動量
	cVector2		m_vPosUp;


	//--------------------------------------------------------------------------------------------
	// 定数

	// 表示優先度
	static const int	PRIORITY;

	// 表示時間
	static const float	LIFE_TIME;

	// 最大移動速度
	static const float  MAX_SPEED;
	// 最小移動速度
	static const float  MIN_SPEED;

	// 点滅間隔
	static const float  FLASH_INTERVAL;

	//--------------------------------------------------------------------------------------------

};
//================================================================================================