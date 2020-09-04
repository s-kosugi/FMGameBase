/*==============================================================================*/
/*																				*/
/*	@file title	:	cDebugFunc.cpp												*/
/*  @brief		:	デバッグ機能クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/03/24													*/
/*																				*/
/*==============================================================================*/
#ifdef DEBUG

#include "cDebugFunc.h"
#include "..\cGame.h"
#include "..\Input\Keyboard\cKeyboard.h"
#include "..\SceneManager\cSceneManager.h"
#include "DrawCtrl/cDrawCtrl.h"
#include <sstream>
#include "EffekseerForDXLib.h"

//==========================================================================================
// 定数
//==========================================================================================
const int cDebugFunc::FPS_MODE_MAX = 5;
const int cDebugFunc::FONT_SIZE = 15;
const int cDebugFunc::LOG_MAX = 30;

//==========================================================================================
//  初期化
//==========================================================================================
void cDebugFunc::Initialize(void)
{
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

	// スクリーンショット保存
	SaveScreenShot();
}

//==========================================================================================
//  描画
//==========================================================================================
void cDebugFunc::Draw(void)
{
	DebugPrint();
}
//==========================================================================================
// デバッグログを追加
//==========================================================================================
void cDebugFunc::PushDebugLog(std::string str)
{
	m_listLog.push_front(str);
	str += "\n";
	str = "[" + std::to_string(m_nLogNum)+"] "+ str;
	LogFileAdd(str.c_str());
	m_nLogNum++;
}
//==========================================================================================
// デバッグログを追加
//==========================================================================================
void cDebugFunc::PushDebugLog(std::string str, float num)
{
	std::ostringstream oss;
	oss << str << " " << num;

	PushDebugLog(oss.str());
}
//==========================================================================================
// デバッグログを追加
//==========================================================================================
void cDebugFunc::PushDebugLog(std::string str, int num)
{
	std::ostringstream oss;
	oss << str << " " << num;

	PushDebugLog(oss.str());
}
//==========================================================================================
// 円描画登録(1フレーム間描画)
// pos   : 指定ポイント
// range : 指定ポイントからの範囲
// color : 描画色(ARGB)
//==========================================================================================
void cDebugFunc::RegistDrawCircle(const cVector2 & pos, float range,unsigned int color)
{
	DebugCircle circle;
	circle.pos = pos;
	circle.range = range;
	circle.color = color;
	m_listDrawCircle.push_back(circle);
}
//==========================================================================================
// 矩形描画登録(1フレーム間描画)
// pos   : 指定ポイント
// range : 指定ポイントからの範囲
// color : 描画色(ARGB)
//==========================================================================================
void cDebugFunc::RegistDrawBox(const cVector2 & pos, POINT range,unsigned int color)
{
	DebugBox box;
	box.pos = pos;
	box.range = range;
	box.color = color;
	m_listDrawBox.push_back(box);
}
//==========================================================================================
// デバッグ用更新速度変更
//==========================================================================================
void cDebugFunc::DebugChangeUpdateSpeed(void)
{
	// FPSモードの変更
	if (cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_F2))
	{
		m_nFPSMode = 0;
	}
	if (cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_F3))
	{
		m_nFPSMode++;
	}
	if (cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_F4))
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
	}
	else if (m_nFPSMode == 0)
	{
		cGame::GetInstance().SetFPS(60);
		cGame::GetInstance().SetOneFrameUpdate(1);
	}
	else if (m_nFPSMode < 0)
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
	if (cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_F11))
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
	if (cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_F1))
	{
		m_eDebugPrintMode = (PRINTMODE)(((int)m_eDebugPrintMode + 1) % (int)PRINTMODE::MAX);
	}

	if (m_eDebugPrintMode <= PRINTMODE::LOG)
	{
		// デバッグ図形の描画
		DrawShape();

		// 文字色
		unsigned int nPrintColor = GetColor(255, 255, 255);


		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawBright(255, 255, 255);

		//------------------------------------------------------------------------
		// フレームレート表示
		DrawFormatStringToHandle(cGame::GetInstance().GetWindowWidth() - 75, cGame::GetInstance().GetWindowHeight() - 16,
								 nPrintColor,
								 m_nDebugFontHandle,
								 "%2.2fFPS", (float)((double)m_fFrameLate * cGame::GetInstance().GetOneFrameUpdate()));
		//------------------------------------------------------------------------
		// マウス座標の表示
		//cMouse mouse = cMouse::GetInstance();
		//POINT mspt = mouse.GetPoint();

		//DrawFormatString(GetWindowWidth() - 120, GetWindowHeight() - 48, nPrintColor, "Mouse.x %d", mspt.x);
		//DrawFormatString(GetWindowWidth() - 120, GetWindowHeight() - 32, nPrintColor, "Mouse.y %d", mspt.y);

		//------------------------------------------------------------------------
		// シーンIDの表示
		cSceneManager& sm = cSceneManager::GetInstance();
		DrawFormatStringToHandle(cGame::GetInstance().GetWindowWidth() - 100, cGame::GetInstance().GetWindowHeight() - 64,
								nPrintColor,
								m_nDebugFontHandle,
								"SceneID %d", sm.GetCurrentSceneID());
		//------------------------------------------------------------------------
		// エフェクト総数の表示
		Effekseer::Manager* efMan = GetEffekseer2DManager();
		int efNum = efMan->GetTotalInstanceCount();
		DrawFormatStringToHandle(cGame::GetInstance().GetWindowWidth() - 190, cGame::GetInstance().GetWindowHeight() - 80,
			nPrintColor,
			m_nDebugFontHandle,
			"EffectInstance %4d", efNum);

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

				DrawFormatStringToHandle(0, cGame::GetInstance().GetWindowHeight() - FONT_SIZE * (i + 1),
					nPrintColor,
					m_nDebugFontHandle,
					("[" + std::to_string(m_nLogNum - i) + "]" + ":" + (*it)).c_str() );

				i++;
				it++;
			}
		}

		// ヘルプの表示
		if (m_eDebugPrintMode == PRINTMODE::ALL)
		{
			std::string str;
			DrawStringToHandle(cGame::GetInstance().GetWindowWidth() - 250, 0, " F1  : デバッグ表示の切り替え", nPrintColor, m_nDebugFontHandle);
			DrawStringToHandle(cGame::GetInstance().GetWindowWidth() - 250, 15, " F2  : FPSリセット", nPrintColor, m_nDebugFontHandle);
			DrawStringToHandle(cGame::GetInstance().GetWindowWidth() - 250, 30, " F3  : FPS増加", nPrintColor, m_nDebugFontHandle);
			DrawStringToHandle(cGame::GetInstance().GetWindowWidth() - 250, 45, " F4  : FPS減少", nPrintColor, m_nDebugFontHandle);
			DrawStringToHandle(cGame::GetInstance().GetWindowWidth() - 250, 60, " F11 : シーンリセット", nPrintColor, m_nDebugFontHandle);
			DrawStringToHandle(cGame::GetInstance().GetWindowWidth() - 250, 75, " PrtScr : スクリーンショット", nPrintColor, m_nDebugFontHandle);
		}
	}
	// デバッグ図形リストのクリア
	m_listDrawBox.clear();
	m_listDrawCircle.clear();
}
//==========================================================================================
// デバッグ図形描画
//==========================================================================================
void cDebugFunc::DrawShape(void)
{
	// 矩形の描画
	if (!m_listDrawBox.empty())
	{
		for (auto it = m_listDrawBox.begin();it != m_listDrawBox.end();it++)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).color >> 24);
			SetDrawBright(255, 255, 255);
			DrawBox((int)((*it).pos.x - (*it).range.x / 2),
				    (int)((*it).pos.y - (*it).range.y / 2),
					(int)((*it).pos.x + (*it).range.x / 2),
					(int)((*it).pos.y + (*it).range.y / 2),
					(*it).color,
					true);
		}
	}
	// 円の描画
	if (!m_listDrawCircle.empty())
	{
		for (auto it = m_listDrawCircle.begin();it != m_listDrawCircle.end();it++)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).color >> 24);
			SetDrawBright(255, 255, 255);
			DrawCircle((int)((*it).pos.x),
					   (int)((*it).pos.y),
					   (int)((*it).range),
					   (*it).color);
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

