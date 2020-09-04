#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cRedFairy.h													*/
/*  @brief		:	赤妖精クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/04/23													*/
/*																				*/
/*==============================================================================*/

#include "..\IEnemyBase.h"

//================================================================================================
// 赤妖精クラス
class cRedFairy : public IEnemyBase
{
public:
	cRedFairy(IBaseObject* parent);
	~cRedFairy(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	void Dead( void ) override;

	void StartAttack(void)override;

private:
	
	//--------------------------------------------------------------------------------------------
	// 定数

	// 表示優先度
	static const int	PRIORITY;

	// 移動速度
	static const float	MOVE_SPEED;

	// バウンド用タイマー
	static const float  BOUND_TIME;

	// 出現Y座標差分
	static const int	BOUND_START_POS;

	//--------------------------------------------------------------------------------------------
	// 変数
	float				m_fFrameBuffer;		//	前フレームの移動量の保存バッファ
};
//================================================================================================