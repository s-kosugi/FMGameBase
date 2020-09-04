/*==============================================================================*/
/*																				*/
/*	@file title	:	cHpNumber.cpp												*/
/*  @brief		:	HP�����I�u�W�F�N�g											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/07													*/
/*																				*/
/*==============================================================================*/

#include "cHpNumber.h"
#include "..\..\..\Player\cPlayer.h"

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cHpNumber::cHpNumber(IBaseObject* parent) :
	cNumber(parent, "HpNumber", "data\\graphic\\DigitalNumber.png"),
	m_nGoalValue(0)
{

}

//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cHpNumber::~cHpNumber(void)
{
}

//==========================================================================================
//  ������
//==========================================================================================
void
cHpNumber::
Initialize(void)
{
	SetPriority(PRIORITY);
	SetDrawColor(COLOR_YELLOW);
	cNumber::Initialize();
}

//==========================================================================================
//  �X�V
//==========================================================================================
void cHpNumber::Update(void)
{
	cPlayer* player = (cPlayer*)GetParent()->FindSibling("Player");
	if (player)
	{
		m_nGoalValue = player->GetHp();

		// �\������l���������ω�������
		if (m_nValue < m_nGoalValue)
		{
			m_nValue += CHANGE_SPEED;
			if (m_nValue > m_nGoalValue) m_nValue = m_nGoalValue;
		}
		if (m_nValue > m_nGoalValue)
		{
			m_nValue -= CHANGE_SPEED;
			if (m_nValue < m_nGoalValue) m_nValue = m_nGoalValue;
		}

	}
	cNumber::Update();
}

//==========================================================================================
//  ���
//==========================================================================================
IBaseObject* cHpNumber::Finalize(void)
{
	cNumber::Finalize();
	return this;
}