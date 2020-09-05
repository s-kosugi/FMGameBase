#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cGetScoreEffect.h											*/
/*  @brief		:	スコア取得エフェクトクラス									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/04/07													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// スコア取得エフェクトクラス
class cGetScoreEffect : public cEffectObject
{
public:
	cGetScoreEffect(IBaseObject* parent);
	~cGetScoreEffect(void);

	void Initialize(void) override;
	void Update(void) override;

private:
	// 定数	
	// 表示優先度
	static const int	PRIORITY;
	static const float	SCALE;
};
//================================================================================================