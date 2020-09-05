#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSpEffectManager.h											*/
/*  @brief		:	�X�v���C�g�G�t�F�N�g�Ǘ��N���X								*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/04/05													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseObject.h"
#include "SpEffectID.h"
#include "Utility/Vector/cVector2.h"

// �O���錾
class cSpriteObject;

// �X�v���C�g�G�t�F�N�g�Ǘ��N���X
class cSpEffectManager : public IBaseObject
{
public:
	// �R���X�g���N�^
	cSpEffectManager( IBaseObject* pObj );
	~cSpEffectManager( void );

	// ������
	void Initialize( void );

	// UI����
	cSpriteObject* Create( SpEffectID id, const cVector2& pos );

private:


};