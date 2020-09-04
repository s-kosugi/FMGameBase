#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cFlameEffect.h												*/
/*  @brief		:	炎攻撃エフェクトクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/04/10													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// 炎攻撃エフェクトクラス
class cFlameEffect : public cEffectObject
{
public:
	cFlameEffect(IBaseObject* parent);
	~cFlameEffect(void);

	void Initialize(void);

private:
	// 定数	
	// 表示優先度
	static const int	PRIORITY;
	static const float	SCALE;
};
//================================================================================================