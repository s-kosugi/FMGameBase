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
#include "..\..\..\SoundCtrl\cSoundCtrl.h"
#include "..\..\..\DebugFunc\cDebugFunc.h"

//==========================================================================================
// �萔
//==========================================================================================
const float cPlayer::MOVE_SPEED = 3.0f;		// �v���C���[�̈ړ����x
const float cPlayer::START_POS_X = 300.0f;	// �Q�[���J�n�ʒu
const float cPlayer::START_POS_Y = 300.0f;	// �Q�[���J�n�ʒu
const int   cPlayer::PRIORITY = 300;	// �\���D��x

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cPlayer::cPlayer(IBaseObject* parent)
	: cAnimSpObject(parent, "Player", "data\\graphic\\player_01.ass")
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cPlayer::~cPlayer(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cPlayer::Initialize(void)
{
	m_vPos = { START_POS_X,START_POS_Y };
	SetPriority(PRIORITY);
	//SetAnimation(0,0, SIZE_X, SIZE_Y, ANIM_NUM, ANIM_TIME);
	cAnimSpObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cPlayer::Update(void)
{
	// ���͊Ǘ��N���X���擾
	cControllerManager* cm = (cControllerManager*)GetRoot()->FindChild("ControllerManager");

	if (cm)
	{
		if (cm->CheckButton(cControllerManager::KEY_DEFINE::KEY_RIGHT))
		{
			m_vPos.x += MOVE_SPEED;
		}
		if (cm->CheckButton(cControllerManager::KEY_DEFINE::KEY_LEFT))
		{
			m_vPos.x -= MOVE_SPEED;
		}
		if (cm->CheckButton(cControllerManager::KEY_DEFINE::KEY_UP))
		{
			m_vPos.y -= MOVE_SPEED;
		}
		if (cm->CheckButton(cControllerManager::KEY_DEFINE::KEY_DOWN))
		{
			m_vPos.y += MOVE_SPEED;
		}
	}

	if ((cControllerManager::GetInstance().CheckTrigger(cControllerManager::KEY_DEFINE::KEY_1)))
		cEffectManager::GetInstance().Create(EFFECT_ID::HIT, m_vPos);

	// �͈͊O����
	ProcAreaOut();

	cAnimSpObject::Update();
}
//==========================================================================================
// �j��
//==========================================================================================
IBaseObject* cPlayer::Finalize(void)
{
	cAnimSpObject::Finalize();

	return this;
}

//==========================================================================================
// �͈͊O����
//==========================================================================================
void cPlayer::ProcAreaOut(void)
{
	// �Q�[���N���X�̃|�C���^���擾
	cGame* game = (cGame*)GetRoot();

	if (m_vPos.x - GetSpriteSize().x / 2.0f < 0.0f)
	{
		m_vPos.x = GetSpriteSize().x / 2.0f;
	}
	if (m_vPos.y - GetSpriteSize().y / 2.0f < 0.0f)
	{
		m_vPos.y = GetSpriteSize().y / 2.0f;
	}
	if (m_vPos.x + GetSpriteSize().x / 2.0f >= (float)game->GetWindowWidth())
	{
		m_vPos.x = (float)game->GetWindowWidth() - GetSpriteSize().x / 2.0f;
	}
	if (m_vPos.y + GetSpriteSize().y / 2.0f >= (float)game->GetWindowHeight())
	{
		m_vPos.y = (float)game->GetWindowHeight() - GetSpriteSize().y / 2.0f;
	}
}
