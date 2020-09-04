/*==============================================================================*/
/*																				*/
/*	@file title	:	cSprite.cpp													*/
/*  @brief		:	スプライトクラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/09/17													*/
/*																				*/
/*==============================================================================*/

#include "cSprite.h"
#include "..\cDrawCtrl.h"
#include "Utility/StrControl/StrControl.h"

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cSprite::cSprite(const std::string& filename):
	m_SrcRect({ 0,0,0,0 }),
	m_vCenter( 0.0f,0.0f ),
	m_vAnchor( 0.0f,0.0f ),
	m_vScale( 1.0f,1.0f ),
	m_BlendMode(DX_BLENDMODE_ALPHA),
	m_fAngle(0.0f),
	IDrawBase(filename)
{
	// ASSファイルでない場合にはそのまま描画情報を登録
	if (!Ends_With(filename, ".ass"))
		cDrawCtrl::GetInstance().RegistDrawObject(*this,filename);
}

//==========================================================================================
//  デストラクタ
//==========================================================================================
cSprite::~cSprite(void)
{
}

//==========================================================================================
//  初期化
//==========================================================================================
void
cSprite::
Initialize(void)
{
	IDrawBase::Initialize();
}

//==========================================================================================
//  更新
//==========================================================================================
void cSprite::Update(void)
{
	IDrawBase::Update();
}
//==========================================================================================
//  解放
//==========================================================================================
void cSprite::Finalize(void)
{
	IDrawBase::Finalize();
}
//==========================================================================================
// スプライトの矩形情報をセット
//==========================================================================================
void cSprite::SetSrcRect(RECT rect)
{
	m_SrcRect = rect;
	// Rectが変わったのでスプライトの中心位置を自動的に変える
	SetCenter(GetSpriteSize().x / 2.0f, GetSpriteSize().y / 2.0f);
}
//==========================================================================================
// スプライトの矩形情報をセット
//==========================================================================================
void cSprite::SetSrcRect(int Startx, int Starty, int Sizex, int Sizey)
{
	m_SrcRect.left = Startx;
	m_SrcRect.right = m_SrcRect.left + Sizex;
	m_SrcRect.top = Starty;
	m_SrcRect.bottom = m_SrcRect.top + Sizey;

	// Rectが変わったのでスプライトの中心位置を自動的に変える
	SetCenter( GetSpriteSize().x / 2.0f, GetSpriteSize().y / 2.0f );
}

//=========================================================================
// スプライトのサイズの取得
// return POINT
//=========================================================================
POINT cSprite::GetSpriteSize(void)
{
	POINT pt;
	pt.x = 0;
	pt.y = 0;
	if (IsFileLoaded())
	{
		pt.x = (m_SrcRect.right - m_SrcRect.left);
		pt.y = (m_SrcRect.bottom - m_SrcRect.top);
	}
	else
	{
		//ErrorLogAdd("GetSpriteSize Error! m_nGraphHandle is None\n");
	}
	return pt;
}