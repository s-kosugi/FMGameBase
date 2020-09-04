#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cHpNumber.h													*/
/*  @brief		:	HP�����I�u�W�F�N�g											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/07													*/
/*																				*/
/*==============================================================================*/

#include "..\cNumber.h"

//================================================================================================
// HP���������N���X
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

	const int CHANGE_SPEED = 2; // �X�R�A�l���ω����Ă����X�s�[�h


	int		  m_nGoalValue;		// �ڕW�Ƃ���ׂ����l
};
//================================================================================================