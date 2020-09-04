/*==============================================================================*/
/*																				*/
/*	@file title	:	cEffect.cpp													*/
/*  @brief		:	エフェクトオブジェクトクラス								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/09/17													*/
/*																				*/
/*==============================================================================*/

#include "cEffect.h"
#include "..\cDrawCtrl.h"

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cEffect::cEffect(const std::string& filename) :
	m_vAngle( 0.0f,0.0f,0.0f ),
	m_vScale( 1.0f, 1.0f,1.0f ),
	m_nPlayingEffectHandle(-1),
	IDrawBase(filename)
{
	// 描画情報を登録
	cDrawCtrl::GetInstance().RegistDrawObject(*this, filename);
}

//==========================================================================================
//  デストラクタ
//==========================================================================================
cEffect::~cEffect(void)
{
	cDrawCtrl::GetInstance().RemoveDrawObject(this);
}

//==========================================================================================
//  初期化
//==========================================================================================
void
cEffect::
Initialize(void)
{
	IDrawBase::Initialize();
}

//==========================================================================================
//  更新
//==========================================================================================
void cEffect::Update(void)
{
	IDrawBase::Update();
}

//==========================================================================================
//  解放
//==========================================================================================
void cEffect::Finalize(void)
{
	IDrawBase::Finalize();
}