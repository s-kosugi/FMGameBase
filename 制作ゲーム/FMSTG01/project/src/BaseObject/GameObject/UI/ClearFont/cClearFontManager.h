#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cClearFontManager.h											*/
/*  @brief		:	ゲームクリア文字管理										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/30													*/
/*																				*/
/*==============================================================================*/

#include "..\cUIObject.h"

//================================================================================================
// ゲームクリア文字管理クラス
class cClearFontManager : public cUIObject
{
public:
	cClearFontManager(IBaseObject* parent);
	~cClearFontManager(void);


	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// 文字出現開始
	inline void StartPop(void) { m_eState = STATE_FONT_POP; };

private:

	enum CFONT_STATE
	{
		STATE_WAIT = -1,
		STATE_FONT_POP = 0,
		STATE_TIMEBONUS_POP,
		STATE_BONUS_RANDSHOW,
		STATE_COMP_WAIT,
		STATE_SCORE_POP,
	};

	void Pop(void);
	void TimeBonusPop(void);
	void CompWait(void);
	void BonusRandShow(void);
	void ScorePop(void);

	int						m_nCounter;
	CFONT_STATE				m_eState;
	RECT					m_ClearFontRect;


	static const float		CLEARFONT_POS_X;
	static const float		CLEARFONT_POS_Y;
	static const float		TIMEBONUSFONT_POS_X;
	static const float		TIMEBONUSFONT_POS_Y;
	static const float		SCOREFONT_POS_X;
	static const float		SCOREFONT_POS_Y;
	static const int		COMP_WAIT_TIME = 180;
};
//================================================================================================