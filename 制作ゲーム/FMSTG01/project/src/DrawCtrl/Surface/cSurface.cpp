/*==============================================================================*/
/*																				*/
/*	@file title	:	cSurface.cpp												*/
/*  @brief		:	サーフェイスクラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/02/26													*/
/*																				*/
/*==============================================================================*/

#include <DxLib.h>
#include "cSurface.h"
#include "..\cDrawCtrl.h"

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cSurface::cSurface(void) :
	IDrawBase(),
	m_vAngle( 0.0f,0.0f,0.0f ),
	m_vCenter(0.0f, 0.0f),
	m_vScale(1.0f, 1.0f),
	m_Rect({ 0,0,0,0 }),
	m_nBlendMode(DX_BLENDMODE_ALPHA)
{
	// サーフェイスはオブジェクト削除時にメモリからアンロードする
	m_bUnload = true;
}
//==========================================================================================
//  デストラクタ
//==========================================================================================
cSurface::~cSurface()
{
	Delete();
}
//==========================================================================================
//  サーフェイス作成
//==========================================================================================
void cSurface::Create(int width, int height, int beginPriority,int endPriority, bool alpha)
{
	// 描画情報を登録
	cDrawCtrl::GetInstance().RegistSurface(*this,width,height,alpha);

	m_Rect.left = 0;
	m_Rect.top = 0;
	m_Rect.right = width;
	m_Rect.bottom = height;
	m_vCenter.x = width / 2.0f;
	m_vCenter.y = height/ 2.0f;

	SetPriority(endPriority);
	m_cBeginPoint.SetPriority(beginPriority);
}
//==========================================================================================
//  サーフェイス解放
//==========================================================================================
void cSurface::Delete(void)
{
	// 描画情報の登録抹消
	cDrawCtrl::GetInstance().RemoveSurface(this);
}
