#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cPause.h													*/
/*  @brief		:	ポーズクラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/01/16													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseSingleton.h"

class cPause : public IBaseSingleton<cPause>
{
public:
	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 破棄
	IBaseObject* Finalize(void);

	// ポーズ中かどうかを取得
	inline bool IsPause(void) { return m_bPause; };


	// ポーズ状態の開始
	void StartPause( void );

	// ポーズ状態の終了
	void EndPause( void );
private:
	enum PauseState
	{
		PAUSE_STATE_START,
		PAUSE_STATE_WAIT
	};

	// 状態別処理
	void Start( void );
	void Wait( void );

	static const int   PRIORITY = 4000;				// 表示優先度
	static const unsigned int MASK_MAX_ALPHA = 140;	// マスクの最大透明度
	static const int	PAUSE_COMP_TIME = 60;			// ポーズ完了時間

	static const float FONT_POS_X;
	static const float FONT_POS_Y;
	static const unsigned int FONT_COLOR;


	bool		m_bPause;			// ポーズ中かどうか
	int			m_nPauseCount;		// ポーズ開始からの経過時間
	PauseState  m_ePauseState;		// ポーズ画面の状態
};