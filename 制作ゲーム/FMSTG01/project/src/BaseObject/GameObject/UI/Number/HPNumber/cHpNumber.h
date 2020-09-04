#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cHpNumber.h													*/
/*  @brief		:	HP数字オブジェクト											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/07													*/
/*																				*/
/*==============================================================================*/

#include "..\cNumber.h"

//================================================================================================
// HP数字数字クラス
class cHpNumber : public cNumber
{
public:
	cHpNumber(IBaseObject* parent);
	~cHpNumber(void);


	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	const int PRIORITY = 2002;

	const int CHANGE_SPEED = 2; // スコア値が変化していくスピード


	int		  m_nGoalValue;		// 目標とするべき数値
};
//================================================================================================