/*==============================================================================*/
/*																				*/
/*	@file title	:	cTargetEffect.cpp											*/
/*  @brief		:	ターゲットエフェクトクラス									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/24													*/
/*																				*/
/*==============================================================================*/

#include "cTargetEffect.h"
#include "..\..\Enemy\cEnemyManager.h"
#include "..\..\..\..\Utility\utility.h"
#include "..\..\..\..\SoundCtrl\cSoundCtrl.h"
#include "..\cSpEffectManager.h"

//==========================================================================================
// コンストラクタ
//==========================================================================================
cTargetEffect::cTargetEffect(IBaseObject * parent)
	: cSpEffectObject(parent, "Target", "data\\graphic\\target01.png"),
	m_pTargetObj( nullptr ),
	m_nLifeTime(LIFE_TIME),
	m_pCircleSprite( nullptr ),
	m_eAnimState(TG_APPEAR)
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cTargetEffect::~cTargetEffect(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cTargetEffect::Initialize(void)
{
	m_pTargetObj = nullptr;
	m_eAnimState = TG_APPEAR;

	SetPriority(PRIORITY);
	m_BlendMode = DX_BLENDMODE_ADD;
	m_nColor = SPRITE_COLOR;

	SetScale(SCALE_RATE);
	SetAlpha( 0 );

	m_pCircleSprite = CreateDrawObject<cSpriteObject>(this,"TargetCircle","data\\graphic\\target02.png");

	// ターゲットサイトの円部分の設定
	if (m_pCircleSprite)
	{
		m_pCircleSprite->SetDrawColor(SPRITE_COLOR);
		m_pCircleSprite->SetPriority(GetPriority());
		m_pCircleSprite->SetBlendMode(DX_BLENDMODE_ADD);
		m_pCircleSprite->SetScale( 0.0f );
	}

	cSoundCtrl::GetInstance().Play(SOUND_LOCK);
	cSpEffectObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cTargetEffect::Update(void)
{
	
	m_fAngle += ANGLE_ADD;

	switch (m_eAnimState)
	{
	case TG_APPEAR:
		Appear();
		break;
	case TG_FLASH:
		Flash();
		break;
	case TG_NORMAL:
		Normal();
		break;

	}

	// 円部分のスプライトの更新
	if (m_pCircleSprite)
	{
		m_pCircleSprite->SetAngle(m_pCircleSprite->GetAngle() - ANGLE_ADD);
		m_pCircleSprite->SetPos(m_vPos);
	}

	// 時間経過で消滅
	m_nLifeTime--;
	if (m_nLifeTime <= 0)
	{
		m_eObjectState = OBJECT_STATE_DEAD;
		m_bVisible = false;
	}

	// 追尾対象が生きていれば追尾する
	if (IsSearchTargetAlive()) {
		m_vPos = m_pTargetObj->GetPos();
	} else
	{
		m_eObjectState = OBJECT_STATE_DEAD;
		m_bVisible = false;
	}

	cSpEffectObject::Update();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cTargetEffect::Finalize(void)
{
	cSpEffectObject::Finalize();

	return this;
}

//==========================================================================================
// 追尾対象が生きているかどうか
//==========================================================================================
bool cTargetEffect::IsSearchTargetAlive(void)
{
	for (auto it = cEnemyManager::GetInstance().GetChildList()->begin(); it != cEnemyManager::GetInstance().GetChildList()->end(); it++)
	{
		if (m_pTargetObj == (cSpriteObject*)*it) return true;
	}
	if((cSpriteObject*)m_pParentObject->FindSibling("Player") == m_pTargetObj) return true;

	return false;
}
//==========================================================================================
// 追尾対象の重複チェック
// pObj : 重複対象のオブジェクト
// return true : 重複 false : 重複なし
//==========================================================================================
bool cTargetEffect::CheckDupulication(cSpriteObject* pObj)
{
	
	// 重複して同じ対象に出しているかを調べる
	for (auto it = cSpEffectManager::GetInstance().GetChildList()->begin(); it != cSpEffectManager::GetInstance().GetChildList()->end(); it++)
	{
		if (((cSpriteObject*)*it)->GetObjectName() == "Target")
		{
			if (pObj == ((cTargetEffect*)*it)->GetTargetObject())
			{
				return true;
			}
		}
	}
	return false;

}

//==========================================================================================
// 出現時処理
//==========================================================================================
void cTargetEffect::Appear(void)
{
	unsigned int alpha = GetAlpha() + ALPHA_MAX / APPEAR_TIME;

	SetAlpha(alpha);
	SetScale(GetScale().x - SCALE_RATE / APPEAR_TIME);

	if (alpha > ALPHA_MAX) SetAlpha(ALPHA_MAX);
	if (GetScale().x < 1.0f) SetScale(1.0f);

	// 円部分の処理
	if (m_pCircleSprite)
	{
		m_pCircleSprite->SetScale(m_pCircleSprite->GetScale().x + CIRCLE_SCALE_MAX / APPEAR_TIME);
		if(m_pCircleSprite->GetScale().x > CIRCLE_SCALE_MAX) m_pCircleSprite->SetScale(CIRCLE_SCALE_MAX);
	}

	// 次の状態へ移行
	if (m_nLifeTime <= LIFE_TIME - APPEAR_TIME)
	{
		SetAlpha(ALPHA_MAX);
		SetScale(1.0f);
		m_eAnimState = TG_FLASH;
		// ターゲットロックオン状態で色を変更
		if(m_pCircleSprite) m_pCircleSprite->SetDrawColor(CIRCLE_DICISION_COLOR);
	}
}
//==========================================================================================
// 点滅時処理
//==========================================================================================
void cTargetEffect::Flash(void)
{
	float angle = 360.0f / FLASH_INTERVAL * (float)(m_nLifeTime % FLASH_INTERVAL + 1);
	float theta = sin(DEG_TO_RAD(angle));
	unsigned int alpha = (unsigned int)((theta + 1.0f) * 127.5f);
	SetAlpha(alpha);

	// 円部分の処理
	if (m_pCircleSprite)
	{
		//m_pCircleSprite->SetAlpha(alpha);
		angle = 360.0f / CIRCLE_SCALE_INTERVAL * (float)(m_nLifeTime % CIRCLE_SCALE_INTERVAL + 1);
		theta = sin(DEG_TO_RAD(angle));
		m_pCircleSprite->SetScale(CIRCLE_SCALE_MAX + theta * CIRCLE_SCALE_RANGE);
	}
	// 次の状態へ移行
	if (m_nLifeTime <= LIFE_TIME - APPEAR_TIME - FLASH_TIME)
	{
		if(m_pCircleSprite) m_pCircleSprite->SetAlpha(ALPHA_MAX);
		SetAlpha(ALPHA_MAX);
		m_eAnimState = TG_NORMAL;
	}
}
//==========================================================================================
// 通常自処理
//==========================================================================================
void cTargetEffect::Normal(void)
{
}
