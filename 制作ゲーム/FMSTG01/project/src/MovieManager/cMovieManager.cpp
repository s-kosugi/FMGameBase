/*==============================================================================*/
/*																				*/
/*	@file title	:	cMovieManager.cpp											*/
/*  @brief		:	動画管理クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/03/06													*/
/*																				*/
/*==============================================================================*/

#include "cMovieManager.h"
#include "..\cGame.h"
#include <DxLib.h>


//==========================================================================================
// 定数

//==========================================================================================
// 初期化
//==========================================================================================
void cMovieManager::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "MovieManager";
	m_ePlayState = STATE_WAIT;
	m_nGraphHandle = LOADMOVIE_NONE;

	IBaseObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cMovieManager::Update(void)
{
	IBaseObject::Update();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject * cMovieManager::Finalize(void)
{
	IBaseObject::Finalize();

	Unload();

	return nullptr;
}
//==========================================================================================
// 動画ファイルの読み込み
//==========================================================================================
void cMovieManager::Load(std::string filename)
{
	// 既に読み込まれている動画がある場合は削除してからロード
	if (m_nGraphHandle != LOADMOVIE_NONE) DeleteGraph(m_nGraphHandle);

	m_nGraphHandle = LoadGraph(filename.c_str());
	m_ePlayState = STATE_WAIT;
}
//==========================================================================================
// 動画ファイルの読み込み
//==========================================================================================
void cMovieManager::Load(MovieID id)
{
	Load(MOVIEFILE_TABLE[id]);
}
//==========================================================================================
// 動画の再生開始
//==========================================================================================
void cMovieManager::Start(void)
{
	if ( m_nGraphHandle == LOADMOVIE_NONE ) return;

	if (0 == GetMovieStateToGraph(m_nGraphHandle) && m_ePlayState == STATE_WAIT)
	{
		// 再生開始
		PlayMovieToGraph(m_nGraphHandle);
		m_ePlayState = STATE_PLAY;
	}
}
//==========================================================================================
// 動画データの再生
//==========================================================================================
void cMovieManager::Play(void)
{
	if( m_nGraphHandle == LOADMOVIE_NONE ) return;

	// 動画再生中は実行速度を落とす
	cGame::GetInstance().SetFPS(PLAYMOVIE_FPS);

	// 再生終了	
	if(0 == GetMovieStateToGraph(m_nGraphHandle))
	{
		// 動画が終了したので停止
		Stop();
		return;
	}
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	SetDrawBright(255, 255, 255);
	
	// 動画の描画
	DrawExtendGraph(0,0,cGame::GetInstance().GetWindowWidth(),cGame::GetInstance().GetWindowHeight(),m_nGraphHandle,FALSE);

}
//==========================================================================================
// 動画停止
//==========================================================================================
void cMovieManager::Stop(void)
{
	m_ePlayState = STATE_STOP;
	cGame::GetInstance().ResetFPS();

	Unload();
}
//==========================================================================================
// 動画データの解放
//==========================================================================================
void cMovieManager::Unload(void)
{
	if (m_nGraphHandle != LOADMOVIE_NONE) DeleteGraph(m_nGraphHandle);
	m_nGraphHandle = LOADMOVIE_NONE;
}
