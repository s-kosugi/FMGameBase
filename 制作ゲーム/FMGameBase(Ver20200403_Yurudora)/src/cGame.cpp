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
#include "Input\Keyboard\cKeyboard.h"
#include "BaseObject/GameObject/Effect/cEffectManager.h"
#include "SceneManager\cSceneManager.h"
#include "Utility\CsvReader\cCsvReader.h"
#include "DrawCtrl/Camera/cCamera.h"
#include "ScoreManager/cScoreManager.h"
#include <time.h>
#include "Utility\memory.h"

#ifdef DEBUG
#include "DebugFunc/cDebugFunc.h"
#endif // DEBUG

//==========================================================================================
// 定数
//==========================================================================================
const float             cGame::MAX_DELTA_TIME = 0.16f;		// 最大デルタタイム
const float				cGame::ONE_MILL_SECOND = 1000.0f;	// １秒
const int				cGame::CALC_FRAME_COUNT = 60;		// 平均を計算するフレームの数
const int				cGame::WINDOW_SIZE_X = 1280;		// ウィンドウ幅
const int				cGame::WINDOW_SIZE_Y = 720;			// ウィンドウ高さ

//==========================================================================================
//  初期化
//==========================================================================================
void cGame::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE::ACTIVE;
	m_sObjectName = "Game";

	// ウィンドウの初期位置を覚えておく
	int x, y = 0;
	GetWindowPosition(&x, &y);
	m_DefaultWindowPos = { x , y };

	// 描画操作クラス
	AddChild(&cDrawCtrl::GetInstance());

	// エフェクトマネージャーの追加
	AddChild( &cEffectManager::GetInstance() );

	// 動画管理クラス
	AddChild(&cMovieManager::GetInstance());

	// サウンド操作クラス
	AddChild(&cSoundCtrl::GetInstance());
	// 全サウンドの読み込み
	cSoundCtrl::GetInstance().LoadAll();

	// 入力管理クラス
	AddChild(&cControllerManager::GetInstance());

	// シーンマネージャークラス
	AddChild(&cSceneManager::GetInstance());

	// Csv読込クラス
	AddChild(&cCsvReader::GetInstance());

	// カメラクラス
	AddChild(&cCamera::GetInstance());

	// スコア管理クラス
	CreateObject<cScoreManager>(this);

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
	// フレームカウント算出
	CalcFrameCount();

	for (int i = 0; i < m_nOneFrameUpdate; i++)
	{
		// 通常の更新
		IBaseObject::Update();
	}

	// システムキーのチェック
	CheckSystemKey();
}
//==========================================================================================
//  描画
//==========================================================================================
void cGame::Draw(void)
{
	cDrawCtrl::GetInstance().Draw();
#ifdef DEBUG
	cDebugFunc::GetInstance().Draw();
#endif
}

//==========================================================================================
// 乱数の発生
//==========================================================================================
int cGame::Random(int min, int max)
{
	int range;

	range = max - min;
	return GetRand(range) + min;
}
//==========================================================================================
// ウィンドウの位置を原点にする
//==========================================================================================
void cGame::SetWindowPosOrigin(void)
{
	SetWindowPosition(0, 0);
}

//==========================================================================================
// ウィンドウの位置を初期位置にする。
//==========================================================================================
void cGame::SetWindowPosDefault(void)
{
	SetWindowPosition(m_DefaultWindowPos.x, m_DefaultWindowPos.y);
}

//==========================================================================================
// 更新するフレームカウントの計算
//==========================================================================================
void cGame::CalcFrameCount(void)
{
	// 現在の時間を取得
	int now_time = GetNowCount();

	// 計算開始時
	if (m_nFrameCount == 0)
	{
		m_nStartTime = now_time;
	}
	// 指定されたフレームカウント時
	else if (m_nFrameCount == CALC_FRAME_COUNT)
	{
		m_nFrameCount = 0;

		m_nStartTime = now_time;
	}

	// フレームカウントを更新
	++m_nFrameCount;

	// 前の処理との時間の差
	int sub_time = now_time - m_nPrevTime;

	// デルタタイムを算出
	m_fDeltaTime = (float)sub_time / ONE_MILL_SECOND;

	// 最大デルタタイムで制限する
	if (m_fDeltaTime > MAX_DELTA_TIME) m_fDeltaTime = MAX_DELTA_TIME;

	// 今の時間を保存
	m_nPrevTime = now_time;
}
//==========================================================================================
// システムキーのチェック
//==========================================================================================
void cGame::CheckSystemKey(void)
{
	// ALT+Enterでウィンドウ位置の切り替え
	if (cKeyboard::GetInstance().CheckButton(KEY_INPUT_LALT) || cKeyboard::GetInstance().CheckButton(KEY_INPUT_RALT))
	{
		if (cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_RETURN)) ChangeWindowPos();
	}
	// Escキーでゲームの終了
	if (cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_ESCAPE))
	{
		PostQuitMessage(0);
	}
}

//==========================================================================================
// ウィンドウ位置の切り替え
//==========================================================================================
void cGame::ChangeWindowPos(void)
{
	int x, y = 0;
	GetWindowPosition(&x, &y);
	if (x == m_DefaultWindowPos.x && y == m_DefaultWindowPos.y)
	{
		SetWindowPosOrigin();
	}
	else
	{
		SetWindowPosDefault();
	}
}

//==========================================================================================
// コンストラクタ
//==========================================================================================
cGame::cGame(void):
	m_nFPS(DEFAULT_FPS),
	m_nOneFrameUpdate(1),
	m_fDeltaTime(0.0f),
	m_fDeltaTimeScale(1.0f),
	m_nFrameCount(0),
	m_nStartTime(0),
	m_nPrevTime(0),
	m_PlayArea({ 0,0,GetWindowWidth(),GetWindowHeight() })
{
}

//==========================================================================================
// コンストラクタ
//==========================================================================================
cGame::cGame(IBaseObject* parent):
	cGame::cGame()
{
}

//==========================================================================================
// コンストラクタ
//==========================================================================================
cGame::cGame(IBaseObject* parent, const std::string& name):
	cGame::cGame(parent)
{
}

//==========================================================================================
// コピーコンストラクタ
//==========================================================================================
cGame::cGame(const cGame& t):
	cGame::cGame()
{
}
