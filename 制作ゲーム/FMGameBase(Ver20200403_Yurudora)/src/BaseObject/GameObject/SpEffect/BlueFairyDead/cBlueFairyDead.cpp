/*==============================================================================*/
/*																				*/
/*	@file title	:	cBlueFairyDead.cpp											*/
/*  @brief		:	�d�����S�G�t�F�N�g�N���X									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/04/05													*/
/*																				*/
/*==============================================================================*/

#include "cBlueFairyDead.h"
#include "Utility/Easing/Easing.h"
#include "Utility/Timer/cTimer.h"

//==========================================================================================
// �萔
//==========================================================================================
const int	cBlueFairyDead::PRIORITY = 400;			// �\���D��x
const float cBlueFairyDead::LIFE_TIME = 1.0f;		// �\������
const float cBlueFairyDead::MAX_SPEED = 0.0f;		// �ő�ړ����x
const float cBlueFairyDead::MIN_SPEED = -5.0f;		// �ŏ��ړ����x
const float cBlueFairyDead::FLASH_INTERVAL = 0.08f;	// �_�ŊԊu

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cBlueFairyDead::cBlueFairyDead( IBaseObject* parent )
	: cSpriteObject( parent, "RedFairyDead1", "data\\graphic\\enemy_02_dead1.png" )
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cBlueFairyDead::~cBlueFairyDead( void )
{
}

//==========================================================================================
// ������
//==========================================================================================
void cBlueFairyDead::Initialize( const cVector2& pos )
{
	SetPriority( PRIORITY );

	// ���W��ݒ�
	m_vPos = pos;

	cTimer* timer = CreateObject<cTimer>( this, "VanishTimer" );
	timer->Setup( LIFE_TIME );

	// �����Е��̔��g��ʃX�v���C�g�ō쐬����
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>( this, "RedFairyDead2", "data\\graphic\\enemy_02_dead2.png" );
	obj->SetPos( pos );

	cSpriteObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cBlueFairyDead::Update( void )
{
	cTimer* timer = (cTimer*)FindChild( "VanishTimer" );
	if( timer )
	{
		cSpriteObject* child = (cSpriteObject*)FindChild( "RedFairyDead2" );

		m_vPosUp.x = m_vPosUp.y = Easing::OutQuad( timer->GetTime(), timer->GetLimit(), MAX_SPEED, MIN_SPEED );

		// �_�ŏ��� �^�C�}�[�𐮐����Ԃɒu�������Čv�Z
		SetVisible( int( timer->GetTime() * 100.0f ) % (int)( FLASH_INTERVAL * 100 ) <= FLASH_INTERVAL * 100 / 2.0f ? true : false );

		// �����Е��̔��g�͋t�����Ɉړ�������
		if( child )
		{
			child->SetPos( child->GetPos() - m_vPosUp );
			child->SetVisible( m_bVisible );
		}
		// ���Ԍo�߂�����I�u�W�F�N�g���폜����
		if( timer->Finished() )
		{
			DeleteObject();
		}
	}
	m_vPos += m_vPosUp;

	cSpriteObject::Update();
}