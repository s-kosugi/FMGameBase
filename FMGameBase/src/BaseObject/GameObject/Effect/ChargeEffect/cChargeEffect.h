#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cChargeEffect.h												*/
/*  @brief		:	チャージエフェクトクラス									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/01/24													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// チャージエフェクトクラス
class cChargeEffect : public cEffectObject
{
public:
	cChargeEffect(IBaseObject* parent);
	~cChargeEffect(void);

	void Initialize(void) override;

private:
	// 定数	
	// 表示優先度
	static const int	PRIORITY;
	static const float	SCALE;
};
//================================================================================================