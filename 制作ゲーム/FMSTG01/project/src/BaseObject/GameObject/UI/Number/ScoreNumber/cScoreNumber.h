#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cScoreNumber.h												*/
/*  @brief		:	スコア数字オブジェクト										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/13													*/
/*																				*/
/*==============================================================================*/

#include "..\cNumber.h"

//================================================================================================
// スコア数字クラス
class cScoreNumber : public cNumber
{
public:
	cScoreNumber(IBaseObject* parent);
	~cScoreNumber(void);


	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	const int PRIORITY = 2002;

	const int CHANGE_SPEED = 10; // スコア値が変化していくスピード


	int		  m_nGoalValue;		// 目標とするべき数値
};
//================================================================================================