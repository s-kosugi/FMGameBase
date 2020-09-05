/*==============================================================================*/
/*																				*/
/*	@file title	:	cBlueFairy.cpp												*/
/*  @brief		:	�d���N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/04/23													*/
/*																				*/
/*==============================================================================*/

#include "cBlueFairy.h"
#include "cGame.h"
#include "SceneManager/Scene/GameMain/cGameMain.h"
#include "..\..\SpEffect\cSpEffectManager.h"
#include "..\..\Effect\cEffectManager.h"
#include "SoundCtrl/cSoundCtrl.h"
#include "Utility/Timer/cTimer.h"
#include "Utility/Easing/Easing.h"

//==========================================================================================
// �萔
//==========================================================================================
const int	cBlueFairy::PRIORITY = 200;
const float cBlueFairy::MOVE_SPEED = 8.0f;
const float cBlueFairy::ATTACK_POSY = 250.0f;

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cBlueFairy::cBlueFairy(IBaseObject * parent)
	: IEnemyBase(parent, "BlueFairy", "data\\graphic\\enemy_02.png")
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cBlueFairy::~cBlueFairy(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cBlueFairy::Initialize(void)
{
	cGame* game = (cGame*)GetRoot();
	cGameMain* gm = (cGameMain*)GetParent()->GetParent();

	if( gm )
	{
		m_vPos = { (float)game->GetWindowWidth() + GetGraphichSize().x / 2,
			(float)game->GetWindowHeight() - GetGraphichSize().y / 2 - gm->GetLandingLine() };
	}

	SetPriority(PRIORITY);
	IEnemyBase::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cBlueFairy::Update(void)
{
	m_vPosUp.x = -MOVE_SPEED;

	// �G������炳���铮��
	cTimer* timer = (cTimer*)FindChild( "SwingTimer" );
	if( !timer ){
		timer = CreateObject<cTimer>( this, "SwingTimer" );
		timer->Setup( 1.0f );
	}
	if( timer->Finished() ) timer->Reset();
	if( timer->GetLimit() / 2.0f < timer->GetTime() )
		m_vPosUp.y = Easing::InCubic( timer->GetTime(), timer->GetLimit(), 3.0f, -3.0f );
	else
		m_vPosUp.y = Easing::OutCubic( timer->GetTime(), timer->GetLimit(), -3.0f, 3.0f );

	IEnemyBase::Update();
}
//==========================================================================================
// �j��
//==========================================================================================
IBaseObject* cBlueFairy::Finalize(void)
{
	IEnemyBase::Finalize();

	return this;
}
//==========================================================================================
// ���S����
//==========================================================================================
void cBlueFairy::Dead( void )
{
	// ���S�G�t�F�N�g�𐶐�
	cSpEffectManager* se = (cSpEffectManager*)GetParent()->FindSibling( "SpEffectManager" );
	if( se ) se->Create( SpEffectID::BLUEFAIRY_DEAD, m_vPos );

	DeleteObject();
}

//==========================================================================================
// �U���J�n����
//==========================================================================================
void cBlueFairy::StartAttack(void)
{
	// �G�t�F�N�g�����ʒu�Z�o
	cVector2 vec = m_vPos;
	vec.x -= ATTACK_POS;
	vec.y += ATTACK_POSY;

	// �U���G�t�F�N�g����
	cEffectManager* em = (cEffectManager*)GetRoot()->FindChild("EffectManager");
	if (em) em->Create(EFFECT_ID::ICEATTACK, vec);

	cSoundCtrl::GetInstance().Play(SOUND_ID::ICE);
	cSoundCtrl::GetInstance().Play(SOUND_ID::WIND);
}
