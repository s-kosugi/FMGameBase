#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cMovieManager.h												*/
/*  @brief		:	動画管理クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/03/06													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseObject.h"
#include "MovieID.h"

class cMovieManager : public IBaseObject
{
public:
	// 動画の再生状態
	enum class PLAYSTATE {
		WAIT = 0,
		PLAY,
		STOP,
	};

	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 破棄
	IBaseObject* Finalize(void);

	// 動画ファイルの読み込み
	void Load(std::string filename);
	void Load(MOVIEID id);

	// 動画の再生開始
	void Start( void );

	// 動画の再生
	void Play(void);

	// 動画の停止
	void Stop(void);

	// 動画データの解放
	void Unload( void );

	// 動画の再生状態を取得
	PLAYSTATE GetPlayState(void);// { return m_ePlayState; };

private:
	int			m_nGraphHandle;		// 動画ファイルのハンドル
	PLAYSTATE	m_ePlayState;		// 動画の再生状態

	// 動画再生中の実行速度
	static const int PLAYMOVIE_FPS = 30;
	// ハンドル未取得
	static const int LOADMOVIE_NONE = -1;

	// 動画ファイル名テーブル
	std::string MOVIEFILE_TABLE[(int)MOVIEID::MOVIE_MAX] =
	{
		""
	};

//-----------------------------------------------------------------------------------------------------
// シングルトン用
private:
	cMovieManager(void);     //  他からの生成を禁止
	cMovieManager(IBaseObject* parent);
	cMovieManager(IBaseObject* parent, const std::string& name);
	~cMovieManager(void) {};   // 他からの削除を禁止(デストラクタをprivateにする事で外部削除不可)
	cMovieManager(const cMovieManager& t);       // オブジェクトの複製禁止(コピーコンストラクタのオーバライド)
	cMovieManager& operator = (const cMovieManager& t) {};  // オブジェクトの複製禁止(代入演算子のオーバーロード)
public:

	static cMovieManager& GetInstance(void) {
		static cMovieManager instance;   // 唯一の実体であるオブジェクト、static変数を使用する事で１つの共有の変数となる
		return instance;    // 常に共通のインスタンスを返す
	};
//-----------------------------------------------------------------------------------------------------
};