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

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cSprite::cSprite(const std::string& filename) :
	m_SrcRect({ 0,0,0,0 }),
	m_vCenter( 0.0f,0.0f ),
	m_vScale( 1.0f, 1.0f ),
	m_BlendMode(DX_BLENDMODE_ALPHA),
	m_fStartAngle(0.0f),
	m_fEndAngle(0.0f),
	m_fAngle(0.0f),
	m_Animation({ {0,0},{0,0},0,0,0,0 }),
	m_eSpType(SPTYPE_NORMAL),
	IDrawBase(filename)
{
	// 描画情報を登録
	cDrawCtrl::GetInstance().RegistDrawObject(*this,filename);
}

//==========================================================================================
//  デストラクタ
//==========================================================================================
cSprite::~cSprite(void)
{
	cDrawCtrl::GetInstance().RemoveDrawObject(this);
}

//==========================================================================================
//  初期化
//==========================================================================================
void
cSprite::
Initialize(void)
{
	// アニメーションがセットされていたら表示画像を更新する
	if ( 0 < m_Animation.AnimMax) {
		// 表示座標更新
		m_SrcRect.left = m_Animation.StartPos.x + m_Animation.AnimFrame * m_Animation.Size.x;
		m_SrcRect.right = m_SrcRect.left + m_Animation.Size.x;
		m_SrcRect.top = m_Animation.StartPos.y;
		m_SrcRect.bottom = m_SrcRect.top + m_Animation.Size.y;

		// アニメーションがセットされていたら中心位置を変更する。(小数点以下四捨五入)
		m_vCenter.x = (float)((int)(m_Animation.Size.x / 2.0f + 0.5f));
		m_vCenter.y = (float)((int)(m_Animation.Size.y / 2.0f + 0.5f));
	}
	IDrawBase::Initialize();
}

//==========================================================================================
//  更新
//==========================================================================================
void cSprite::Update(void)
{
	// アニメーションがセットされてる物のみアニメーション処理をする
	if ( 0 < m_Animation.AnimMax) {
		if (m_Animation.TimerCount >= m_Animation.AnimTime)
		{
			// アニメーション更新
			++m_Animation.AnimFrame %= m_Animation.AnimMax;
			// タイマーリセット
			m_Animation.TimerCount = 0;

			// 表示座標更新
			m_SrcRect.left = m_Animation.StartPos.x + m_Animation.AnimFrame * m_Animation.Size.x;
			m_SrcRect.right = m_SrcRect.left + m_Animation.Size.x;
			m_SrcRect.top = m_Animation.StartPos.y;
			m_SrcRect.bottom = m_SrcRect.top + m_Animation.Size.y;
		}
		m_Animation.TimerCount++;
	}
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
void cSprite::SetSrcRect(int Startx, int Starty, int Sizex, int Sizey)
{
	m_SrcRect.left = Startx;
	m_SrcRect.right = m_SrcRect.left + Sizex;
	m_SrcRect.top = Starty;
	m_SrcRect.bottom = m_SrcRect.top + Sizey;
}
//==========================================================================================
// アニメーション情報のセット
//==========================================================================================
void cSprite::SetAnimation(int Startx, int Starty, int width, int height, short AnimMax, short AnimTime)
{
	Animation anim;
	anim.StartPos.x = Startx;
	anim.StartPos.y = Starty;
	anim.Size.x = width;
	anim.Size.y = height;
	anim.AnimMax = AnimMax;
	anim.AnimTime = AnimTime;
	anim.AnimFrame = 0;
	anim.TimerCount = 0;
	m_Animation = anim;
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