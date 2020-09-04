#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cTitleTile.h												*/
/*  @brief		:	タイトルタイルオブジェクト									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/26													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\cSpriteObject.h"

//================================================================================================
// タイトルタイルオブジェクト
class cTitleTile : public cSpriteObject
{
public:
	cTitleTile(IBaseObject* parent, const std::string& objectname, const std::string& filename);
	~cTitleTile(void);


	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	inline bool isPop(void) { return m_bPop; };
	inline bool isCrumble(void) { return m_bCrumble; };
	inline void StartPop(void) { m_bPop = true; };
	void StartCrumble(void);

private:
	static const int PRIORITY = 100;
	static const float TILE_SCALEUP;
	static const float CRUMBLE_MOVE_X;
	static const float CRUMBLE_START_Y;
	static const float CRUMBLE_GRAVITY;

	
	cVector2			m_vPosUp;	// 移動力

	bool				m_bPop;		// タイルが出現中かどうか
	bool				m_bCrumble; // タイルが崩壊中かどうか
};
//================================================================================================