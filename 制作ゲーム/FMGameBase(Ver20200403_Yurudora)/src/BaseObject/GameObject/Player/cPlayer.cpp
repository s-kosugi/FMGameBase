/*==============================================================================*/
/*																				*/
/*	@file title	:	cPlayer.cpp													*/
/*  @brief		:	プレイヤークラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "cPlayer.h"
#include "..\..\..\Input\cControllerManager.h"
#include "..\..\..\cGame.h"
#include "..\Effect\cEffectManager.h"
#include "..\Enemy\cEnemyManager.h"
#include "..\..\..\SceneManager\cSceneManager.h"
#include "..\..\..\SceneManager\Scene\GameMain\cGameMain.h"
#include "..\..\..\SoundCtrl\cSoundCtrl.h"

//==========================================================================================
// 定数
//==========================================================================================
const float cPlayer::GRAVITY = 0.98f;
const float cPlayer::START_POS_X = 300.0f;
const float cPlayer::START_POS_Y = 350.0f;
const float cPlayer::JUMP_POWER = 8.0f;

//==========================================================================================
// コンストラクタ
//==========================================================================================
cPlayer::cPlayer( IBaseObject* parent )
	: cSpriteObject( parent, "Player", "data\\graphic\\player_01.png" ),
	m_vPosUp( 0.0f, 0.0f ),
	m_vAccele( 0.0f, 0.0f ),
	m_bLand( false ),
	m_nFailedTimer( 0 )
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cPlayer::~cPlayer( void )
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cPlayer::Initialize( void )
{
	m_vPos = { START_POS_X,START_POS_Y };
	SetPriority( PRIORITY );
	cSpriteObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cPlayer::Update( void )
{
	cGameMain* gm = (cGameMain*)GetParent();

	// ゲームプレイ中にのみプレイヤーの更新
	if( gm->GetGameState() == cGameMain::GAME_STATE::PLAY )
	{
		// 攻撃不能タイマーをカウントする
		if( --m_nFailedTimer <= 0 ) m_nFailedTimer = 0;

		// 攻撃
		Attack();

		// ジャンプ処理
		JumpWalk();

		// 重力落下処理
		if( !m_bLand ) m_vAccele.y = GRAVITY;

		// 移動処理
		m_vPosUp += m_vAccele;
		m_vPos += m_vPosUp;

		// 地面にめり込んだら地上に戻す
		if( m_vPos.y + GetGraphichSize().y / 2 > cGame::GetInstance().GetWindowHeight() - LANDING_LINE )
		{
			m_vPos.y = (float)( cGame::GetInstance().GetWindowHeight() - LANDING_LINE - GetGraphichSize().y / 2 );
			m_bLand = true;
			m_vPosUp.y = 0.0f;
			m_vAccele.y = 0.0f;
		}

		// プレイヤーと敵との当たり判定処理
		cEnemyManager* enm = (cEnemyManager*)FindSibling( "EnemyManager" );
		if( enm )
		{
			if( enm->JudgePlayer( m_vPos, PLAYER_DIST ) )
			{
				// プレイヤーと敵が接触したらゲームオーバー
				cGameMain* gm = (cGameMain*)GetParent();
				gm->SetGameState( cGameMain::GAME_STATE::OVER );
			}
		}
	}

	cSpriteObject::Update();
}
//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cPlayer::Finalize( void )
{
	cSpriteObject::Finalize();

	return this;
}

//==========================================================================================
// ジャンプ移動
//==========================================================================================
void cPlayer::JumpWalk( void )
{
	// キャラクターが地面についたらジャンプをさせる
	if( m_bLand )
	{
		m_vPosUp.y = -JUMP_POWER;
		m_bLand = false;
	}
}

//==========================================================================================
// 攻撃
//==========================================================================================
void cPlayer::Attack( void )
{
	cControllerManager* cm = (cControllerManager*)GetRoot()->FindChild( "ControllerManager" );
	if( cm )
	{
		// 攻撃コマンド実行(攻撃失敗タイマーが1以上の場合は攻撃ができない)
		if( ( cm->CheckTrigger( cControllerManager::KEY_DEFINE::KEY_1 ) ) &&
			m_nFailedTimer <= 0 )
		{
			cVector2 vec = m_vPos;
			vec.x += ATTACK_POS;

			// エフェクト再生
			cEffectManager* efm = (cEffectManager*)GetRoot()->FindChild("EffectManager");
			if( efm ) efm->Create( EFFECT_ID::SLASH, vec );

			// サウンド再生
			cSoundCtrl* sc = (cSoundCtrl*)GetRoot()->FindChild( "SoundCtrl" );
			if( sc ) sc->Play( SOUND_ID::SLASH );

			// 攻撃判定
			cEnemyManager* enm = (cEnemyManager*)FindSibling( "EnemyManager" );
			if( enm )
			{
				if( !enm->JudgeHit( vec, (float)ATTACK_RANGE ) )
				{
					// 攻撃失敗時には攻撃不能タイマーをセットする
					m_nFailedTimer = FAILED_TIME;
				}
			}
		}
	}
}
