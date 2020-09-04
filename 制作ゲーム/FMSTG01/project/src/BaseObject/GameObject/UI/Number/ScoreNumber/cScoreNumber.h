#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cScoreNumber.h												*/
/*  @brief		:	�X�R�A�����I�u�W�F�N�g										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/13													*/
/*																				*/
/*==============================================================================*/

#include "..\cNumber.h"

//================================================================================================
// �X�R�A�����N���X
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

	const int CHANGE_SPEED = 10; // �X�R�A�l���ω����Ă����X�s�[�h


	int		  m_nGoalValue;		// �ڕW�Ƃ���ׂ����l
};
//================================================================================================