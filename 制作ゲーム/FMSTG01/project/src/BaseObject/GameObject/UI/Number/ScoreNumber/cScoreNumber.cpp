/*==============================================================================*/
/*																				*/
/*	@file title	:	cScoreNumber.cpp											*/
/*  @brief		:	�X�R�A�����I�u�W�F�N�g										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/13													*/
/*																				*/
/*==============================================================================*/

#include "cScoreNumber.h"
#include "..\..\..\..\..\ScoreManager\cScoreManager.h"

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cScoreNumber::cScoreNumber(IBaseObject* parent) :
	cNumber(parent, "ScoreNumber", "data\\graphic\\DigitalNumber.png"),
	m_nGoalValue( 0 )
{

}

//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cScoreNumber::~cScoreNumber(void)
{
}

//==========================================================================================
//  ������
//==========================================================================================
void
cScoreNumber::
Initialize(void)
{
	SetPriority(PRIORITY);
	SetDrawColor(0xffccccff);
	cNumber::Initialize();
}

//==========================================================================================
//  �X�V
//==========================================================================================
void cScoreNumber::Update(void)
{
	m_nGoalValue = cScoreManager::GetInstance().GetScore();

	// �\������l���������ω�������
	if (m_nValue < m_nGoalValue)
	{
		int changespeed = CHANGE_SPEED;
		// �Ƃ肠�������܂�ɂ��l������Ă�����ύX���x��{��������
		if( m_nGoalValue > m_nValue + 200)	changespeed *=2;
		if( m_nGoalValue > m_nValue + 600)	changespeed *=2;
		if( m_nGoalValue > m_nValue + 1000)	changespeed *=2;
		if( m_nGoalValue > m_nValue + 2500)	changespeed *=2;

		m_nValue += changespeed;
		if( m_nValue > m_nGoalValue ) m_nValue = m_nGoalValue;
	}
	if (m_nValue > m_nGoalValue)
	{
		m_nValue -= CHANGE_SPEED;
		if( m_nValue < m_nGoalValue ) m_nValue = m_nGoalValue;
	}

	cNumber::Update();
}

//==========================================================================================
//  ���
//==========================================================================================
IBaseObject* cScoreNumber::Finalize(void)
{
	cNumber::Finalize();
	return this;
}