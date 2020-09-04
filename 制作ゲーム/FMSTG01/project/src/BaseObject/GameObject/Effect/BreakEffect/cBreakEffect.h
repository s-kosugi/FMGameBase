#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBreakEffect.h												*/
/*  @brief		:	割れるエフェクトクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/12													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// 割れるエフェクトクラス
class cBreakEffect : public cEffectObject
{
public:
	cBreakEffect(IBaseObject* parent);
	~cBreakEffect(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	// 定数	
	// 表示優先度
	const int	PRIORITY = 2500;
};
//================================================================================================