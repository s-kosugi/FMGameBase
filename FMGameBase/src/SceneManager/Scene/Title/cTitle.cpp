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
#include "..\..\..\Input\Keyboard\cKeyboard.h"
#include "..\..\..\BaseObject\cSpriteObject.h"
#include <DxLib.h>

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
	// 背景スプライトの生成
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this,"TitleBack","data\\graphic\\title.png");
	obj->SetPriority(-100);
	obj->SetPos((float)cGame::GetInstance().GetWindowWidth() / 2, (float)cGame::GetInstance().GetWindowHeight() / 2);


	IBaseObject::Initialize();
}
//==========================================================================================
//  更新
//==========================================================================================
void cTitle::Update(void)
{
	IBaseObject::Update();

	// ゲームメインシーンへ
	cKeyboard& key = cKeyboard::GetInstance();
	//if (key.CheckTrigger(KEY_INPUT_RETURN))
	{
		cSceneManager* sm = (cSceneManager*)GetParent();
		//sm->ChangeScene(SCENE_ID_GAMEMAIN, cSceneManager::CHANGE_TYPE::CHANGE_UNITRANS);
		sm->ChangeSceneUniTrans(SCENE_ID::GAMEMAIN,"data\\graphic\\rule_01.png");
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
