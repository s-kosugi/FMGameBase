/*==============================================================================*/
/*																				*/
/*	@file title	:	cTimeBonusNumber.cpp										*/
/*  @brief		:	タイムボーナス数字オブジェクト								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/30													*/
/*																				*/
/*==============================================================================*/

#include "cTimeBonusNumber.h"
#include "..\..\..\..\..\cGame.h"

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cTimeBonusNumber::cTimeBonusNumber(IBaseObject* parent) :
	cNumber(parent, "TimeBonusNumber", "data\\graphic\\ImpactNumber.png"),
	m_nGoalValue(0),
	m_nCounter(0)
{

}

//==========================================================================================
//  デストラクタ
//==========================================================================================
cTimeBonusNumber::~cTimeBonusNumber(void)
{
}

//==========================================================================================
//  初期化
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
//  更新
//==========================================================================================
void cTimeBonusNumber::Update(void)
{

	m_nCounter++;
	int i = 0;
	// 何桁目までをランダム表示をするかを決定する
	for (i = m_nMaxDigit; i > 0; i--)
	{
		if (i * DIGIT_DICISION_TIME < m_nCounter)
		{
			break;
		}
	}
	// ランダムな値を表示する
	int value = 0;
	for (int j = m_nMaxDigit; j > 0; j--)
	{
		int temp = cGame::Random(0, 9);
		for (int k = j; k > 0; k--) temp *= 10;
		value += temp;
	}
	// 決定した部分を０にする
	for (int j = 0; j < i; j++) value /= 10;
	for (int j = 0; j < i; j++) value *= 10;


	// 目標値を加算
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

	// 最終表示値をセットする
	SetValue(value);

	cNumber::Update();
}

//==========================================================================================
//  解放
//==========================================================================================
IBaseObject* cTimeBonusNumber::Finalize(void)
{
	cNumber::Finalize();
	return this;
}

//==========================================================================================
//  目標値になったかどうか
//==========================================================================================
bool cTimeBonusNumber::IsGoal(void)
{
	bool ret = false;

	if (DIGIT_DICISION_TIME * m_nMaxDigit <= m_nCounter) ret = true;

	return ret;
}
