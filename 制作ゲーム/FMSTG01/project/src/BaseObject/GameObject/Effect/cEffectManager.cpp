/*==============================================================================*/
/*																				*/
/*	@file title	:	cEffectManager.cpp											*/
/*  @brief		:	エフェクト管理クラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/12													*/
/*																				*/
/*==============================================================================*/

#include "cEffectManager.h"
#include "HitEffect\cHitEffect.h"
#include "BomEffect\cBomEffect.h"
#include "SmokeEffect\cSmokeEffect.h"
#include "BreakEffect\cBreakEffect.h"
#include "ChargeEffect\cChargeEffect.h"
#include "BossLaser\cBossLaserEffect.h"
#include "BigBomEffect\cBigBomEffect.h"

//==========================================================================================
// 初期化
//==========================================================================================
void cEffectManager::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "EffectManager";

	IBaseObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cEffectManager::Update(void)
{
	IBaseObject::Update();

	// エフェクシアの更新
	UpdateEffekseer2D();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject * cEffectManager::Finalize(void)
{
	IBaseObject::Finalize();
	return nullptr;
}

//==========================================================================================
// 生成
//==========================================================================================
cEffectObject* cEffectManager::Create(EffectID id, cVector2 pos)
{
	cEffectObject* obj = nullptr;
	switch (id)
	{
	case EFFECT_HIT: obj = CreateObject<cHitEffect>(this); break;
	case EFFECT_BOM: obj = CreateObject<cBomEffect>(this); break;
	case EFFECT_SMOKE: obj = CreateObject<cSmokeEffect>(this); break;
	case EFFECT_BREAK: obj = CreateObject<cBreakEffect>(this); break;
	case EFFECT_CHARGE: obj = CreateObject<cChargeEffect>(this); break;
	case EFFECT_BOSSLASER: obj = CreateObject<cBossLaserEffect>(this); break;
	case EFFECT_BIGBOM: obj = CreateObject<cBigBomEffect>(this); break;
	}

	if (obj != nullptr)
	{
		obj->Initialize();
		obj->SetPos(pos);
	}
	return obj;
}
