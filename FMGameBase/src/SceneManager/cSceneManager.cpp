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
#include "Scene\EffekseerTest\cEffekseerTest.h"
#include "Scene/Pause/cPause.h"
#include "..\cGame.h"
#include "Utility/Timer/cTimer.h"
#include "Utility/Easing/Easing.h"

#include "../BaseObject/cSpriteObject.h"

//==========================================================================================
// 定数
//==========================================================================================
const float    cSceneManager::DEFAULT_FADE_TIME = 1.0f;

//==========================================================================================
// 初期化
//==========================================================================================
void cSceneManager::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE::ACTIVE;
	m_sObjectName = "SceneManager";

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
	case STATE::FADEIN:      FadeIn();			break;
	case STATE::UPDATE:		UpdateScene();		break;
	case STATE::FADEOUT:     FadeOut();			break;
	case STATE::TRANSITION:	TransitionScene();	break;
	}
}

//==========================================================================================
// シーン変更
//==========================================================================================
void cSceneManager::ChangeScene(SCENE_ID id, CHANGE_TYPE type)
{
	m_eNextScene = id;
	m_eChangeOutType = type;
	m_eChangeInType = type;
}

//==========================================================================================
// シーン変更(ユニバーサルトランジション)
//==========================================================================================
void cSceneManager::ChangeSceneUniTrans(SCENE_ID id, std::string ruleFilename)
{
	m_eNextScene = id;
	m_eChangeOutType = CHANGE_TYPE::UNITRANS;
	m_eChangeInType = CHANGE_TYPE::UNITRANS;
	m_sTransOutFileName = ruleFilename;
	m_sTransInFileName = ruleFilename;
}

