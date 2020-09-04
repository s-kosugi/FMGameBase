#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cScoreManager.h												*/
/*  @brief		:	スコア管理クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/01/13													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseSingleton.h"

class cScoreManager : public IBaseSingleton<cScoreManager>
{
public:
	// 初期化
	void Initialize(void);

	// 破棄
	IBaseObject* Finalize(void);

	// スコアリセット
	inline void ResetScore(void) { m_nCurrentScore = 0; };

	// スコア加算
	inline void AddScore(int score) { m_nCurrentScore += score; };

	inline int GetScore(void) { return m_nCurrentScore; };
	inline int GetHiScore(void) { return m_nHiScore; };
	inline int GetTimeBonus(void) { return m_nTimeBonus; };

	// タイムボーナスセット
	inline void SetTimeBonus(int bonus) { m_nTimeBonus = bonus; };

private:

	// 現在スコア
	int m_nCurrentScore;

	// ハイスコア
	int m_nHiScore;

	// タイムボーナス
	int m_nTimeBonus;
};