/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnemyBase.cpp												*/
/*  @brief		:	敵ベースクラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "cEnemyBase.h"
#include "..\..\..\ScoreManager\cScoreManager.h"
#include "..\Effect\cEffectManager.h"

//==========================================================================================
// コンストラクタ
//==========================================================================================
cEnemyBase::cEnemyBase(IBaseObject * parent, const std::string object_name, const std::string graphic_file_name)
	: cHitObject(parent, object_name, graphic_file_name),
	m_vPosUp(0.0f,0.0f),
	m_nScore(0)
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cEnemyBase::~cEnemyBase(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cEnemyBase::Initialize(void)
{
	cHitObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cEnemyBase::Update(void)
{
	m_vPos.x += m_vPosUp.x;
	m_vPos.y += m_vPosUp.y;


	switch (m_eState)
	{
	case STATE_HIT:
		// 残りHPを見てオブジェクトの状態を変更する
		if (m_nHp <= 0)
		{
			m_eState = STATE_DEAD;


			// スコア加算
			cScoreManager::GetInstance().AddScore(m_nScore);
			// エフェクトを再生
			cEffectManager::GetInstance().Create(EFFECT_BOM, m_vPos);
		}
		else m_eState = STATE_NORMAL;
		break;
	case STATE_DEAD:
		// オブジェクトの削除をする
		m_eObjectState = OBJECT_STATE_DEAD;
		break;
	}
	cHitObject::Update();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cEnemyBase::Finalize(void)
{
	cHitObject::Finalize();

	return this;
}