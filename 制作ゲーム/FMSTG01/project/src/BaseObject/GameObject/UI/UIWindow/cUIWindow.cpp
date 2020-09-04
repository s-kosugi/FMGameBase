/*==============================================================================*/
/*																				*/
/*	@file title	:	cUIWindow.cpp												*/
/*  @brief		:	UIウィンドウオブジェクト									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/27													*/
/*																				*/
/*==============================================================================*/

#include "cUIWindow.h"

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cUIWindow::cUIWindow(IBaseObject* parent) :
	cUIObject(parent,"UIWindow","data\\graphic\\UI_Window.png")
{

}

//==========================================================================================
//  デストラクタ
//==========================================================================================
cUIWindow::~cUIWindow(void)
{
}

//==========================================================================================
//  初期化
//==========================================================================================
void
cUIWindow::
Initialize(void)
{
	SetPriority(PRIORITY);

	// スコア枠の表示
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this,"ScoreFrame", "data\\graphic\\ScoreFrame.png");
	obj->SetPos(700,60);
	obj->SetPriority(PRIORITY+1);


	cUIObject::Initialize();
}

//==========================================================================================
//  更新
//==========================================================================================
void cUIWindow::Update(void)
{
	cUIObject::Update();
}

//==========================================================================================
//  解放
//==========================================================================================
IBaseObject* cUIWindow::Finalize(void)
{
	cUIObject::Finalize();
	return this;
}