#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cHPGauge.h													*/
/*  @brief		:	HPゲージオブジェクト										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/28													*/
/*																				*/
/*==============================================================================*/

#include "..\cUIObject.h"

//================================================================================================
// HPゲージクラス
class cHPGauge : public cUIObject
{
public:
	cHPGauge(IBaseObject* parent);
	~cHPGauge(void);


	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	const int PRIORITY = 2003;
	const float START_ANGLE = 0.0f;		// 0が一番上で100で1週する角度 
	const float END_ANGLE = 75.0f;

	const float EFFECT_START_DIFF = 60.0f;	// エフェクトを表示する位置の差分
};
//================================================================================================