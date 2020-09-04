#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cHPGaugeFrame.h												*/
/*  @brief		:	HPゲージ枠オブジェクト										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/28													*/
/*																				*/
/*==============================================================================*/

#include "..\cUIObject.h"

//================================================================================================
// HPゲージ枠クラス
class cHPGaugeFrame : public cUIObject
{
public:
	cHPGaugeFrame(IBaseObject* parent);
	~cHPGaugeFrame(void);


	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	static const int PRIORITY = 2001;
};
//================================================================================================