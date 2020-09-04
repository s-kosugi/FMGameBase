#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cHPGaugeBefore.h											*/
/*  @brief		:	HPゲージオブジェクト										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/28													*/
/*																				*/
/*==============================================================================*/

#include "..\cUIObject.h"

//================================================================================================
// HPゲージクラス
class cHPGaugeBefore : public cUIObject
{
public:
	cHPGaugeBefore(IBaseObject* parent);
	~cHPGaugeBefore(void);


	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	const int PRIORITY = 2002;
	const float START_ANGLE = 0.0f;
	const float END_ANGLE = 75.0f;
};
//================================================================================================