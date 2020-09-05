/*==============================================================================*/
/*																				*/
/*	@file title	:	cTitle.cpp													*/
/*  @brief		:	タイトルシーン												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\cGame.h"
#include "cTitle.h"
#include "..\..\cSceneManager.h"
#include "Input/cControllerManager.h"
#include "..\..\..\BaseObject\cSpriteObject.h"
#include "SoundCtrl/cSoundCtrl.h"
#include "Utility/Timer/cTimer.h"
#include "Utility/Easing/Easing.h"
#include "BaseObject/cSurfaceObject.h"
#include "SoundCtrl/cSoundCtrl.h"


//==========================================================================================
//  定数
//==========================================================================================
const float cTitle::PUSH_Z_TIME = 0.5f;
const float cTitle::TITLELOGO_TIME = 2.0f;
const float cTitle::SURFACE_TIME = 1.0f;

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cTitle::cTitle(IBaseObject * parent)
	: IBaseScene(parent, "Title")
{
}
//==========================================================================================
//  デストラクタ
//==========================================================================================
cTitle::~cTitle(void)
{
}
//==========================================================================================
//  初期化
//==========================================================================================
void cTitle::Initialize(void)
{
	cGame* game = (cGame*)GetRoot();

	// 背景スプライトの生成
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this,"TitleBack","data\\graphic\\bg_01.png");
	obj->SetPriority(-100);
	obj->SetPos( game->GetWindowWidth() / 2.0f, game->GetWindowHeight() / 2.0f );

	// タイトルロゴの生成
	obj = CreateDrawObject<cSpriteObject>( this, "TitleLogo", "data\\graphic\\title_logo.png" );
	obj->SetPriority( 0 );
	obj->SetPos( game->GetWindowWidth() / 2.0f, game->GetWindowHeight() / 2.0f );
	cTimer* timer = CreateObject<cTimer>( this, "TitleLogoTimer" );
	timer->Setup( TITLELOGO_TIME );

	// PushZKey
	obj = CreateDrawObject<cSpriteObject>( this, "PushZKey", "data\\graphic\\push.png" );
	obj->SetPriority( 0 );
	obj->SetPos( game->GetWindowWidth() / 2.0f, game->GetWindowHeight() / 2.0f  + 150);
	timer = CreateObject<cTimer>( this, "ZKeyTimer" );
	timer->Setup( PUSH_Z_TIME );


	// サーフェイスの作成
	cSurfaceObject* surface = CreateSurfaceObject<cSurfaceObject>( this, "ScreenSurface", game->GetWindowWidth(), game->GetWindowHeight(), -200, 500 );
	surface->SetPos( game->GetWindowWidth() / 2.0f, game->GetWindowHeight() / 2.0f );
	

	// BGMの再生
	cSoundCtrl* sc = (cSoundCtrl*)GetRoot()->FindChild( "SoundCtrl" );
	if (sc) sc->BGMPlay(SOUND_ID::BGM0);

	IBaseObject::Initialize();
}
//==========================================================================================
//  更新
//==========================================================================================
void cTitle::Update(void)
{
	IBaseObject::Update();

	// PushZKeyのアニメーション処理
	AnimationPushZKey();

	// タイトルロゴのアニメーション処理
	AnimationTitleLogo();

	// サーフェイスのアニメーション処理
	AnimationSurface();

	// ゲームメインシーンへ
	cControllerManager* cm = (cControllerManager*)GetParent()->FindSibling("ControllerManager");
	if( cm )
	{
		if( cm->CheckTrigger( cControllerManager::KEY_DEFINE::KEY_1 ) )
		{
			cSceneManager* sm = (cSceneManager*)GetParent();
			sm->ChangeSceneUniTrans( SCENE_ID::GAMEMAIN, "data\\graphic\\rule_00.png" );

			cSoundCtrl::GetInstance().Play(SOUND_ID::WARP);
		}
	}
}
//==========================================================================================
//  破棄
//==========================================================================================
IBaseObject* cTitle::Finalize(void)
{

	IBaseObject::Finalize();
	return this;
}

//==========================================================================================
//  PushZKeyのアニメーション処理
//==========================================================================================
void cTitle::AnimationPushZKey( void )
{
	cSpriteObject* obj = (cSpriteObject*)FindChild( "PushZKey" );
	if( !obj ) return;

	// PushZKeyをアニメーションさせる
	// 表示を消す
	cTimer* timer = (cTimer*)FindChild( "ZKeyTimer" );
	if( timer )
	{
		if( !timer->Finished() )
		{
			obj->SetAlpha( (int)Easing::InExp( timer->GetTime(), timer->GetLimit(), 0.0f, 255.0f ) );
		}
		else
		{
			timer->DeleteObject();
			cTimer* timer = CreateObject<cTimer>( this, "ZKeyTimerBack" );
			timer->Setup( PUSH_Z_TIME );
		}
	}
	// 出現させる
	cTimer* backTimer = (cTimer*)FindChild("ZKeyTimerBack");
	if( backTimer )
	{
		if( !backTimer->Finished() )
		{
			obj->SetAlpha( (int)Easing::OutExp( backTimer->GetTime(), backTimer->GetLimit(), 255.0f, 0.0f ) );
		}
		else
		{
			backTimer->DeleteObject();
			cTimer* timer = CreateObject<cTimer>( this, "ZKeyTimer" );
			timer->Setup( PUSH_Z_TIME );
		}
	}
}

//==========================================================================================
//  タイトルロゴのアニメーション処理
//==========================================================================================
void cTitle::AnimationTitleLogo( void )
{
	cSpriteObject* obj = (cSpriteObject*)FindChild( "TitleLogo" );
	if( !obj ) return;

	// 拡大アニメーション
	cTimer* timer = (cTimer*)FindChild( "TitleLogoTimer" );
	if( timer )
	{
		if( !timer->Finished() )
		{
			obj->SetScale(Easing::OutBack(timer->GetTime(),timer->GetLimit(),1.1f,1.0f,2.0f));
		}
		else
		{
			timer->DeleteObject();
			cTimer* timer = CreateObject<cTimer>( this, "TitleLogoTimerBack" );
			timer->Setup( TITLELOGO_TIME );
		}
	}

	// 大きさを元に戻す
	cTimer* backTimer = (cTimer*)FindChild( "TitleLogoTimerBack" );
	if( backTimer )
	{
		if( !backTimer->Finished() )
		{
			obj->SetScale( Easing::OutBack( backTimer->GetTime(), backTimer->GetLimit(), 1.0f, 1.1f ,2.0f) );
		}
		else
		{
			backTimer->DeleteObject();
			cTimer* timer = CreateObject<cTimer>( this, "TitleLogoTimer" );
			timer->Setup( TITLELOGO_TIME );
		}
	}

}

//==========================================================================================
//  サーフェイスのアニメーション処理
//==========================================================================================
void cTitle::AnimationSurface( void )
{
	cSurfaceObject* obj = (cSurfaceObject*)FindChild( "ScreenSurface" );
	if( !obj ) return;

	cTimer* seTimer = (cTimer*)FindChild("SETimer");

	// サーフェイスをアニメーションさせる
	cTimer* timer = (cTimer*)FindChild( "SurfaceTimer" );
	if (!timer)
	{
		timer = CreateObject<cTimer>(this, "SurfaceTimer");
		timer->Setup(SURFACE_TIME);

		seTimer = CreateObject<cTimer>(this, "SETimer");
		seTimer->Setup(0.1f);
	}

	if (seTimer)
	{
		if (seTimer->Finished())
		{
			seTimer->DeleteObject();
			// サーフェイス生成時にサウンドを再生
			cSoundCtrl* sc = (cSoundCtrl*)GetRoot()->FindChild("SoundCtrl");
			if (sc) sc->Play(SOUND_ID::TITLEPOP);
		}
	}

	if( !timer->Finished() )
	{
		obj->SetScale(Easing::OutBack(timer->GetTime(),timer->GetLimit(),1.0f,0.0f,1.5f));
	}
	else
	{
		if (seTimer) seTimer->DeleteObject();
		timer->DeleteObject();
		obj->DeleteObject();
	}
}
