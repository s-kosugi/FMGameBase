/*==============================================================================*/
/*																				*/
/*	@file title	:	cSpEffectManager.cpp										*/
/*  @brief		:	�X�v���C�g�G�t�F�N�g�Ǘ��N���X								*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/04/05													*/
/*																				*/
/*==============================================================================*/

#include "cSpEffectManager.h"
#include "RedFairyDead/cRedFairyDead.h"
#include "BlueFairyDead/cBlueFairyDead.h"

//==========================================================================================
// �萔
//==========================================================================================

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cSpEffectManager::cSpEffectManager( IBaseObject* pObj )
	:IBaseObject( pObj, "SpEffectManager" )
{
}
//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cSpEffectManager::~cSpEffectManager( void )
{
}

//==========================================================================================
// ������
//==========================================================================================
void cSpEffectManager::Initialize( void )
{
}

//==========================================================================================
// UI����
// return : ��������UI�̃|�C���^ ��������Ȃ������ꍇ��nullptr
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
