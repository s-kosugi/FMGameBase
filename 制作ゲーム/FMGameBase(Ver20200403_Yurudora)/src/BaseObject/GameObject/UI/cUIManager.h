#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cUIManager.h												*/
/*  @brief		:	UI管理クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/04/03													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseObject.h"
#include "UIID.h"
#include "Utility/Vector/cVector2.h"

// 前方宣言
class cSpriteObject;

// UI管理クラス
class cUIManager : public IBaseObject
{
public:
	// コンストラクタ
	cUIManager( IBaseObject* pObj );
	~cUIManager( void );

	// 初期化
	void Initialize( void );

	// UI生成
	cSpriteObject* Create( UIID id ,const cVector2& pos);

private:


};