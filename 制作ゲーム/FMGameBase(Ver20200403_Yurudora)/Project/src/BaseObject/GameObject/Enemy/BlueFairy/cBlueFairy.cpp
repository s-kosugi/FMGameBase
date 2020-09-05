/*==============================================================================*/
/*																				*/
/*	@file title	:	cBlueFairy.cpp												*/
/*  @brief		:	青妖精クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/04/23													*/
/*																				*/
/*==============================================================================*/

#include "cBlueFairy.h"
#include "cGame.h"
#include "SceneManager/Scene/GameMain/cGameMain.h"
#include "..\..\SpEffect\cSpEffectManager.h"
#include "..\..\Effect\cEffectManager.h"
#include "SoundCtrl/cSoundCtrl.h"
#include "Utility/Timer/cTimer.h"
#include "Utility/Easing/Easing.h"

//==========================================================================================
// 定数
//==========================================================================================
const int	cBlueFairy::PRIORITY = 200;
const float cBlueFairy::MOVE_SPEED = 8.0f;
const float cBlueFairy::ATTACK_POSY = 250.0f;

//==========================================================================================
// コンストラクタ
//==========================================================================================
cBlueFairy::cBlueFairy(IBaseObject * parent)
	: IEnemyBase(parent, "BlueFairy", "data\\graphic\\enemy_02.png")
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cBlueFairy::~cBlueFairy(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cBlueFairy::Initialize(void)
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
void cBlueFairy::Update(void)
{
	m_vPosUp.x = -MOVE_SPEED;

	// 敵をゆらゆらさせる動き
	cTimer* timer = (cTimer*)FindChild( "SwingTimer" );
	if( !timer ){
		timer = CreateObject<cTimer>( this, "SwingTimer" );
		timer->Setup( 1.0f );
	}
	if( timer->Finished() ) timer->Reset();
	if( timer->GetLimit() / 2.0f < timer->GetTime() )
		m_vPosUp.y = Easing::InCubic( timer->GetTime(), timer->GetLimit(), 3.0f, -3.0f );
	else
		m_vPosUp.y = Easing::OutCubic( timer->GetTime(), timer->GetLimit(), -3.0f, 3.0f );

	IEnemyBase::Update();
}
//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cBlueFairy::Finalize(void)
{
	IEnemyBase::Finalize();

	return this;
}
//==========================================================================================
// 死亡処理
//==========================================================================================
void cBlueFairy::Dead( void )
{
	// 死亡エフェクトを生成
	cSpEffectManager* se = (cSpEffectManager*)GetParent()->FindSibling( "SpEffectManager" );
	if( se ) se->Create( SpEffectID::BLUEFAIRY_DEAD, m_vPos );

	DeleteObject();
}

//==========================================================================================
// 攻撃開始処理
//==========================================================================================
void cBlueFairy::StartAttack(void)
{
	// エフェクト生成位置算出
	cVector2 vec = m_vPos;
	vec.x -= ATTACK_POS;
	vec.y += ATTACK_POSY;

	// 攻撃エフェクト生成
	cEffectManager* em = (cEffectManager*)GetRoot()->FindChild("EffectManager");
	if (em) em->Create(EFFECT_ID::ICEATTACK, vec);

	cSoundCtrl::GetInstance().Play(SOUND_ID::ICE);
	cSoundCtrl::GetInstance().Play(SOUND_ID::WIND);
}
