/*==============================================================================*/
/*																				*/
/*	@file title	:	cRedFairy.cpp												*/
/*  @brief		:	赤妖精クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/04/23													*/
/*																				*/
/*==============================================================================*/

#include "cRedFairy.h"
#include "cGame.h"
#include "SceneManager/Scene/GameMain/cGameMain.h"
#include "..\..\SpEffect\cSpEffectManager.h"
#include "SoundCtrl/cSoundCtrl.h"
#include "Utility/Timer/cTimer.h"
#include "Utility/Easing/Easing.h"
#include "BaseObject/GameObject/Effect/cEffectManager.h"

//==========================================================================================
// 定数
//==========================================================================================
const int	cRedFairy::PRIORITY = 200;
const float cRedFairy::MOVE_SPEED = 8.0f;
const float cRedFairy::BOUND_TIME = 1.5f;
const int	cRedFairy::BOUND_START_POS = 400;

//==========================================================================================
// コンストラクタ
//==========================================================================================
cRedFairy::cRedFairy(IBaseObject* parent)
	: IEnemyBase(parent, "RedFairy", "data\\graphic\\enemy_01.png")
	, m_fFrameBuffer(0.0f)
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cRedFairy::~cRedFairy(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cRedFairy::Initialize(void)
{
	cGame* game = (cGame*)GetRoot();
	cGameMain* gm = (cGameMain*)GetParent()->GetParent();

	if( gm )
	{
		m_vPos = { (float)game->GetWindowWidth() + GetGraphichSize().x / 2,
			(float)game->GetWindowHeight() - GetGraphichSize().y / 2 - gm->GetLandingLine() };
	}
	SetPriority(PRIORITY);
	IEnemyBase::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cRedFairy::Update(void)
{
	m_vPosUp.x = -MOVE_SPEED;

	// 敵をバウンドさせる動き
	cTimer* timer = (cTimer*)FindChild( "BounceTimer" );
	if( !timer ){
		timer = CreateObject<cTimer>( this, "BounceTimer" );
		timer->Setup( BOUND_TIME );
	}
	cGameMain* gm = (cGameMain*)GetParent()->GetParent();
	cGame* game = (cGame*)GetRoot();
	if( gm && !timer->Finished())
	{
		float oldPosY = m_vPos.y;

		// 着地点を計算する
		float targetPos = game->GetWindowHeight() - GetGraphichSize().y / 2.0f - gm->GetLandingLine();
		m_vPos.y = Easing::OutBounce( timer->GetTime(), timer->GetLimit(), targetPos, targetPos - BOUND_START_POS );

		// 着地エフェクトを表示
		if ( m_fFrameBuffer > 0 && m_vPos.y - oldPosY < 0)
		{
			cEffectManager* em = (cEffectManager*)GetRoot()->FindChild("EffectManager");
			cVector2 efPos(m_vPos);
			efPos.x -= 140.0f;
			efPos.y += 240.0f;
			if (em) em->Create(EFFECT_ID::LANDING, efPos);

		}

		// 前フレームからの差分を記憶する。
		m_fFrameBuffer = m_vPos.y - oldPosY;

	}
	IEnemyBase::Update();
}
//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cRedFairy::Finalize(void)
{
	IEnemyBase::Finalize();

	return this;
}
//==========================================================================================
// 死亡処理
//==========================================================================================
void cRedFairy::Dead( void )
{
	// 死亡エフェクトを生成
	cSpEffectManager* se = (cSpEffectManager*)GetParent()->FindSibling( "SpEffectManager" );
	if( se ) se->Create( SpEffectID::REDFAIRY_DEAD, m_vPos );

	DeleteObject();
}
//==========================================================================================
// 攻撃開始処理
//==========================================================================================
void cRedFairy::StartAttack(void)
{
	// エフェクト生成位置算出
	cVector2 vec = m_vPos;
	vec.x -= ATTACK_POS + 80;
	//vec.y += ATTACK_POSY;

	// 攻撃エフェクト生成
	cEffectManager* em = (cEffectManager*)GetRoot()->FindChild("EffectManager");
	if (em)
	{
		em->Create(EFFECT_ID::FLAME, vec);
		//em->Create(EFFECT_ID::FLAME_HIT, vec);
	}

	cSoundCtrl::GetInstance().Play(SOUND_ID::FIRE);
}
