#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cResult.h													*/
/*  @brief		:	リザルトシーン												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/04/11													*/
/*																				*/
/*==============================================================================*/

#include "..\IBaseScene.h"

//================================================================================================
// リザルトシーン
class cResult : public IBaseScene
{
public:
	cResult(IBaseObject* parent);
	~cResult(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	// リザルトシーン状態
	enum class RESULT_STATE
	{
		START,
		PAPER,		// 紙出現
		SCORETEXT,	// スコア文字出現
		HISCORETEXT,// ハイスコア文字出現
		NEWRECORD,  // ハイスコア更新
		WAIT,
	};

	// 状態別処理
	// 開始時
	void Start(void);
	// 紙出現
	void Paper(void);
	// スコア文字出現
	void ScoreText(void);
	// ハイスコア文字出現
	void HiScoreText(void);
	// ハイスコア更新
	void NewRecord(void);
	// 入力待ち状態
	void Wait(void);


	// リザルトシーン状態
	RESULT_STATE m_eResultState;

	// ハイスコア
	int			 m_nHiScore;

	// 定数
	static const float		PAPER_START_POSX;
	static const float		PAPER_START_POSY;
};
//================================================================================================