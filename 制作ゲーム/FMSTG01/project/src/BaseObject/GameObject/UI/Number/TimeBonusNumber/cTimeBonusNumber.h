#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cTimeBonusNumber.h											*/
/*  @brief		:	タイムボーナス数字オブジェクト								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/30													*/
/*																				*/
/*==============================================================================*/

#include "..\cNumber.h"

//================================================================================================
// HP数字数字クラス
class cTimeBonusNumber : public cNumber
{
public:
	cTimeBonusNumber(IBaseObject* parent);
	~cTimeBonusNumber(void);


	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	inline void SetGoalValue(int num) { m_nGoalValue = num; };

	bool IsGoal(void);
private:
	static const int PRIORITY = 2002;
	
	static const int DIGIT_DICISION_TIME = 30;

	int			m_nGoalValue;		// 目標とするべき数値

	int			m_nCounter;			// 
};
//================================================================================================