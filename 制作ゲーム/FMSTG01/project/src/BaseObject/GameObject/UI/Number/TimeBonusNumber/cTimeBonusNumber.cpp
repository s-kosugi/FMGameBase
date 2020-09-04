/*==============================================================================*/
/*																				*/
/*	@file title	:	cTimeBonusNumber.cpp										*/
/*  @brief		:	�^�C���{�[�i�X�����I�u�W�F�N�g								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/30													*/
/*																				*/
/*==============================================================================*/

#include "cTimeBonusNumber.h"
#include "..\..\..\..\..\cGame.h"

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cTimeBonusNumber::cTimeBonusNumber(IBaseObject* parent) :
	cNumber(parent, "TimeBonusNumber", "data\\graphic\\ImpactNumber.png"),
	m_nGoalValue(0),
	m_nCounter(0)
{

}

//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cTimeBonusNumber::~cTimeBonusNumber(void)
{
}

//==========================================================================================
//  ������
//==========================================================================================
void
cTimeBonusNumber::
Initialize(void)
{
	SetPriority(PRIORITY);
	SetDrawColor(COLOR_YELLOW);
	cNumber::Initialize();
}

//==========================================================================================
//  �X�V
//==========================================================================================
void cTimeBonusNumber::Update(void)
{

	m_nCounter++;
	int i = 0;
	// �����ڂ܂ł������_���\�������邩�����肷��
	for (i = m_nMaxDigit; i > 0; i--)
	{
		if (i * DIGIT_DICISION_TIME < m_nCounter)
		{
			break;
		}
	}
	// �����_���Ȓl��\������
	int value = 0;
	for (int j = m_nMaxDigit; j > 0; j--)
	{
		int temp = cGame::Random(0, 9);
		for (int k = j; k > 0; k--) temp *= 10;
		value += temp;
	}
	// ���肵���������O�ɂ���
	for (int j = 0; j < i; j++) value /= 10;
	for (int j = 0; j < i; j++) value *= 10;


	// �ڕW�l�����Z
	int target = m_nGoalValue;
	for (int j = 0; j < i; j++)
	{
		int temp = target % 10;
		for (int k = 0; k < j; k++)
		{
			temp *= 10;
		}
		value += temp;
		target /= 10;
	}

	// �ŏI�\���l���Z�b�g����
	SetValue(value);

	cNumber::Update();
}

//==========================================================================================
//  ���
//==========================================================================================
IBaseObject* cTimeBonusNumber::Finalize(void)
{
	cNumber::Finalize();
	return this;
}

//==========================================================================================
//  �ڕW�l�ɂȂ������ǂ���
//==========================================================================================
bool cTimeBonusNumber::IsGoal(void)
{
	bool ret = false;

	if (DIGIT_DICISION_TIME * m_nMaxDigit <= m_nCounter) ret = true;

	return ret;
}
