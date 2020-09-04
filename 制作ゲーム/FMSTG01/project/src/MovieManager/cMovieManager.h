#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cMovieManager.h												*/
/*  @brief		:	動画管理クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/03/06													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseSingleton.h"
#include "MovieID.h"

class cMovieManager : public IBaseSingleton<cMovieManager>
{
public:
	// 動画の再生状態
	enum PlayState {
		STATE_WAIT = 0,
		STATE_PLAY,
		STATE_STOP,
	};

	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 破棄
	IBaseObject* Finalize(void);

	// 動画ファイルの読み込み
	void Load(std::string filename);
	void Load(MovieID id);

	// 動画の再生開始
	void Start( void );

	// 動画の再生
	void Play(void);

	// 動画の停止
	void Stop(void);

	// 動画データの解放
	void Unload( void );

	// 動画の再生状態を取得
	inline PlayState GetPlayState(void) { return m_ePlayState; };

private:
	int			m_nGraphHandle;		// 動画ファイルのハンドル
	PlayState	m_ePlayState;		// 動画の再生状態

	// 動画再生中の実行速度
	static const int PLAYMOVIE_FPS = 30;
	// ハンドル未取得
	static const int LOADMOVIE_NONE = -1;

	// 動画ファイル名テーブル
	std::string MOVIEFILE_TABLE[MOVIE_MAX] =
	{
		"data\\movie\\Start.avi",
	};
};