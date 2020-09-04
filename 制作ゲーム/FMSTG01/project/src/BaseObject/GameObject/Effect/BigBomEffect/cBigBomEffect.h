#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBigBomEffect.h												*/
/*  @brief		:	大爆発エフェクトクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/28													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// 大爆発エフェクトクラス
class cBigBomEffect : public cEffectObject
{
public:
	cBigBomEffect(IBaseObject* parent);
	~cBigBomEffect(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	// 定数	
	// 表示優先度
	static const int	PRIORITY = 500;
};
//================================================================================================