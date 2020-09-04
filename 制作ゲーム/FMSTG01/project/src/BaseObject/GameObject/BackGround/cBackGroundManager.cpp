/*==============================================================================*/
/*																				*/
/*	@file title	:	cBackGroundManager.cpp										*/
/*  @brief		:	背景管理クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/10													*/
/*																				*/
/*==============================================================================*/

#include "cBackGroundManager.h"
#include "Star\cStar.h"
#include "..\..\..\cGame.h"

//==========================================================================================
// 初期化
//==========================================================================================
void cBackGroundManager::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "BackGroundManager";

	cGame& game = cGame::GetInstance();

	for (int i = 0; i < STAR_POP_NUM; i++)
	{
		cStar* obj = CreateObject<cStar>(this);
		// 初期位置をランダムに設定
		obj->SetPos((float)game.Random(0,game.GetPlayAreaWidth()), (float)game.Random(0, game.GetPlayAreaHeight()) );
	}

	IBaseObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cBackGroundManager::Update(void)
{

	IBaseObject::Update();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject * cBackGroundManager::Finalize(void)
{
	IBaseObject::Finalize();
	return nullptr;
}