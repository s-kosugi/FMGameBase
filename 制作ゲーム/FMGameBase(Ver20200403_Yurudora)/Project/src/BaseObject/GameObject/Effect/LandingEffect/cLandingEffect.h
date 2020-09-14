#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cLandingEffect.h											*/
/*  @brief		:	着地エフェクトクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/04/10													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// 着地エフェクトクラス
class cLandingEffect : public cEffectObject
{
public:
	cLandingEffect(IBaseObject* parent);
	~cLandingEffect(void);

	void Initialize(void);

private:
	// 定数	
	// 表示優先度
	static const int	PRIORITY;
	static const float	SCALE;
};
//================================================================================================