//==========================================================================================
// スタックしているシーンの最後尾を取得
//==========================================================================================
SCENE_ID cSceneManager::GetStackSceneID(void)
{
	if (m_nStackCount < 1) return m_eCurrentScene;

	if (m_listChildObject.empty()) return m_eCurrentScene;
	auto end = m_listChildObject.end();
	end--;

	IBaseScene* scene = (IBaseScene*)(*end);

	return scene->GetSceneID();
}
//==========================================================================================
// シーンのスタック
//==========================================================================================
void cSceneManager::PushScene(SCENE_ID id)
{
	// 同フレーム中にすでにプッシュされている
	if (m_bPush || m_ePushSceneID != SCENE_ID::NONE) return;

	// 直前のシーンの更新を止める
	if (!m_listChildObject.empty())
	{
		auto end = m_listChildObject.end();
		end--;

		IBaseScene* scene = (IBaseScene*)(*end);
		scene->SetObjetState(OBJECT_STATE::WAIT);
	}

	// プッシュフラグをON
	m_bPush = true;

	// スタックするシーンIDを保存
	m_ePushSceneID = id;

	m_nStackCount++;
}
//==========================================================================================
// スタックしたシーンの削除
//==========================================================================================
void cSceneManager::PopScene(void)
{
	// 子のシーンが1つの場合はポップできない
	if (m_nStackCount <= 1)
		return;

	// 末尾のシーンのイテレータ取得
	auto it = m_listChildObject.rbegin();

	IBaseScene* scene = (IBaseScene*)(*it);

	// 末尾のシーンを削除対象に設定
	scene->DeleteObject();

	// １つ前のシーンを取得
	scene = (IBaseScene*)(*(++it));

	// １つ前のシーンをアクティブ状態に変更
	scene->SetObjetState(OBJECT_STATE::ACTIVE);

	m_nStackCount--;
}
//==========================================================================================
// リセット
//==========================================================================================
void cSceneManager::Reset(CHANGE_TYPE changeType)
{
	// 指定したフェードでシーンをリセットする(デフォルト無し)
	m_eChangeOutType = changeType;
	PrepareFadeOut();
}
//==========================================================================================
// シーン生成
// id : 生成するシーンID
// return : 生成したシーンのポインタ
//==========================================================================================
IBaseScene* cSceneManager::CreateScene(SCENE_ID id)
{
	IBaseScene* pscene = nullptr;
	switch (id)
	{
	case SCENE_ID::TITLE:			pscene = CreateObject<cTitle>(this);			break;
	case SCENE_ID::GAMEMAIN:		pscene = CreateObject<cGameMain>(this);			break;
	case SCENE_ID::EFFEKSEER_TEST:	pscene = CreateObject<cEffekseerTest>(this);	break;
	case SCENE_ID::PAUSE:			pscene = CreateObject<cPause>(this);			break;
	}
	if (pscene != nullptr) pscene->SetSceneID(id);
	return pscene;
}
//==========================================================================================
// フェードアウト前準備
//==========================================================================================
void cSceneManager::PrepareFadeOut(void)
{
	m_eState = STATE::FADEOUT;

	cSpriteObject* obj = (cSpriteObject*)FindChild("black");
	obj->SetAlpha(0);
	switch (m_eChangeOutType)
	{
	case CHANGE_TYPE::NOFADE:
		obj->SetVisible(false);
		break;
	case CHANGE_TYPE::FADE:
		obj->SetVisible(true);
		break;
	case CHANGE_TYPE::UNITRANS:
		if (m_pTransObj == nullptr)
		{
			m_pTransObj = new cTransition(m_sTransOutFileName, obj, cTransition::TransDirection::TRANS_OUT, (float)m_nFadeOutTime);
			m_pTransObj->Initialize();
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
	cTimer* timer = (cTimer*)FindChild("FadeInTimer");

	switch (m_eChangeInType)
	{
		// フェードイン演出なし
	case CHANGE_TYPE::NOFADE:
		m_eState = STATE::UPDATE;
		break;
		// フェードイン
	case CHANGE_TYPE::FADE:
		if (timer == nullptr)
		{
			timer = CreateObject<cTimer>(this, "FadeInTimer");
			timer->Setup(m_nFadeOutTime);
		}
		timer->Update();
		alpha = (int)Easing::Linear(timer->GetTime(), timer->GetLimit(), 0.0f, 255.0f);
		if (alpha <= 0)
		{
			alpha = 0;
			timer->DeleteObject();
			m_eState = STATE::UPDATE;
		}
		obj->SetAlpha(alpha);
		break;
	case CHANGE_TYPE::UNITRANS:
		if (m_pTransObj != nullptr)
		{
			m_pTransObj->Update();
			if (m_pTransObj->IsEnd())
			{
				m_eState = STATE::UPDATE;
				SAFE_DELETE(m_pTransObj);
			}
		}
		else
		{
			m_eState = STATE::UPDATE;
		}
		break;
	}
}

//==========================================================================================
// シーン更新
//==========================================================================================
void cSceneManager::UpdateScene(void)
{
	// プッシュ処理がある
	if (m_bPush)
	{
		// 新しいシーンを生成してスタックする
		IBaseScene* pscene = CreateScene(m_ePushSceneID);
		if (pscene)
		{
			pscene->Initialize();
		}
		m_ePushSceneID = SCENE_ID::NONE;
		m_bPush = false;
	}
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
	cSpriteObject* obj = (cSpriteObject*)FindChild("black");
	int alpha = obj->GetAlpha();
	cTimer* timer = (cTimer*)FindChild("FadeOutTimer");

	switch (m_eChangeOutType)
	{
		// フェードアウト演出なし
	case CHANGE_TYPE::NOFADE:
		m_eState = STATE::TRANSITION;
		break;
		// フェードアウト
	case CHANGE_TYPE::FADE:
		if (timer == nullptr)
		{
			timer = CreateObject<cTimer>(this, "FadeOutTimer");
			timer->Setup(m_nFadeOutTime);
		}
		timer->Update();
		alpha = (int)Easing::Linear(timer->GetTime(), timer->GetLimit(), 255.0f, 0.0f);
		if (alpha > 255)
		{
			alpha = 255;
			timer->DeleteObject();
			m_eState = STATE::TRANSITION;
		}

		obj->SetAlpha(alpha);
		break;
	case CHANGE_TYPE::UNITRANS:
		if (m_pTransObj != nullptr)
		{
			m_pTransObj->Update();
			if (m_pTransObj->IsEnd())	m_eState = STATE::TRANSITION;
		}
		else
		{
			m_eState = STATE::TRANSITION;
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

	// フェード用スプライトの生成
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "black", "data\\graphic\\black.png");
	obj->SetAlpha(255);
	obj->SetPriority(60000);
	obj->SetPos((float)cGame::GetInstance().GetWindowWidth() / 2, (float)cGame::GetInstance().GetWindowHeight() / 2);

	CreateScene(m_eNextScene);

	switch (m_eChangeOutType)
	{
	case CHANGE_TYPE::NOFADE: obj->SetVisible(false); break;
	case CHANGE_TYPE::FADE:	obj->SetVisible(true); break;
	case CHANGE_TYPE::UNITRANS:
		m_pTransObj = new cTransition(m_sTransOutFileName, obj, cTransition::TransDirection::TRANS_IN, (float)m_nFadeInTime);
		m_pTransObj->Initialize();
		obj->SetVisible(false);
		break;
	}

	m_eCurrentScene = m_eNextScene;

	m_eState = STATE::FADEIN;

	m_nStackCount = 1;

	IBaseObject::Initialize();

	IBaseObject::Update();

}

//==========================================================================================
// コンストラクタ
//==========================================================================================
cSceneManager::cSceneManager(void) :
	m_eCurrentScene(SCENE_ID::NONE),
	m_eNextScene(SCENE_ID::TITLE),
	m_eState(STATE::TRANSITION),
	m_eChangeInType(CHANGE_TYPE::NOFADE),
	m_eChangeOutType(CHANGE_TYPE::NOFADE),
	m_nFadeInTime(DEFAULT_FADE_TIME),
	m_nFadeOutTime(DEFAULT_FADE_TIME),
	m_ePushSceneID(SCENE_ID::NONE),
	m_bPush(false),
	m_nStackCount(0),
	m_pTransObj(nullptr),
	m_sTransOutFileName(""),
	m_sTransInFileName("")
{
}

//==========================================================================================
// コンストラクタ
//==========================================================================================
cSceneManager::cSceneManager(IBaseObject* parent) :
	cSceneManager()
{
}

//==========================================================================================
// コンストラクタ
//==========================================================================================
cSceneManager::cSceneManager(IBaseObject* parent, const std::string& name) :
	cSceneManager(parent)
{
}

//==========================================================================================
// コピーコンストラクタ
//==========================================================================================
cSceneManager::cSceneManager(const cSceneManager& t) :
	cSceneManager()
{
}
