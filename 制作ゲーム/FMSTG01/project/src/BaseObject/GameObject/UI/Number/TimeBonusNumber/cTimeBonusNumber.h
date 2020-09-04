#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cTimeBonusNumber.h											*/
/*  @brief		:	�^�C���{�[�i�X�����I�u�W�F�N�g								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/30													*/
/*																				*/
/*==============================================================================*/

#include "..\cNumber.h"

//================================================================================================
// HP���������N���X
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

	int			m_nGoalValue;		// �ڕW�Ƃ���ׂ����l

	int			m_nCounter;			// 
};
//================================================================================================