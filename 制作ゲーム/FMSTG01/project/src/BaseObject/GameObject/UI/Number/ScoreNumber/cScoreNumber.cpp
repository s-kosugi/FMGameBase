/*==============================================================================*/
/*																				*/
/*	@file title	:	cScoreNumber.cpp											*/
/*  @brief		:	スコア数字オブジェクト										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/13													*/
/*																				*/
/*==============================================================================*/

#include "cScoreNumber.h"
#include "..\..\..\..\..\ScoreManager\cScoreManager.h"

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cScoreNumber::cScoreNumber(IBaseObject* parent) :
	cNumber(parent, "ScoreNumber", "data\\graphic\\DigitalNumber.png"),
	m_nGoalValue( 0 )
{

}

//==========================================================================================
//  デストラクタ
//==========================================================================================
cScoreNumber::~cScoreNumber(void)
{
}

//==========================================================================================
//  初期化
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
//  更新
//==========================================================================================
void cScoreNumber::Update(void)
{
	m_nGoalValue = cScoreManager::GetInstance().GetScore();

	// 表示する値を少しずつ変化させる
	if (m_nValue < m_nGoalValue)
	{
		int changespeed = CHANGE_SPEED;
		// とりあえずあまりにも値が離れていたら変更速度を倍加させる
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
//  解放
//==========================================================================================
IBaseObject* cScoreNumber::Finalize(void)
{
	cNumber::Finalize();
	return this;
}