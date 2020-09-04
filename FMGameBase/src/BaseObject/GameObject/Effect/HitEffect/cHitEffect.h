#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cHitEffect.h												*/
/*  @brief		:	ショットヒットエフェクトクラス								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/12													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// ショットヒットエフェクトクラス
class cHitEffect : public cEffectObject
{
public:
	cHitEffect(IBaseObject* parent);
	~cHitEffect(void);

	void Initialize(void);

private:
	// 定数	
	// 表示優先度
	static const int	PRIORITY;
	static const float	SCALE;
};
//================================================================================================