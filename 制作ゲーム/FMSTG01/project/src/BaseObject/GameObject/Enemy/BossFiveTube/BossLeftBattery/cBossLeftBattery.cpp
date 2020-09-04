/*==============================================================================*/
/*																				*/
/*	@file title	:	cBossLeftBattery.cpp										*/
/*  @brief		:	�{�X��͂̍��C��N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/22													*/
/*																				*/
/*==============================================================================*/

#include "cBossLeftBattery.h"
#include "..\..\..\Bullet\cBulletManager.h"
#include "..\..\..\Bullet\SnipeBullet\cSnipeBullet.h"
#include "..\..\..\Player\cPlayer.h"
#include "..\..\..\Effect\cEffectManager.h"
#include "..\..\cEnemyManager.h"

#include "..\..\..\..\..\Utility\utility.h"

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cBossLeftBattery::cBossLeftBattery(IBaseObject * parent)
	: cEnemyBase(parent, "BossFiveTube", "data\\graphic\\boss_01_leftBattery.png"),
	m_eActionState(STATE_WAIT),
	m_nActionTimer(0),
	m_nBulletTimer(0),
	m_pFollowObject(nullptr),
	m_nCrazyTimer(0)
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cBossLeftBattery::~cBossLeftBattery(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cBossLeftBattery::Initialize(void)
{
	m_eHitCate = HIT_ENEMY;
	m_fHitRange = HIT_RANGE;
	m_nHp = DEF_HP;
	m_nAtk = DEF_ATK;
	m_nScore = DEF_SCORE;

	// �Ǐ]�I�u�W�F�N�g�����肷��܂ł͉�ʊO�ɒu��
	m_vPos = cVector2 (-200.0f,-200.0f );

	SetPriority(PRIORITY);

	cEnemyBase::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cBossLeftBattery::Update(void)
{

	// ��ԕʍs��
	switch (m_eActionState)
	{

	case STATE_WAIT:
		Wait();
		break;

	case STATE_ATTACK:
		Attack();
		break;

	case STATE_CRAZYWAIT:
		CrazyWait();
		break;

	case STATE_CRAZYATTACK:
		CrazyAttack();
		break;
	}

	// ������Ԃւ̈ڍs�`�F�b�N
	CheckCrazy();

	// �Ǐ]����
	MoveFollow();

	cEnemyBase::Update();
}

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject* cBossLeftBattery::Finalize(void)
{
	cEnemyBase::Finalize();

	return this;
}

//==========================================================================================
// �ҋ@
//==========================================================================================
void cBossLeftBattery::Wait(void)
{
	m_nActionTimer++;
	if (m_nActionTimer >= WAIT_NEXTACT_TIME)
	{
		m_eActionState = STATE_ATTACK;
		m_nActionTimer = 0;
	}
}
//==========================================================================================
// �U��
//==========================================================================================
void cBossLeftBattery::Attack(void)
{
	m_nBulletTimer++;
	if (m_nBulletTimer >= SHOOT_INTERVAL)
	{
		cVector2 shotPos = m_vPos;
		shotPos.x += SHOT_POSX;
		shotPos.y += SHOT_POSY;
		cBulletManager::GetInstance().Create(BT_SNIPE_BULLET, shotPos, HIT_ENEMY, BULLET_SPEED, BULLET_COLOR, "data\\graphic\\Bullet_02.png");
		m_nBulletTimer = 0;
	}

	m_nActionTimer++;
	if (m_nActionTimer >= ATTACK_NEXTACT_TIME)
	{
		m_eActionState = STATE_WAIT;
		m_nActionTimer = 0;
	}
}
//==========================================================================================
// ������ԑҋ@
//==========================================================================================
void cBossLeftBattery::CrazyWait(void)
{
	m_nActionTimer++;
	if (m_nActionTimer >= CRZWAIT_NEXTACT_TIME)
	{
		m_eActionState = STATE_CRAZYATTACK;
		m_nActionTimer = 0;
	}
}
//==========================================================================================
// ������ԑҋ@
//==========================================================================================
void cBossLeftBattery::CrazyAttack(void)
{
	m_nBulletTimer++;
	if (m_nBulletTimer >= SHOOT_INTERVAL)
	{
		cVector2 shotPos = m_vPos;
		shotPos.x += SHOT_POSX;
		shotPos.y += SHOT_POSY;
		cBulletManager::GetInstance().Create(BT_SNIPE_BULLET, shotPos, HIT_ENEMY, BULLET_SPEED, BULLET_COLOR, "data\\graphic\\Bullet_02.png");
		// nWay�e����
		cBulletManager::GetInstance().CreateNWayBullet(m_vPos, HIT_ENEMY, BULLET_SPEED, BULLET_NUM, BULLET_ANGLE_INTERVAL, 0, CRZ_BULLLET_COLOR);
		m_nBulletTimer = 0;
	}

	m_nActionTimer++;
	if (m_nActionTimer >= CRZATTACK_NEXTACT_TIME)
	{
		m_eActionState = STATE_CRAZYWAIT;
		m_nActionTimer = 0;
	}
}

//==========================================================================================
// �Ǐ]����
//==========================================================================================
void cBossLeftBattery::MoveFollow(void)
{
	if (nullptr != m_pFollowObject)
	{
		bool find = false;
		for (auto it = cEnemyManager::GetInstance().GetChildList()->begin(); it != cEnemyManager::GetInstance().GetChildList()->end(); it++)
		{
			if ((*it) == m_pFollowObject)
			{
				find = true;
				break;
			}
		}
		// �Ǐ]�I�u�W�F�N�g�����������ꍇ
		if (find)
		{
			m_vPos.x = m_pFollowObject->GetPos().x + DEF_POSX;
			m_vPos.y = m_pFollowObject->GetPos().y + DEF_POSY;

			// �e������ł�����e�������Ȃ�
			if(STATE_DEAD == m_pFollowObject->GetState())
			{
				m_eState = STATE_FLASH;
				m_eActionState = STATE_WAIT;
				m_nActionTimer = 0;

			}
		}
		else
		{
			// �Ǐ]�I�u�W�F�N�g��������Ȃ������׍폜����
			m_eObjectState = OBJECT_STATE_DEAD;
		}
	}
	else
	{
		// �Ǐ]�I�u�W�F�N�g��������Ȃ������׍폜����
		m_eObjectState = OBJECT_STATE_DEAD;
	}
}

//==========================================================================================
// ������Ԃւ̈ڍs�`�F�b�N
//==========================================================================================
void cBossLeftBattery::CheckCrazy(void)
{
	m_nCrazyTimer++;
	// �����`�F�b�N
	if (m_nCrazyTimer >= CRAZY_TIME && m_eActionState < STATE_CRAZYWAIT)
	{
		m_eActionState = STATE_CRAZYWAIT;
	}
}
