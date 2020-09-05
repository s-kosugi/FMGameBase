/*==============================================================================*/
/*																				*/
/*	@file title	:	cGameMain.cpp												*/
/*  @brief		:	ゲームメインシーン											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\cGame.h"
#include "cGameMain.h"
#include "..\..\cSceneManager.h"
#include "Input\Keyboard\cKeyboard.h"
#include "BaseObject/GameObject/Enemy/cEnemyManager.h"
#include "BaseObject/cSurfaceObject.h"
#include "BaseObject/cTransitionObject.h"

#include "BaseObject\GameObject\Player\cPlayer.h"
#include "BaseObject/GameObject/BackGround/cBackGround.h"
#include "Utility/Timer/cTimer.h"
#include "Utility/Easing/Easing.h"
#include "ScoreManager/cScoreManager.h"
#include "BaseObject/GameObject/UI/cUIManager.h"
#include "BaseObject/GameObject/SpEffect/cSpEffectManager.h"
#include "SoundCtrl/cSoundCtrl.h"


//==========================================================================================
// 定数
//==========================================================================================
const float cGameMain::LEVELUP_TIME  = 10.0f;	// 難易度が上がるまでの時間(秒)
const int cGameMain::MAX_DIFFICULT	 = 10;		// 最大難易度
const float cGameMain::GAMEOVER_TIME = 4.0f;	// ゲームオーバー状態の時間(秒)
const int cGameMain::LANDING_LINE = 100;		// 地面の高さ
const float cGameMain::GAMESTART_TIME = 1.5f;	// ゲームスタート状態の時間(秒)

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cGameMain::cGameMain(IBaseObject * parent)
	: IBaseScene(parent, "GameMain")
	, m_nDifficult(0)
	, m_eGameState(GAME_STATE::START)
{
}
//==========================================================================================
//  デストラクタ
//==========================================================================================
cGameMain::~cGameMain(void)
{
}
//==========================================================================================
//  初期化
//==========================================================================================
void cGameMain::Initialize(void)
{
	// 背景の生成
	cBackGround* obj = CreateObject<cBackGround>( this );
	obj->SetPos( 0.0f, (float)cGame::GetInstance().GetWindowHeight() / 2 );
	obj = CreateObject<cBackGround>( this );
	obj->SetPos( (float)cGame::GetInstance().GetWindowWidth(), (float)cGame::GetInstance().GetWindowHeight() / 2 );

	// プレイヤーキャラクターの生成
	CreateObject<cPlayer>(this);

	// 敵管理クラスの生成
	CreateObject<cEnemyManager>(this);

	// スコアの初期化
	cScoreManager* sm = (cScoreManager*)GetRoot()->FindChild("ScoreManager");
	if( sm ) sm->ResetScore();

	// スプライトエフェクト管理クラスの生成
	CreateObject<cSpEffectManager>(this);

	// UI管理クラスの生成
	cUIManager* um = CreateObject<cUIManager>(this);
	// スコアボード」の生成
	um->Create( UIID::SCORE_BOARD, { 150, 100 } );

	

	IBaseObject::Initialize();
}
//==========================================================================================
//  更新
//==========================================================================================
void cGameMain::Update(void)
{
	IBaseObject::Update();

	// ゲームモード中の各状態処理
	switch( m_eGameState )
	{
	case GAME_STATE::START: Start(); break;
	case GAME_STATE::PLAY: Play(); break;
	case GAME_STATE::OVER: Over(); 	break;
	}
}
//==========================================================================================
//  破棄
//==========================================================================================
IBaseObject* cGameMain::Finalize(void)
{
	IBaseObject::Finalize();
	return this;
}

//==========================================================================================
//  ゲーム開始状態
//==========================================================================================
void cGameMain::Start(void)
{
	cTimer* timer = (cTimer*)FindChild("StartTimer");
	cTimer* seTimer = (cTimer*)FindChild("SETimer");
	cSpriteObject* startLogo = (cSpriteObject*)FindChild("StartLogo");
	cGame* game = (cGame*)GetRoot();
	if (!timer)
	{
		// ゲームスタートタイマーの作成
		timer = CreateObject<cTimer>(this, "StartTimer");
		timer->Setup(GAMESTART_TIME);

		// SE再生開始タイマーの作成
		seTimer = CreateObject<cTimer>(this, "SETimer");
		seTimer->Setup(0.5f);

		
		if (!startLogo)
		{
			startLogo = CreateDrawObject<cSpriteObject>(this, "StartLogo", "data\\graphic\\start.png");
			startLogo->SetPos(game->GetWindowWidth() / 2.0f,game->GetWindowHeight() / 2.0f);
			startLogo->SetPriority(500);
		}
	}
	// スタート文字をアニメーションさせる
	if (startLogo)
	{
		startLogo->SetScale(Easing::OutBounce(timer->GetTime(),timer->GetLimit(),1.0f,0.0f));
	}
	if (seTimer)
	{
		if (seTimer->Finished())
		{
			cSoundCtrl::GetInstance().Play(SOUND_ID::START);
			seTimer->DeleteObject();
		}
	}

	if (timer->Finished())
	{
		startLogo->DeleteObject();
		timer->DeleteObject();
		if (seTimer) seTimer->DeleteObject();
		// ゲーム状態をプレイ中に変更する
		SetGameState(GAME_STATE::PLAY);
	}
}

//==========================================================================================
//  ゲームプレイ状態
//==========================================================================================
void cGameMain::Play(void)
{
	// 段階的にゲームを難しくするための処理
	cTimer* lvTimer = (cTimer*)FindChild("LevelUpTimer");
	if (lvTimer)
	{
		if (lvTimer->Finished())
		{
			// レベルアップタイマーを初期化して難易度を1段階上げる
			lvTimer->Reset();
			m_nDifficult++;
			if (m_nDifficult >= MAX_DIFFICULT) m_nDifficult = MAX_DIFFICULT;
		}
	}
	else
	{
		// レベルアップタイマーの生成
		lvTimer = CreateObject<cTimer>(this, "LevelUpTimer");
		lvTimer->Setup(LEVELUP_TIME);
	}
}

//==========================================================================================
//  ゲームオーバー状態
//==========================================================================================
void cGameMain::Over(void)
{
	cGame* game = (cGame*)GetRoot();

	// ゲーム画面をセピアカラーにする
	cSurfaceObject* surface = (cSurfaceObject*)FindChild("MonoSurface");
	cTransitionObject* transition = (cTransitionObject*)FindChild("Transition");
	if ( !surface )
	{
		// モノトーンサーフェイスを作成
		surface = CreateSurfaceObject<cSurfaceObject>(this, "MonoSurface", game->GetWindowWidth(), game->GetWindowHeight(), -202, 501);
		surface->SetPos(game->GetWindowCenter());
		surface->SetFilterMode(cSurface::FILTER_MODE::MONO);
		surface->SetMonoBlue(-60);
		surface->SetMonoRed(7);

		// トランジション用サーフェイスを作成
		surface = CreateSurfaceObject<cSurfaceObject>(this, "SorceSurface", game->GetWindowWidth(), game->GetWindowHeight(), -201, 502);
		surface->SetPos(game->GetWindowCenter());
		surface->SetFilterMode(cSurface::FILTER_MODE::NONE);
		// トランジションで表示するサーフェイスの為非表示
		surface->SetShow(false);

		// トランジションを作成
		transition = CreateTransitionObject<cTransitionObject>(this,"Transition","data\\graphic\\rule_02.png",surface,cTransition::TransDirection::TRANS_IN,2.0f);
		transition->SetPriority(550);
	}

	// トランジションが終了したらリザルトシーンをPushする
	if (transition->IsEnd())
	{
		transition->DeleteObject();
		surface = (cSurfaceObject*)FindChild("SorceSurface");
		if(surface) surface->DeleteObject();

		cSceneManager* sm = (cSceneManager*)GetParent();
		sm->PushScene(SCENE_ID::RESULT);
	}
}
