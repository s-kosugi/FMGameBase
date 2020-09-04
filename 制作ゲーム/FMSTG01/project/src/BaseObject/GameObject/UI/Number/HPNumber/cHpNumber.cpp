/*==============================================================================*/
/*																				*/
/*	@file title	:	cHpNumber.cpp												*/
/*  @brief		:	HP数字オブジェクト											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/07													*/
/*																				*/
/*==============================================================================*/

#include "cHpNumber.h"
#include "..\..\..\Player\cPlayer.h"

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cHpNumber::cHpNumber(IBaseObject* parent) :
	cNumber(parent, "HpNumber", "data\\graphic\\DigitalNumber.png"),
	m_nGoalValue(0)
{

}

//==========================================================================================
//  デストラクタ
//==========================================================================================
cHpNumber::~cHpNumber(void)
{
}

//==========================================================================================
//  初期化
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
//  更新
//==========================================================================================
void cHpNumber::Update(void)
{
	cPlayer* player = (cPlayer*)GetParent()->FindSibling("Player");
	if (player)
	{
		m_nGoalValue = player->GetHp();

		// 表示する値を少しずつ変化させる
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
//  解放
//==========================================================================================
IBaseObject* cHpNumber::Finalize(void)
{
	cNumber::Finalize();
	return this;
}