//==========================================================================================
// 現在フレームのスクリーンショットを保存する
//==========================================================================================
void cDebugFunc::SaveScreenShot(void)
{
	if (cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_SYSRQ))
	{
		cDrawCtrl::GetInstance().RequestScreenShot();
	}
}

//==========================================================================================
// コンストラクタ
//==========================================================================================
cDebugFunc::cDebugFunc(void) :
	m_nStartTime(0),
	m_nFrameCount(0),
	m_fFrameLate(0.0f),
	m_nMaxLog(LOG_MAX),
	m_nLogNum(0),
	m_eDebugPrintMode(PRINTMODE::ALL),
	m_nFPSMode(0),
	m_nDebugFontHandle(-1)
{
	m_nStartTime = GetNowCount();
	m_nDebugFontHandle = CreateFontToHandle("DebugFont", FONT_SIZE,-1, DX_FONTTYPE_NORMAL);
	m_listLog.clear();
	m_listDrawCircle.clear();
	m_listDrawBox.clear();
}
//==========================================================================================
// コンストラクタ
//==========================================================================================
cDebugFunc::cDebugFunc(IBaseObject* parent) :
	cDebugFunc::cDebugFunc()
{
}
//==========================================================================================
// コンストラクタ
//==========================================================================================
cDebugFunc::cDebugFunc(IBaseObject* parent, const std::string& name) :
	cDebugFunc::cDebugFunc(parent)
{
}
//==========================================================================================
// コピーコンストラクタ
//==========================================================================================
cDebugFunc::cDebugFunc(const cDebugFunc& t) :
	cDebugFunc::cDebugFunc()
{
}

#endif // DEBUG