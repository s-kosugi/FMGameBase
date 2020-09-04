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
#include "..\..\..\Input\Keyboard\cKeyboard.h"
#include "..\..\..\BaseObject\cSpriteObject.h"
#include <DxLib.h>

#include "..\..\..\BaseObject\GameObject\BackGround\cBackGroundManager.h"
#include "..\..\..\BaseObject\GameObject\Player\cPlayer.h"
#include "..\..\..\BaseObject\GameObject\Enemy\cEnemyManager.h"
#include "..\..\..\BaseObject\GameObject\Bullet\cBulletManager.h"
#include "..\..\..\EventManager\cEventManager.h"
#include "..\..\..\BaseObject\GameObject\Effect\cEffectManager.h"
#include "..\..\..\BaseObject\GameObject\SpEffect\cSpEffectManager.h"
#include "..\..\..\BaseObject\GameObject\UI\cUIManager.h"

#include "..\..\..\ScoreManager\cScoreManager.h"
#include "..\..\..\Input\cControllerManager.h"
#include "..\..\..\Pause\cPause.h"

#include "..\..\..\SoundCtrl\cSoundCtrl.h"

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cGameMain::cGameMain(IBaseObject * parent)
	: IBaseObject(parent, "GameMain")
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
	// 背景マネージャーの追加
	AddChild(&cBackGroundManager::GetInstance());

	// プレイヤーキャラクターの生成
	CreateObject<cPlayer>(this);

	// 敵マネージャーの追加
	AddChild(&cEnemyManager::GetInstance());

	// 弾マネージャーの追加
	AddChild(&cBulletManager::GetInstance());

	// イベントマネージャーの追加
	AddChild(&cEventManager::GetInstance());

	// ステージ１のイベントを開始
	cEventManager::GetInstance().StartEvent(1);

	// エフェクトマネージャーの追加
	AddChild(&cEffectManager::GetInstance());

	// スプライトエフェクトマネージャーの追加
	AddChild(&cSpEffectManager::GetInstance());

	// UIマネージャーの追加
	AddChild(&cUIManager::GetInstance());

	// スコアリセット
	cScoreManager::GetInstance().ResetScore();

	IBaseObject::Initialize();
}
//==========================================================================================
//  更新
//==========================================================================================
void cGameMain::Update(void)
{

	IBaseObject::Update();

	// 当たり判定処理
	CheckHitProc();

	// ポーズ開始処理
	if (cControllerManager::GetInstance().CheckTriger(cControllerManager::KEY_PAUSE))
		cPause::GetInstance().StartPause();

#ifdef DEBUG
	// タイトルシーンへ
	cKeyboard key = cKeyboard::GetInstance();
	if (key.CheckTriger(KEY_INPUT_RETURN))
	{
		cSceneManager* sm = (cSceneManager*)GetParent();
		sm->ChangeScene(SCENE_ID_TITLE);
	}
#endif
}

//==========================================================================================
//  破棄
//==========================================================================================
IBaseObject* cGameMain::Finalize(void)
{
	// ※フェードアウト関数を作ったほうがいいかも。
	cSoundCtrl::GetInstance().BGMStop();

	IBaseObject::Finalize();
	return this;
}
//==========================================================================================
//  当たり判定処理
//==========================================================================================
void cGameMain::CheckHitProc(void)
{
	// 自機と敵の当たり判定処理
	CheckHitPlayer();

	// 敵の当たり判定処理
	CheckHitEnemy();
	
}

//==========================================================================================
//  自機と敵の当たり判定
//  自機VS敵  自機VS敵の弾
//==========================================================================================
void cGameMain::CheckHitPlayer(void)
{
	cPlayer* player = (cPlayer*)FindChild("Player");
	if (nullptr == player) return;
	cEnemyManager& em = cEnemyManager::GetInstance();

	std::list<IBaseObject*>::iterator it = em.GetChildList()->begin();
	std::list<IBaseObject*>::iterator end = em.GetChildList()->end();

	while (it != end)
	{
		cHitObject* obj = (cHitObject*)(*it);
		// 敵とプレイヤーの当たり判定をする
		if (player->CheckHitObject(*obj))
		{
			// 当たった
			return;
		}
		it++;
	}


	cBulletManager& bm = cBulletManager::GetInstance();
	std::list<IBaseObject*>::iterator bit = bm.GetChildList()->begin();
	std::list<IBaseObject*>::iterator bend = bm.GetChildList()->end();

	while (bit != bend)
	{
		cHitObject* obj = (cHitObject*)(*bit);
		if (obj->GetHitCate() == cHitObject::HIT_ENEMY)
		{
			// プレイヤーと敵の弾の当たり判定をする
			if (player->CheckHitObject(*obj))
			{
				// 当たった
				return;
			}
		}
		bit++;
	}
}

//==========================================================================================
//  敵と自機の弾の当たり判定
//==========================================================================================
void cGameMain::CheckHitEnemy(void)
{
	cEnemyManager& em = cEnemyManager::GetInstance();
	std::list<IBaseObject*>::iterator it = em.GetChildList()->begin();
	std::list<IBaseObject*>::iterator end = em.GetChildList()->end();

	cBulletManager& bm = cBulletManager::GetInstance();
	std::list<IBaseObject*>::iterator bit = bm.GetChildList()->begin();
	std::list<IBaseObject*>::iterator bend = bm.GetChildList()->end();


	while (it != end)
	{
		cHitObject* obj = (cHitObject*)(*it);

		while (bit != bend)
		{
			cHitObject* bobj = (cHitObject*)(*bit);
			if (bobj->GetHitCate() == cHitObject::HIT_PLAYER)
			{
				// 全オブジェクトと当たり判定をする
				obj->CheckHitObject(*bobj);
				// 敵とプレイヤーの弾当たり判定をする
				//if (obj->CheckHitObject(*bobj))
				//{
				//	// 当たった
				//	break;
				//}
			}
			bit++;
		}
		bit = bm.GetChildList()->begin();
		it++;
	}
}
