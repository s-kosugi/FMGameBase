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
#pragma warning(disable: 26495)
#include "EffekseerForDXLib.h"

//==========================================================================================
//  コンストラクタ
//==========================================================================================
cEffect::cEffect(const std::string& filename) :
	m_vAngle( 0.0f,0.0f,0.0f ),
	m_vScale( 1.0f,1.0f,1.0f ),
	m_nPlayingEffectHandle(-1),
	IDrawBase(filename),
	m_bLoop( false ),
	m_bStop( false ),
	m_ePlayScene(SCENE_ID::NONE)
{
	// 描画情報を登録
	cDrawCtrl::GetInstance().RegistDrawObject(*this, filename);
}

//==========================================================================================
//  デストラクタ
//==========================================================================================
cEffect::~cEffect(void)
{
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

//==========================================================================================
//  エフェクトの停止
//==========================================================================================
void cEffect::Stop( void )
{
	m_bStop = true;
}

//==========================================================================================
// エフェクトが再生終了したかどうか
//==========================================================================================
bool cEffect::IsEffectEnd(void)
{
	return IsEffekseer2DEffectPlaying(m_nPlayingEffectHandle) == -1 && m_nPlayingEffectHandle != -1 ? true : false;
}
//==========================================================================================
//  再生シーンのセット
//==========================================================================================
inline void cEffect::SetPlayScene(SCENE_ID id)
{
	m_ePlayScene = id;
}
