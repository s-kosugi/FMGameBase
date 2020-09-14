#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSpEffectManager.h											*/
/*  @brief		:	スプライトエフェクト管理クラス								*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/04/05													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseObject.h"
#include "SpEffectID.h"
#include "Utility/Vector/cVector2.h"

// 前方宣言
class cSpriteObject;

// スプライトエフェクト管理クラス
class cSpEffectManager : public IBaseObject
{
public:
	// コンストラクタ
	cSpEffectManager( IBaseObject* pObj );
	~cSpEffectManager( void );

	// 初期化
	void Initialize( void );

	// UI生成
	cSpriteObject* Create( SpEffectID id, const cVector2& pos );

private:


};