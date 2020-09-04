#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBlueFairyDead.h											*/
/*  @brief		:	�d�����S�G�t�F�N�g										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/04/05													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\cSpriteObject.h"

//================================================================================================
// �d�����S�G�t�F�N�g�N���X
class cBlueFairyDead : public cSpriteObject
{
public:
	cBlueFairyDead( IBaseObject* parent );
	~cBlueFairyDead( void );

	void Initialize( const cVector2& pos );
	void Update( void );

private:

	// �ړ���
	cVector2		m_vPosUp;


	//--------------------------------------------------------------------------------------------
	// �萔

	// �\���D��x
	static const int	PRIORITY;

	// �\������
	static const float	LIFE_TIME;

	// �ő�ړ����x
	static const float  MAX_SPEED;
	// �ŏ��ړ����x
	static const float  MIN_SPEED;

	// �_�ŊԊu
	static const float  FLASH_INTERVAL;

	//--------------------------------------------------------------------------------------------

};
//================================================================================================