/*==============================================================================*/
/*																				*/
/*	@file title	:	cDebugFunc.cpp												*/
/*  @brief		:	デバッグ機能クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/03/24													*/
/*																				*/
/*==============================================================================*/

#include <string>
#include "cDebugFunc.h"
#include "..\cGame.h"
#include "..\Input\Keyboard\cKeyboard.h"
#include "..\SceneManager\cSceneManager.h"
#include "..\Input\cControllerManager.h"

//==========================================================================================
// 定数
//==========================================================================================
const int cDebugFunc::FPS_MODE_MAX = 5;
const int cDebugFunc::FONT_SIZE = 15;

//==========================================================================================
//  デストラクタ
//==========================================================================================
cDebugFunc::~cDebugFunc()
{
}

//==========================================================================================
//  初期化
//==========================================================================================
void cDebugFunc::Initialize(void)
{
	m_nStartTime = GetNowCount();
	m_nFrameCount = 0;
	m_fFrameLate = 0.0f;

	m_listLog.clear();
	m_nMaxLog = 10;
	m_bHitVisible = false;
	m_nLogNum = 0;

	m_nDebugFontHandle = CreateFontToHandle("DebugFont", FONT_SIZE, -1, DX_FONTTYPE_NORMAL);
}

//==========================================================================================
//  更新
//==========================================================================================
void cDebugFunc::Update(void)
{
	// デバッグ用更新速度変更
	DebugChangeUpdateSpeed();

	// デバッグ用シーンリセット
	DebugSceneReset();

	// フレームレート計算
	CalcFrameRate();
}

//==========================================================================================
//  描画
//==========================================================================================
void cDebugFunc::Draw(void)
{
	DebugPrint();
}

//==========================================================================================
//  破棄
//==========================================================================================
IBaseObject * cDebugFunc::Finalize(void)
{
	DeleteFontToHandle(m_nDebugFontHandle);

	IBaseObject::Finalize();

	return nullptr;
}

//==========================================================================================
// デバッグログを追加
//==========================================================================================
void cDebugFunc::PushDebugLog(std::string str)
{
	m_listLog.push_front(str);
	str += "\n";
	str = "[" + std::to_string(m_nLogNum) + "] " + str;
	LogFileAdd(str.c_str());
	m_nLogNum++;
}

//==========================================================================================
// デバッグ用更新速度変更
//==========================================================================================
void cDebugFunc::DebugChangeUpdateSpeed(void)
{
	// FPSモードの変更
	if (cKeyboard::GetInstance().CheckTriger(KEY_INPUT_F2))
	{
		m_nFPSMode = 0;
	}
	if (cKeyboard::GetInstance().CheckTriger(KEY_INPUT_F3))
	{
		m_nFPSMode++;
	}
	if (cKeyboard::GetInstance().CheckTriger(KEY_INPUT_F4))
	{
		m_nFPSMode--;
	}
	// 最大値チェック
	if (FPS_MODE_MAX <= m_nFPSMode) m_nFPSMode = FPS_MODE_MAX;
	if (-FPS_MODE_MAX >= m_nFPSMode) m_nFPSMode = -FPS_MODE_MAX;

	// ゲーム速度の変更
	if (m_nFPSMode > 0)
	{
		cGame::GetInstance().SetFPS(60);
		cGame::GetInstance().SetOneFrameUpdate(m_nFPSMode);
	} else if (m_nFPSMode == 0)
	{
		cGame::GetInstance().SetFPS(60);
		cGame::GetInstance().SetOneFrameUpdate(1);
	} else if (m_nFPSMode < 0)
	{
		cGame::GetInstance().SetFPS(60 + m_nFPSMode * 10);
		cGame::GetInstance().SetOneFrameUpdate(1);
	}
}
//==========================================================================================
// デバッグシーンリセット
//==========================================================================================
void cDebugFunc::DebugSceneReset(void)
{
	if (cKeyboard::GetInstance().CheckTriger(KEY_INPUT_F12))
	{
		cSceneManager::GetInstance().Reset();
	}
}

//==========================================================================================
// デバッグ出力
//==========================================================================================
void cDebugFunc::DebugPrint(void)
{
	// デバッグ出力の切り替え
	if (cKeyboard::GetInstance().CheckTriger(KEY_INPUT_F1))
	{
		m_eDebugPrintMode = (DebugPrintMode)((m_eDebugPrintMode + 1) % DPRINT_MAX);
	}

	if (m_eDebugPrintMode <= DPRINT_LOG)
	{
		// 文字色
		unsigned int nPrintColor = GetColor(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawBright(255, 255, 255);

		//------------------------------------------------------------------------
		// フレームレート表示
		DrawFormatString(cGame::GetInstance().GetWindowWidth() - 75, cGame::GetInstance().GetWindowHeight() - 16, nPrintColor, "%2.2fFPS", m_fFrameLate * cGame::GetInstance().GetOneFrameUpdate());

		//------------------------------------------------------------------------
		// シーンIDの表示
		cSceneManager sm = cSceneManager::GetInstance();
		DrawFormatString(cGame::GetInstance().GetWindowWidth() - 100, cGame::GetInstance().GetWindowHeight() - 64, nPrintColor, "SceneID %d", sm.GetCurrentSceneID());

		//------------------------------------------------------------------------
		// デバッグログの表示
		if (!m_listLog.empty())
		{
			auto it = m_listLog.begin();
			auto end = m_listLog.end();
			int i = 0;
			while (it != end)
			{
				if (i >= m_nMaxLog)
				{
					it = m_listLog.erase(it);
					continue;
				}

				DrawFormatString(0, cGame::GetInstance().GetWindowHeight() - 20 * (i + 1), nPrintColor, ("[" + std::to_string(m_nLogNum - i) + "] " + " : " + (*it)).c_str());

				i++;
				it++;
			}
		}

		// ヘルプの表示
		if (m_eDebugPrintMode == DPRINT_ALL)
		{
			std::string str;
			DrawStringToHandle(cGame::GetInstance().GetWindowWidth() - 250, 0, " F1  : デバッグ表示の切り替え", nPrintColor, m_nDebugFontHandle);
			DrawStringToHandle(cGame::GetInstance().GetWindowWidth() - 250, 15, " F2  : FPSリセット", nPrintColor, m_nDebugFontHandle);
			DrawStringToHandle(cGame::GetInstance().GetWindowWidth() - 250, 30, " F3  : FPS増加", nPrintColor, m_nDebugFontHandle);
			DrawStringToHandle(cGame::GetInstance().GetWindowWidth() - 250, 45, " F4  : FPS減少", nPrintColor, m_nDebugFontHandle);
			DrawStringToHandle(cGame::GetInstance().GetWindowWidth() - 250, 60, " F12 : シーンリセット", nPrintColor, m_nDebugFontHandle);
		}
	}
	// デバッグ当たり判定の表示
	if (cControllerManager::GetInstance().CheckTriger(cControllerManager::KEY_4))
	{
		if (m_bHitVisible)
		{
			m_bHitVisible = false;
		} else
		{
			m_bHitVisible = true;
		}
	}
}

//==========================================================================================
// フレームレート計算
//==========================================================================================
void cDebugFunc::CalcFrameRate(void)
{
	// フレームレート計算
	int nNowTime = GetNowCount();
	m_nFrameCount++;
	// 1秒毎に更新
	if (nNowTime > m_nStartTime + 1000)
	{
		m_fFrameLate = m_nFrameCount / ((float)(nNowTime - m_nStartTime) / 1000.0f);
		m_nFrameCount = 0;
		m_nStartTime = nNowTime;
	}
}
