/*==============================================================================*/
/*																				*/
/*	@file title	:	cGame.cpp													*/
/*  @brief		:	ゲームクラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/11/14													*/
/*																				*/
/*==============================================================================*/

#include "cGame.h"
#include "SoundCtrl\cSoundCtrl.h"
#include "DrawCtrl\cDrawCtrl.h"
#include "MovieManager/cMovieManager.h"
#include "Input\cControllerManager.h"
#include "CsvReader\cCsvReader.h"
#include "ScoreManager\cScoreManager.h"
#include "SceneManager\cSceneManager.h"
#include "Pause\cPause.h"
#include <time.h>
#include "Utility\memory.h"
#include "Utility\utility.h"

#ifdef DEBUG
#include "DebugFunc\cDebugFunc.h"
#endif

cGame::~cGame()
{
}
//==========================================================================================
//  初期化
//==========================================================================================
void cGame::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "Game";

	// FPS
	m_nFPS = DEFAULT_FPS;

	// 1フレーム内の更新回数
	m_nOneFrameUpdate = 1;

	// プレイエリアの設定(UI表示領域があることを想定)
	m_PlayArea = { 0,0,PLAYAREA_RIGHT,PLAYAREA_BOTTOM };

	// 描画操作クラス
	AddChild(&cDrawCtrl::GetInstance());

	// 動画管理クラス
	AddChild(&cMovieManager::GetInstance());

	// サウンド操作クラス
	AddChild(&cSoundCtrl::GetInstance());
	// 全サウンドの読み込み
	cSoundCtrl::GetInstance().LoadAll();

	// 入力管理クラス
	AddChild(&cControllerManager::GetInstance());

	// CSV読み込みクラス
	AddChild(&cCsvReader::GetInstance());

	// スコア管理クラス
	AddChild(&cScoreManager::GetInstance());

	// シーンマネージャークラス
	AddChild(&cSceneManager::GetInstance());

	// ポーズクラス
	AddChild(&cPause::GetInstance());

#ifdef DEBUG
	// デバッグ機能クラス
	AddChild(&cDebugFunc::GetInstance());
#endif

	IBaseObject::Initialize();
}
//==========================================================================================
//  更新
//==========================================================================================
void cGame::Update(void)
{
	if (cMovieManager::GetInstance().GetPlayState() == cMovieManager::PlayState::STATE_PLAY)
	{
		// ムービー再生
		cMovieManager::GetInstance().Play();

		// 入力を取るために更新する
		cControllerManager::GetInstance().Update();

		// いずれかのキーが押されたらムービー終了
		if (cControllerManager::GetInstance().CheckTriger(cControllerManager::KEY_ANY))
			cMovieManager::GetInstance().Stop();
	}
	else if (cPause::GetInstance().IsPause())
	{
		// ポーズ中

		// 入力を取るために更新する
		cControllerManager::GetInstance().Update();

		// ポーズクラスの更新
		cPause::GetInstance().Update();

		// ポーズ解除
		if (cControllerManager::GetInstance().CheckTriger(cControllerManager::KEY_PAUSE))
			cPause::GetInstance().EndPause();
	}
	else
	{
		for (int i = 0; i < m_nOneFrameUpdate; i++)
		{
			// 通常の更新
			IBaseObject::Update();
		}
	}
}
//==========================================================================================
//  描画
//==========================================================================================
void cGame::Draw(void)
{
	// 描画
	cDrawCtrl::GetInstance().Draw();

#ifdef DEBUG
	cDebugFunc::GetInstance().Draw();
#endif
}
//==========================================================================================
//  終了
//==========================================================================================
IBaseObject* cGame::Finalize(void)
{
	IBaseObject::Finalize();

	return nullptr;
}

//==========================================================================================
// 乱数の発生
//==========================================================================================
int cGame::Random(int min, int max)
{
	static unsigned int cnt = 0;
	int range;

	if (cnt == 0) {
		srand((unsigned int)time(NULL));
		cnt = 1;
	}
	if( min >= max ) return 0;
	range = max - min + 1;
	return((rand() % range) + min);
}
