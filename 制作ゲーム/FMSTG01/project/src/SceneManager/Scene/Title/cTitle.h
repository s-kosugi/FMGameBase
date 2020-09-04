#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cTitle.h													*/
/*  @brief		:	タイトルシーン												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\BaseObject\IBaseObject.h"
#include <vector>

class cSpriteObject;

//================================================================================================
// タイトルシーン
class cTitle : public IBaseObject
{
public:
	cTitle(IBaseObject* parent);
	~cTitle(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:

	enum TITLE_STATE
	{
		STATE_TILE_POP = 0,
		STATE_APPEAR_TITLE,
		STATE_PUSHKEY,
		STATE_CRUMBLE,
	};


	void TilePop( void );
	void AppearTitle( void );
	void PushKey( void );
	void Crumble( void );


	static const int PUSHKEY_INTERVAL = 60;


	int					m_nCounter;			// タイトル用カウンター

	TITLE_STATE			m_eTitleState;

};
//================================================================================================