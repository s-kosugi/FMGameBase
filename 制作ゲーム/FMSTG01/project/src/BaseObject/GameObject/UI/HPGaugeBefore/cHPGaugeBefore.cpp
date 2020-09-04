/*==============================================================================*/
/*																				*/
/*	@file title	:	cHPGaugeBefore.cpp											*/
/*  @brief		:	HPゲージオブジェクト										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/28													*/
/*																				*/
/*==============================================================================*/

#include "cHPGaugeBefore.h"
#include "..\..\..\GameObject\Player\cPlayer.h"

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cHPGaugeBefore::cHPGaugeBefore(IBaseObject* parent) :
	cUIObject(parent, "HPGaugeBefore", "data\\graphic\\HPGauge.png")
{

}

//==========================================================================================
//  デストラクタ
//==========================================================================================
cHPGaugeBefore::~cHPGaugeBefore(void)
{
}

//==========================================================================================
//  初期化
//==========================================================================================
void
cHPGaugeBefore::
Initialize(void)
{
	m_eSpType = cSprite::SPTYPE_CIRCLEGAUGE;
	m_fStartAngle = START_ANGLE;
	m_fEndAngle = END_ANGLE;
	SetPriority(PRIORITY);

	cUIObject::Initialize();
}

//==========================================================================================
//  更新
//==========================================================================================
void cHPGaugeBefore::Update(void)
{
	cSpriteObject* obj = (cSpriteObject*)FindSibling("HPGauge");
	if (obj)
	{
		SetVisible(true);
		if (m_fStartAngle < obj->GetStartAngle())
		{
			m_fEndAngle = obj->GetStartAngle();
			// ゲージを減らす
			m_fStartAngle += 0.1f;
			if (m_fStartAngle > obj->GetStartAngle())
			{
				m_fStartAngle = obj->GetStartAngle();
			}
			SetDrawColor(COLOR_RED);
		}
		else
		{
			SetVisible(false);
		}
	}
	cUIObject::Update();
}

//==========================================================================================
//  解放
//==========================================================================================
IBaseObject* cHPGaugeBefore::Finalize(void)
{
	cUIObject::Finalize();
	return this;
}