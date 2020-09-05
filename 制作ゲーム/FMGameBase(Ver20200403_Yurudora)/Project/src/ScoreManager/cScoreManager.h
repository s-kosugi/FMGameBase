#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cScoreManager.h												*/
/*  @brief		:	スコア管理クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/04/03													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseObject.h"

// スコア管理クラス
class cScoreManager : public IBaseObject
{
public:
	// コンストラクタ
	cScoreManager(IBaseObject* pObj);

	// デストラクタ
	~cScoreManager( void );

	// 初期化
	void Initialize( void );

	// 破棄
	IBaseObject* Finalize( void );

	// スコアリセット
	inline void ResetScore( void ) { m_nCurrentScore = 0; };

	// スコア加算
	inline void AddScore( int score ) { m_nCurrentScore += score; };

	// スコア取得
	inline int GetScore( void ) { return m_nCurrentScore; };


private:

	// 現在スコア
	int m_nCurrentScore;

};