#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cUIManager.h												*/
/*  @brief		:	UI�Ǘ��N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2020/04/03													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseObject.h"
#include "UIID.h"
#include "Utility/Vector/cVector2.h"

// �O���錾
class cSpriteObject;

// UI�Ǘ��N���X
class cUIManager : public IBaseObject
{
public:
	// �R���X�g���N�^
	cUIManager( IBaseObject* pObj );
	~cUIManager( void );

	// ������
	void Initialize( void );

	// UI����
	cSpriteObject* Create( UIID id ,const cVector2& pos);

private:


};