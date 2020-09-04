#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cScreenFlash.h												*/
/*  @brief		:	スクリーン点滅クラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/27													*/
/*																				*/
/*==============================================================================*/

#include "..\cSpEffectObject.h"

//================================================================================================
// スクリーン点滅エフェクトクラス
class cScreenFlash : public cSpEffectObject
{
public:
	cScreenFlash(IBaseObject* parent);
	~cScreenFlash(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	int m_nLifeTime;
	int m_nMaxLifeTime;

	const int DEFAULT_LIFE_TIME = 20;

};
//================================================================================================