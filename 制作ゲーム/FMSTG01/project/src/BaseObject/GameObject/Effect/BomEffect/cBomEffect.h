#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBomEffect.h												*/
/*  @brief		:	爆発エフェクトクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/12													*/
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
	void Update(void);
	IBaseObject* Finalize(void);

private:
	// 定数	
	// 表示優先度
	static const int	PRIORITY = 500;
};
//================================================================================================