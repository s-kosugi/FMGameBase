/*==============================================================================*/
/*																				*/
/*	@file title	:	cScreenFlash.cpp											*/
/*  @brief		:	スクリーン点滅エフェクトクラス								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/27													*/
/*																				*/
/*==============================================================================*/

#include "cScreenFlash.h"
#include "..\..\Enemy\cEnemyManager.h"
#include "..\..\..\..\Utility\utility.h"
#include "..\..\..\..\SoundCtrl\cSoundCtrl.h"
#include "..\cSpEffectManager.h"

//==========================================================================================
// コンストラクタ
//==========================================================================================
cScreenFlash::cScreenFlash(IBaseObject * parent)
	: cSpEffectObject(parent, "ScreenFlhash", "data\\graphic\\white.png"),
	m_nLifeTime( DEFAULT_LIFE_TIME ),
	m_nMaxLifeTime( DEFAULT_LIFE_TIME)
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cScreenFlash::~cScreenFlash(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cScreenFlash::Initialize(void)
{
	m_nMaxLifeTime = m_nLifeTime = DEFAULT_LIFE_TIME;


	cSpEffectObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cScreenFlash::Update(void)
{
	m_nLifeTime--;

	SetAlpha((unsigned int)(((float)m_nLifeTime) / ((float)m_nMaxLifeTime) * 200.0f));

	if( m_nLifeTime <= 0 ) m_eObjectState = OBJECT_STATE_DEAD;

	cSpEffectObject::Update();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cScreenFlash::Finalize(void)
{
	cSpEffectObject::Finalize();

	return this;
}