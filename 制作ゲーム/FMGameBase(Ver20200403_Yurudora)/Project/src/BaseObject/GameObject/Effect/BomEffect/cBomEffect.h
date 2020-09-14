#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBomEffect.h												*/
/*  @brief		:	爆発エフェクトクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/01/24													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// 爆発エフェクトクラス
class cBomEffect : public cEffectObject
{
public:
	cBomEffect(IBaseObject* parent);
	~cBomEffect(void);

	void Initialize(void);

private:
	// 定数	
	// 表示優先度
	static const int	PRIORITY;
	static const float	SCALE;
};
//================================================================================================