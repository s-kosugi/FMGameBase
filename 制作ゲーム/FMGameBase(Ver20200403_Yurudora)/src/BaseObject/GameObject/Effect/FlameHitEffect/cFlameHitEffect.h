#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cFlameHitEffect.h											*/
/*  @brief		:	炎攻撃ヒットエフェクトクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/04/10													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// 炎攻撃火っとエフェクトクラス
class cFlameHitEffect : public cEffectObject
{
public:
	cFlameHitEffect(IBaseObject* parent);
	~cFlameHitEffect(void);

	void Initialize(void);

private:
	// 定数	
	// 表示優先度
	static const int	PRIORITY;
	static const float	SCALE;
};
//================================================================================================