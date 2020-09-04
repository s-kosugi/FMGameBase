#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBlueFairy.h												*/
/*  @brief		:	青妖精クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/04/23													*/
/*																				*/
/*==============================================================================*/

#include "..\IEnemyBase.h"

//================================================================================================
// 青妖精クラス
class cBlueFairy : public IEnemyBase
{
public:
	cBlueFairy(IBaseObject* parent);
	~cBlueFairy(void);

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

	// 攻撃座標の補正値
	static const float	ATTACK_POSY;

	//--------------------------------------------------------------------------------------------

};
//================================================================================================