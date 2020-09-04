#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBossLaserEffect.h											*/
/*  @brief		:	ボスレーザーエフェクトクラス								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/23													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// ボスレーザーエフェクトクラス
class cBossLaserEffect : public cEffectObject
{
public:
	cBossLaserEffect(IBaseObject* parent);
	~cBossLaserEffect(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	// 定数	
	// 表示優先度
	static const int	PRIORITY = 500;
};
//================================================================================================