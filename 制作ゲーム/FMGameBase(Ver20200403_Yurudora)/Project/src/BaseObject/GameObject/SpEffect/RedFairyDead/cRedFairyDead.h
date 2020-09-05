#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cRedFairyDead.h												*/
/*  @brief		:	�ԗd�����S�G�t�F�N�g										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/04/05													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\cSpriteObject.h"

//================================================================================================
// �ԗd�����S�G�t�F�N�g�N���X
class cRedFairyDead : public cSpriteObject
{
public:
	cRedFairyDead( IBaseObject* parent );
	~cRedFairyDead( void );

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