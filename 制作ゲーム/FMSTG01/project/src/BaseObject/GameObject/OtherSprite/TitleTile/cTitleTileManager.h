#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cTitleTileManager.h											*/
/*  @brief		:	タイトルタイル管理											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/28													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\IBaseObject.h"

//================================================================================================
// タイトルタイル管理クラス
class cTitleTileManager : public IBaseObject
{
public:
	cTitleTileManager(IBaseObject* parent);
	~cTitleTileManager(void);


	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// タイル出現開始
	inline void StartPop(void) { m_eState = STATE_TILE_POP; };

	// タイル崩壊開始
	inline void StartCrumble(void) { m_eState = STATE_CRUMBLE; };

	// タイルの出現完了を取得
	inline bool IsPopComp(void) { return m_bPopComp; };
private:

	enum TILE_STATE
	{
		STATE_WAIT = -1,
		STATE_TILE_POP = 0,
		STATE_CRUMBLE,
	};

	static const int TILE_SIZE = 64;
	static const int TILE_ADJUST = 32;		// ２列目以降のタイル補正値
	static const int TILE_HEIGHT = 48;

	static const int TILE_POP_INTERVAL = 1;
	static const short TILE_SAME_POP = 2;
	static const int TILE_CRUMBLE_INTERVAL = 1;
	static const short TILE_SAME_CRUMBLE = 2;

	void Pop( void );
	void Crumble( void );

	
	int						m_nCounter;
	TILE_STATE				m_eState;
	bool					m_bPopComp;		// タイル出現完了フラグ
};
//================================================================================================