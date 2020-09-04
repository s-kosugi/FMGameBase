#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cIceAttackEffect.h											*/
/*  @brief		:	氷攻撃エフェクトクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/04/10													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// 氷攻撃エフェクトクラス
class cIceAttackEffect : public cEffectObject
{
public:
	cIceAttackEffect(IBaseObject* parent);
	~cIceAttackEffect(void);

	void Initialize(void);

private:
	// 定数	
	// 表示優先度
	static const int	PRIORITY;
	static const float	SCALE;
};
//================================================================================================