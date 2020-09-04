/*==============================================================================*/
/*																				*/
/*	@file title	:	cPlayer.cpp													*/
/*  @brief		:	�v���C���[�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "cPlayer.h"
#include "..\..\..\Input\cControllerManager.h"
#include "..\..\..\cGame.h"
#include "..\Effect\cEffectManager.h"
#include "..\Enemy\cEnemyManager.h"
#include "..\..\..\SceneManager\cSceneManager.h"
#include "..\..\..\SceneManager\Scene\GameMain\cGameMain.h"
#include "..\..\..\SoundCtrl\cSoundCtrl.h"

//==========================================================================================
// �萔
//==========================================================================================
const float cPlayer::GRAVITY = 0.98f;
const float cPlayer::START_POS_X = 300.0f;
const float cPlayer::START_POS_Y = 350.0f;
const float cPlayer::JUMP_POWER = 8.0f;

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cPlayer::cPlayer( IBaseObject* parent )
	: cSpriteObject( parent, "Player", "data\\graphic\\player_01.png" ),
	m_vPosUp( 0.0f, 0.0f ),
	m_vAccele( 0.0f, 0.0f ),
	m_bLand( false ),
	m_nFailedTimer( 0 )
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cPlayer::~cPlayer( void )
{
}

//==========================================================================================
// ������
//==========================================================================================
void cPlayer::Initialize( void )
{
	m_vPos = { START_POS_X,START_POS_Y };
	SetPriority( PRIORITY );
	cSpriteObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cPlayer::Update( void )
{
	cGameMain* gm = (cGameMain*)GetParent();

	// �Q�[���v���C���ɂ̂݃v���C���[�̍X�V
	if( gm->GetGameState() == cGameMain::GAME_STATE::PLAY )
	{
		// �U���s�\�^�C�}�[���J�E���g����
		if( --m_nFailedTimer <= 0 ) m_nFailedTimer = 0;

		// �U��
		Attack();

		// �W�����v����
		JumpWalk();

		// �d�͗�������
		if( !m_bLand ) m_vAccele.y = GRAVITY;

		// �ړ�����
		m_vPosUp += m_vAccele;
		m_vPos += m_vPosUp;

		// �n�ʂɂ߂荞�񂾂�n��ɖ߂�
		if( m_vPos.y + GetGraphichSize().y / 2 > cGame::GetInstance().GetWindowHeight() - LANDING_LINE )
		{
			m_vPos.y = (float)( cGame::GetInstance().GetWindowHeight() - LANDING_LINE - GetGraphichSize().y / 2 );
			m_bLand = true;
			m_vPosUp.y = 0.0f;
			m_vAccele.y = 0.0f;
		}

		// �v���C���[�ƓG�Ƃ̓����蔻�菈��
		cEnemyManager* enm = (cEnemyManager*)FindSibling( "EnemyManager" );
		if( enm )
		{
			if( enm->JudgePlayer( m_vPos, PLAYER_DIST ) )
			{
				// �v���C���[�ƓG���ڐG������Q�[���I�[�o�[
				cGameMain* gm = (cGameMain*)GetParent();
				gm->SetGameState( cGameMain::GAME_STATE::OVER );
			}
		}
	}

	cSpriteObject::Update();
}
//==========================================================================================
// �j��
//==========================================================================================
IBaseObject* cPlayer::Finalize( void )
{
	cSpriteObject::Finalize();

	return this;
}

//==========================================================================================
// �W�����v�ړ�
//==========================================================================================
void cPlayer::JumpWalk( void )
{
	// �L�����N�^�[���n�ʂɂ�����W�����v��������
	if( m_bLand )
	{
		m_vPosUp.y = -JUMP_POWER;
		m_bLand = false;
	}
}

//==========================================================================================
// �U��
//==========================================================================================
void cPlayer::Attack( void )
{
	cControllerManager* cm = (cControllerManager*)GetRoot()->FindChild( "ControllerManager" );
	if( cm )
	{
		// �U���R�}���h���s(�U�����s�^�C�}�[��1�ȏ�̏ꍇ�͍U�����ł��Ȃ�)
		if( ( cm->CheckTrigger( cControllerManager::KEY_DEFINE::KEY_1 ) ) &&
			m_nFailedTimer <= 0 )
		{
			cVector2 vec = m_vPos;
			vec.x += ATTACK_POS;

			// �G�t�F�N�g�Đ�
			cEffectManager* efm = (cEffectManager*)GetRoot()->FindChild("EffectManager");
			if( efm ) efm->Create( EFFECT_ID::SLASH, vec );

			// �T�E���h�Đ�
			cSoundCtrl* sc = (cSoundCtrl*)GetRoot()->FindChild( "SoundCtrl" );
			if( sc ) sc->Play( SOUND_ID::SLASH );

			// �U������
			cEnemyManager* enm = (cEnemyManager*)FindSibling( "EnemyManager" );
			if( enm )
			{
				if( !enm->JudgeHit( vec, (float)ATTACK_RANGE ) )
				{
					// �U�����s���ɂ͍U���s�\�^�C�}�[���Z�b�g����
					m_nFailedTimer = FAILED_TIME;
				}
			}
		}
	}
}
