/*==============================================================================*/
/*																				*/
/*	@file title	:	cTransitionObject.cpp										*/
/*  @brief		:	トランジションオブジェクト									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/02/12													*/
/*																				*/
/*==============================================================================*/

#include "cTransitionObject.h"

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cTransitionObject::cTransitionObject(IBaseObject* parent, const std::string& objectname, const std::string& ruleFilename, const std::string& spriteFileName, TransDirection dir, float transTime) :
	IBaseObject(parent, objectname),
	cTransition(ruleFilename, m_pSprite = new cSprite(spriteFileName), dir, transTime)
{
	// 元画像のスプライト画像は非表示にする
	m_pSprite->SetVisible(false);
}
//==========================================================================================
//  コンストラクタ
//==========================================================================================
cTransitionObject::cTransitionObject(IBaseObject* parent, const std::string& objectname, const std::string& ruleFilename, IDrawBase* pTransObj, TransDirection dir, float transTime) :
	IBaseObject(parent, objectname),
	cTransition(ruleFilename, pTransObj, dir, transTime),
	m_pSprite(nullptr)
{
}

//==========================================================================================
//  デストラクタ
//==========================================================================================
cTransitionObject::~cTransitionObject(void)
{
	SAFE_DELETE(m_pSprite);
}

//==========================================================================================
//  初期化
//==========================================================================================
void
cTransitionObject::
Initialize(void)
{
	IBaseObject::Initialize();
	cTransition::Initialize();
}

//==========================================================================================
//  初期化
//==========================================================================================
void cTransitionObject::Initialize(const cVector2& pos)
{
	m_vPos = pos;
	Initialize();
}

//==========================================================================================
//  更新
//==========================================================================================
void cTransitionObject::Update(void)
{
	IBaseObject::Update();
	cTransition::Update();

}

//==========================================================================================
//  解放
//==========================================================================================
IBaseObject* cTransitionObject::Finalize(void)
{
	IBaseObject::Finalize();
	cTransition::Finalize();
	return this;
}