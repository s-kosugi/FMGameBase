#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cWarning.h													*/
/*  @brief		:	ワーニングエフェクトクラス									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/27													*/
/*																				*/
/*==============================================================================*/

#include "..\cSpEffectObject.h"

//================================================================================================
// スクフェクトクラス
class cWarning : public cSpEffectObject
{
public:
	cWarning(IBaseObject* parent);
	~cWarning(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:

	int m_nCounter;

	static const int PRIORITY = 900;
};
//================================================================================================