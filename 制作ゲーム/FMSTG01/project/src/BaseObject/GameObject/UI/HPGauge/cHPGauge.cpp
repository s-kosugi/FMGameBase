/*==============================================================================*/
/*																				*/
/*	@file title	:	cHPGauge.cpp												*/
/*  @brief		:	HPゲージオブジェクト										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/28													*/
/*																				*/
/*==============================================================================*/

#include "cHPGauge.h"
#include "..\..\..\GameObject\Player\cPlayer.h"
#include "..\..\Effect\cEffectManager.h"
#include "..\..\..\..\Utility\utility.h"

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cHPGauge::cHPGauge(IBaseObject* parent) :
	cUIObject(parent, "HPGauge", "data\\graphic\\HPGauge.png")
{

}

//==========================================================================================
//  デストラクタ
//==========================================================================================
cHPGauge::~cHPGauge(void)
{
}

//==========================================================================================
//  初期化
//==========================================================================================
void
cHPGauge::
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
void cHPGauge::Update(void)
{
	cPlayer* pl = (cPlayer*)GetParent()->FindSibling("Player");
	if (pl)
	{
		float afterangle= END_ANGLE - ((float)pl->GetHp()) / ((float)pl->GetMaxHp()) * m_fEndAngle;
		if (afterangle != m_fStartAngle)
		{
			cVector2 effectPos = m_vPos;
			// 100%→360度に変換
			float angle = m_fStartAngle * 3.6f;
			// 角度を上から起点にする
			angle -= 90.0f;
			effectPos.x = effectPos.x + cos(DEG_TO_RAD(angle)) * EFFECT_START_DIFF;
			effectPos.y = effectPos.y + sin(DEG_TO_RAD(angle)) * EFFECT_START_DIFF;
			cEffectObject* obj = cEffectManager::GetInstance().Create(EFFECT_BREAK, effectPos);
			obj->SetDrawColor(COLOR_RED);

			m_fStartAngle = afterangle;
		}
	}
	cUIObject::Update();
}

//==========================================================================================
//  解放
//==========================================================================================
IBaseObject* cHPGauge::Finalize(void)
{
	cUIObject::Finalize();
	return this;
}