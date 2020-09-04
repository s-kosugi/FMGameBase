/*==============================================================================*/
/*																				*/
/*	@file title	:	cHitEffect.cpp												*/
/*  @brief		:	ヒットエフェクトクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/12													*/
/*																				*/
/*==============================================================================*/

#include "cHitEffect.h"
#include "..\cEffectManager.h"

//==========================================================================================
// 定数
//==========================================================================================
const int cHitEffect::PRIORITY = 300;
const float cHitEffect::SCALE = 1.0f;

//==========================================================================================
// コンストラクタ
//==========================================================================================
cHitEffect::cHitEffect(IBaseObject * parent)
	: cEffectObject(parent, "HitEffect", cEffectManager::GetInstance().GetEffectFilename(EFFECT_ID::HIT))
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cHitEffect::~cHitEffect(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cHitEffect::Initialize(void)
{

	SetPriority(PRIORITY);
	SetScale(SCALE);

	cEffectObject::Initialize();
}