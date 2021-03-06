/*==============================================================================*/
/*																				*/
/*	@file title	:	cSpriteObject.cpp											*/
/*  @brief		:	描画オブジェクト											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "cSpriteObject.h"
#include "..\DrawCtrl\cDrawCtrl.h"
#include "..\cGame.h"

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cSpriteObject::cSpriteObject(IBaseObject* parent, const std::string& objectname, const std::string& filename) :
	IBaseObject(parent,objectname),
	cSprite(filename)
{
	
}

//==========================================================================================
//  デストラクタ
//==========================================================================================
cSpriteObject::~cSpriteObject(void)
{
}

//==========================================================================================
//  初期化
//==========================================================================================
void
cSpriteObject::
Initialize(void)
{
	IBaseObject::Initialize();
	cSprite::Initialize();
}

//==========================================================================================
//  更新
//==========================================================================================
void cSpriteObject::Update(void)
{
	IBaseObject::Update();
	cSprite::Update();
}

//==========================================================================================
//  解放
//==========================================================================================
IBaseObject* cSpriteObject::Finalize(void)
{
	IBaseObject::Finalize();
	cSprite::Finalize();
	return this;
}

//==========================================================================================
// 画面内のランダムなX座標に配置する
//==========================================================================================
void cSpriteObject::SetRandomPosX(void)
{
	cGame game = cGame::GetInstance();
	// 画面内に出現させる
	m_vPos.x = (float)game.Random(GetSpriteSize().x / 2, game.GetPlayAreaWidth() - GetSpriteSize().x / 2);
}

//==========================================================================================
// 画面内のランダムなY座標に配置する
//==========================================================================================
void cSpriteObject::SetRandomPosY(void)
{
	cGame game = cGame::GetInstance();
	// 画面内に出現させる
	m_vPos.y = (float)game.Random(GetSpriteSize().y / 2, game.GetPlayAreaHeight() - GetSpriteSize().y / 2);
}
