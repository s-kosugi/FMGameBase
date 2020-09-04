/*==============================================================================*/
/*																				*/
/*	@file title	:	cSceneManager.cpp											*/
/*  @brief		:	シーン管理クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/
#include "cSceneManager.h"
#include "Scene\Title\cTitle.h"
#include "Scene\GameMain\cGameMain.h"
#include "..\cGame.h"

#include "../BaseObject/cSpriteObject.h"

//==========================================================================================
// 初期化
//==========================================================================================
void cSceneManager::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "SceneManager";

	// 現在シーンをダミーに設定
	m_eCurrentScene = SCENE_ID_NONE;

	// タイトルシーンを次に生成する
	m_eNextScene = SCENE_ID_TITLE;

	// シーン切り替えの状態設定
	m_eState = STATE_TRANSITION;

	// シーンの切り替え演出設定
	m_eChangeType = CHANGE_NOFADE;

	m_pTransObj = nullptr;

	//フェードアウト用
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "black", "data\\graphic\\black.png");
	obj->SetPos((float)cGame::GetInstance().GetWindowWidth() / 2, (float)cGame::GetInstance().GetWindowHeight() / 2);
	obj->SetVisible(false);


	IBaseObject::Initialize();
}
//==========================================================================================
// 更新
//==========================================================================================
void cSceneManager::Update(void)
{
	switch (m_eState)
	{
		case STATE_FADEIN:      FadeIn();			break;
		case STATE_UPDATE:		UpdateScene();		break;
		case STATE_FADEOUT:     FadeOut();			break;
		case STATE_TRANSITION:	TransitionScene();	break;
	}
}
//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject * cSceneManager::Finalize(void)
{
	IBaseObject::Finalize();

	return nullptr;
}
//==========================================================================================
// リセット
//==========================================================================================
void cSceneManager::Reset(CHANGE_TYPE changeType)
{
	// 指定したフェードでシーンをリセットする(デフォルト無し)
	m_eChangeType = changeType;
	PrepareFadeOut();
}
//==========================================================================================
// シーン生成
// id : 生成するシーンID
//==========================================================================================
void cSceneManager::CreateScene(SCENE_ID id)
{
	switch (id)
	{
		case SCENE_ID_TITLE:        CreateObject<cTitle>(this);         break;
		case SCENE_ID_GAMEMAIN:     CreateObject<cGameMain>(this);      break;
	}
}
//==========================================================================================
// フェードアウト前準備
//==========================================================================================
void cSceneManager::PrepareFadeOut(void)
{
	m_eState = STATE_FADEOUT;

	cSpriteObject* obj = (cSpriteObject*)FindChild("black");
	obj->SetAlpha(0);
	switch (m_eChangeType)
	{
	case CHANGE_NOFADE:
		obj->SetVisible(false);
		break;
	case CHANGE_FADE:
		obj->SetVisible(true);
		break;
	case CHANGE_UNITRANS:
		if (m_pTransObj == nullptr)
		{
			m_pTransObj = new cTransition(cTransition::RULE_CHECKSPHERE, obj);
			m_pTransObj->Initialize();
			m_pTransObj->SetTransDirection(cTransition::TRANS_OUT);
		}
		break;
	}
}
//==========================================================================================
// フェードイン
//==========================================================================================
void cSceneManager::FadeIn(void)
{
	cSpriteObject* obj = (cSpriteObject*)FindChild("black");
	int alpha = obj->GetAlpha();

	switch (m_eChangeType)
	{
		// フェードイン演出なし
		case CHANGE_NOFADE:
			m_eState = STATE_UPDATE;
			break;
		// フェードイン
		case CHANGE_FADE:
			alpha -= FADE_SPEED;
			if (alpha < 0)
			{
				alpha = 0;

				m_eState = STATE_UPDATE;
			}
			obj->SetAlpha(alpha);
			break;
		case CHANGE_UNITRANS:
			if (m_pTransObj != nullptr)
			{
				m_pTransObj->Update();
				if (m_pTransObj->IsEnd())
				{
					m_eState = STATE_UPDATE;
					SAFE_DELETE(m_pTransObj);
				}
			} else
			{
				m_eState = STATE_UPDATE;
			}
			break;
	}
}

//==========================================================================================
// シーン更新
//==========================================================================================
void cSceneManager::UpdateScene(void)
{
	IBaseObject::Update();

	// シーン変更の検知
	if (m_eCurrentScene != m_eNextScene)
	{
		// フェードアウト準備
		PrepareFadeOut();
	}
}
//==========================================================================================
// フェードアウト
//==========================================================================================
void cSceneManager::FadeOut(void)
{
	cSpriteObject * obj = (cSpriteObject*)FindChild("black");
	int alpha = obj->GetAlpha();

	switch (m_eChangeType)
	{
		// フェードアウト演出なし
		case CHANGE_NOFADE:
			m_eState = STATE_TRANSITION;
			break;
		// フェードアウト
		case CHANGE_FADE:
			alpha += FADE_SPEED;
			if (alpha > 255)
			{
				alpha = 255;

				m_eState = STATE_TRANSITION;
			}
			obj->SetAlpha(alpha);
			break;
		case CHANGE_UNITRANS:
			if (m_pTransObj != nullptr)
			{
				m_pTransObj->Update();
				if (m_pTransObj->IsEnd())	m_eState = STATE_TRANSITION;
			} else
			{
				m_eState = STATE_TRANSITION;
			}
			break;
	}
}
//==========================================================================================
// シーン遷移
//==========================================================================================
void cSceneManager::TransitionScene(void)
{
	IBaseObject::Finalize();
	SAFE_DELETE(m_pTransObj);

	CreateScene(m_eNextScene);

	// フェード用スプライトの生成
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "black", "data\\graphic\\black.png");
	obj->SetAlpha(255);
	obj->SetPriority(60000);
	obj->SetPos((float)cGame::GetInstance().GetWindowWidth() / 2, (float)cGame::GetInstance().GetWindowHeight() / 2);

	switch( m_eChangeType)
	{
	case CHANGE_NOFADE: obj->SetVisible(false); break;
	case CHANGE_FADE:	obj->SetVisible(true); break;
	case CHANGE_UNITRANS:
		m_pTransObj = new cTransition(cTransition::RULE_CHECKSPHERE, obj);
		m_pTransObj->Initialize();
		m_pTransObj->SetTransDirection(cTransition::TRANS_IN);
		obj->SetVisible(false);
		break;
	}

	IBaseObject::Initialize();

	IBaseObject::Update();

	m_eCurrentScene = m_eNextScene;

	m_eState = STATE_FADEIN;
}
