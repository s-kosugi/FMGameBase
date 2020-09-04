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
#include "..\..\..\BaseObject\GameObject\Effect\cEffectManager.h"
#include <DxLib.h>

#include "..\..\..\BaseObject\GameObject\Player\cPlayer.h"

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cGameMain::cGameMain(IBaseObject * parent)
	: IBaseScene(parent, "GameMain")
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
	// 背景スプライトの生成
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "TitleBack", "data\\graphic\\title.png");
	obj->SetPriority(-100);
	obj->SetPos((float)cGame::GetInstance().GetWindowWidth()/2, (float)cGame::GetInstance().GetWindowHeight() / 2);

	// エフェクトマネージャーの追加
	AddChild(&cEffectManager::GetInstance());

	// プレイヤーキャラクターの生成
	CreateObject<cPlayer>(this);

	IBaseObject::Initialize();
}
//==========================================================================================
//  更新
//==========================================================================================
void cGameMain::Update(void)
{

	IBaseObject::Update();

	// エフェクシアテストシーンへ
	cKeyboard& key = cKeyboard::GetInstance();
	if (key.CheckTrigger(KEY_INPUT_RETURN))
	{
		cSceneManager* sm = (cSceneManager*)GetParent();
		sm->ChangeSceneUniTrans(SCENE_ID::EFFEKSEER_TEST,"data\\graphic\\rule_00.png");
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
