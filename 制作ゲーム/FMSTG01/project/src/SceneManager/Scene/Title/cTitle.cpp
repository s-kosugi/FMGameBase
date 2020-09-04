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
#include "..\..\..\Input\cControllerManager.h"
#include "..\..\..\BaseObject\cSpriteObject.h"
#include "..\..\..\BaseObject\GameObject\Effect\cEffectManager.h"
#include "..\..\..\BaseObject\GameObject\OtherSprite\TitleTile\cTitleTileManager.h"
#include "..\..\..\SoundCtrl\cSoundCtrl.h"

#include <DxLib.h>


//==========================================================================================
//  コンストラクタ
//==========================================================================================
cTitle::cTitle(IBaseObject * parent)
	: IBaseObject(parent, "Title"),
	m_nCounter( 0 ),
	m_eTitleState( STATE_TILE_POP )
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
	// タイルマネージャーの作成
	cTitleTileManager* tileMan = CreateObject<cTitleTileManager>(this);
	tileMan->StartPop();

	// タイトル文字の生成
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this,"TitleFont","data\\graphic\\TitleFont.png");
	obj->SetVisible(false);
	obj->SetPriority(101);
	obj->SetPos(cGame::GetInstance().GetWindowWidth() / 2.0f ,cGame::GetInstance().GetWindowHeight() / 2.0f - 75.0f);


	// PUSHKEYの生成
	obj = CreateDrawObject<cSpriteObject>(this,"PushKey","data\\graphic\\PushKey.png");
	obj->SetVisible(false);
	obj->SetPriority(101);
	obj->SetPos(cGame::GetInstance().GetWindowWidth() / 2.0f ,(float)cGame::GetInstance().GetWindowHeight() - obj->GetSpriteSize().y );

	// タイトルBGMの再生
	cSoundCtrl::GetInstance().BGMPlay(SOUND_TITLE);

	IBaseObject::Initialize();
}
//==========================================================================================
//  更新
//==========================================================================================
void cTitle::Update(void)
{
	IBaseObject::Update();

	m_nCounter++;
	
	switch( m_eTitleState )
	{
	case STATE_TILE_POP:
		TilePop();
		break;
	case STATE_APPEAR_TITLE:
		AppearTitle();
		break;
	case STATE_PUSHKEY:
		PushKey();
		break;
	case STATE_CRUMBLE:
		Crumble();
		break;
	}

	// タイル崩ステートへ
	if (cControllerManager::GetInstance().CheckTriger(cControllerManager::KEY_1))
	{
		m_eTitleState = STATE_CRUMBLE;

		cSpriteObject* font = ((cSpriteObject*)FindChild("TitleFont"));
		if( nullptr != font ) font->DeleteObject();
		cSpriteObject* push = ((cSpriteObject*)FindChild("PushKey"));
		if(nullptr != push) push->DeleteObject();
		((cTitleTileManager*)FindChild("TitleTileManager"))->StartCrumble();
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
//  タイル出現時
//==========================================================================================
void cTitle::TilePop(void)
{
	cTitleTileManager* tileMan = (cTitleTileManager*)FindChild("TitleTileManager");

	// タイルの出現が終わっていればタイトル文字出現シーンへ移行
	if (tileMan != nullptr && tileMan->IsPopComp())
	{
		cSpriteObject* obj = (cSpriteObject*)FindChild("TitleFont");
		obj->SetVisible(true);
		m_eTitleState = STATE_APPEAR_TITLE;
	}
}
//==========================================================================================
//  タイトル出現時
//==========================================================================================
void cTitle::AppearTitle(void)
{
	m_eTitleState = STATE_PUSHKEY;
	m_nCounter = 0;
}
//==========================================================================================
//  キー押下表示
//==========================================================================================
void cTitle::PushKey(void)
{
	cSpriteObject* obj = (cSpriteObject*)FindChild("PushKey");
	if(m_nCounter % PUSHKEY_INTERVAL > PUSHKEY_INTERVAL / 2)
	{
		obj->SetVisible(true);
	}else
	{
		obj->SetVisible(false);
	}
}
//==========================================================================================
//  タイルが崩れる
//==========================================================================================
void cTitle::Crumble(void)
{
	// 全てのタイルが崩れるかキー押下した場合はゲームメイン
	if (m_listChildObject.empty() || cControllerManager::GetInstance().CheckTriger(cControllerManager::KEY_1))
	{
		// 全てのタイルが崩れたらゲームメイン
		cSceneManager* sm = (cSceneManager*)GetParent();
		sm->ChangeScene(SCENE_ID_GAMEMAIN, cSceneManager::CHANGE_UNITRANS);
	}
}
