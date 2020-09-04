/*==============================================================================*/
/*																				*/
/*	@file title	:	cSpEffectManager.cpp										*/
/*  @brief		:	スプライトエフェクト管理クラス								*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/04/05													*/
/*																				*/
/*==============================================================================*/

#include "cSpEffectManager.h"
#include "RedFairyDead/cRedFairyDead.h"
#include "BlueFairyDead/cBlueFairyDead.h"

//==========================================================================================
// 定数
//==========================================================================================

//==========================================================================================
// コンストラクタ
//==========================================================================================
cSpEffectManager::cSpEffectManager( IBaseObject* pObj )
	:IBaseObject( pObj, "SpEffectManager" )
{
}
//==========================================================================================
// デストラクタ
//==========================================================================================
cSpEffectManager::~cSpEffectManager( void )
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cSpEffectManager::Initialize( void )
{
}

//==========================================================================================
// UI生成
// return : 生成したUIのポインタ 生成されなかった場合はnullptr
//==========================================================================================
cSpriteObject* cSpEffectManager::Create( SpEffectID id, const cVector2& pos )
{
	cSpriteObject* pObj = nullptr;
	switch( id )
	{
	case SpEffectID::REDFAIRY_DEAD:		pObj = CreateObject<cRedFairyDead>( this ); break;
	case SpEffectID::BLUEFAIRY_DEAD:	pObj = CreateObject<cBlueFairyDead>( this ); break;
	}
	if( pObj )
	{
		pObj->Initialize( pos );
	}

	return pObj;
}
