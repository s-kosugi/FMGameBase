#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cChargeEffect.h												*/
/*  @brief		:	チャージエフェクトクラス									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/22													*/
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

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	// 定数	
	// 表示優先度
	static const int	PRIORITY = 300;
};
//================================================================================================