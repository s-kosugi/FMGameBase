/*==============================================================================*/
/*																				*/
/*	@file title	:	cScoreBoard.cpp												*/
/*  @brief		:	�X�R�A�{�[�h�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/04/03													*/
/*																				*/
/*==============================================================================*/

#include "cScoreBoard.h"
#include "Utility/Number/cNumber.h"
#include "ScoreManager/cScoreManager.h"

//==========================================================================================
// �萔
//==========================================================================================
const int	cScoreBoard::PRIORITY = 200;

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cScoreBoard::cScoreBoard( IBaseObject* parent )
	: cSpriteObject( parent, "ScoreBoard", "data\\graphic\\ScoreBoard.png" )
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cScoreBoard::~cScoreBoard( void )
{
}

//==========================================================================================
// ������
//==========================================================================================
void cScoreBoard::Initialize( void )
{
	SetPriority( PRIORITY );

	cNumber* num = CreateDrawObject<cNumber>( this, "ScoreNumber", "data\\graphic\\Number.png" );
	num->CreateNumber( 5, 0 );
	num->SetPriority( PRIORITY + 10 );

	cSpriteObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cScoreBoard::Update( void )
{
	cNumber* num = (cNumber*)FindChild("ScoreNumber");
	cScoreManager* sm = (cScoreManager*)GetRoot()->FindChild("ScoreManager");
	if( num && sm )
	{
		num->SetValue(sm->GetScore());
		cVector2 vec = m_vPos;
		vec.x += 100.0f;
		vec.y += 15.0f;
		num->SetPos( vec );
	}

	cSpriteObject::Update();
}