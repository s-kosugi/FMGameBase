#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cDebugFunc.h												*/
/*  @brief		:	デバッグ機能クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/03/24													*/
/*																				*/
/*==============================================================================*/

#include "DxLib.h"
#include "..\BaseObject\IBaseSingleton.h"

//===============================================================================
// デバッグ機能クラス
class cDebugFunc : public IBaseSingleton<cDebugFunc>
{
public:
	~cDebugFunc();

	void Initialize(void);
	void Update(void);
	void Draw(void);
	IBaseObject* Finalize(void);

	// デバッグ当たり判定表示切替
	bool GetDebugHitVisible(void) {return m_bHitVisible;};

	// デバッグログ追加
	void PushDebugLog(std::string str);

	// デバッグログ最大出力数設定
	inline void SetDebugLogMax(int num) { m_nMaxLog = num; };

private:
	enum DebugPrintMode
	{
		DPRINT_ALL,
		DPRINT_LOG,
		DPRINT_NO,

		DPRINT_MAX
	};

	// デバッグ用更新速度変更
	void DebugChangeUpdateSpeed(void);

	// デバッグシーンリセット
	void DebugSceneReset(void);

	// デバッグ出力
	void DebugPrint(void);

	// フレームレート計算
	void CalcFrameRate(void);

	//---------------------------------------------------------
	// フレームレート計算用
	int m_nStartTime;
	int m_nFrameCount;
	float m_fFrameLate;
	//---------------------------------------------------------

	std::list<std::string> m_listLog;		// デバッグログ
	int m_nMaxLog;							// デバッグログ最大表示行数
	int m_nLogNum;							// ログNo

	DebugPrintMode m_eDebugPrintMode;		// デバッグ表示の切り替え 0:ログ、ヘルプ表示 1:ログのみ表示 2:非表示

	int m_nFPSMode;							// 0:初期値 1:少し早い 2:速い -1:少し遅い -2:遅い

	int m_nDebugFontHandle;					// フォントのハンドル


	static const int FPS_MODE_MAX;			// 更新フレームモード最大
	static const int FONT_SIZE;				// フォントサイズ

	bool m_bHitVisible;						// 当たり判定表示有無
};