/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmBlueCore.cpp											*/
/*  @brief		:	�u���[�R�A�̓G�N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/21													*/
/*																				*/
/*==============================================================================*/

#include "cEnmBlueCore.h"
#include "..\..\..\..\cGame.h"
#include "..\..\Bullet\cBulletManager.h"
#include "..\..\Bullet\AngleBullet\cAngleBullet.h"
#include "..\..\Effect\cEffectManager.h"

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cEnmBlueCore::cEnmBlueCore(IBaseObject * parent)
	: cEnemyBase(parent, "EnmBlueCore", "data\\graphic\\enemy_02.png"),
	m_nBulletTimer(0)
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cEnmBlueCore::~cEnmBlueCore(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cEnmBlueCore::Initialize(void)
{
	cGame game = cGame::GetInstance();

	m_eHitCate = HIT_ENEMY;
	m_fHitRange = HIT_RANGE;
	m_nHp = DEF_HP;
	m_nAtk = DEF_ATK;
	m_nScore = DEF_SCORE;


	SetPriority(PRIORITY);

	cEnemyBase::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cEnmBlueCore::Update(void)
{
	m_fAngle += ROTATE_SPEED;
	m_vPos.y += MOVE_SPEED;

	m_nBulletTimer++;
	if (m_nBulletTimer >= SHOOT_INTERVAL)
	{
		// �z�[�~���O�e����
		cAngleBullet* bul = (cAngleBullet*)cBulletManager::GetInstance().Create(BT_ANGLE,m_vPos,HIT_ENEMY,BULLET_SPEED,BULLET_COLOR);
		bul->SetShootAngle(m_fAngle);
		m_nBulletTimer = 0;
	}

	// �������ɃG���A�A�E�g������G������
	AreaOutBottomProc();

	cEnemyBase::Update();
}

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject* cEnmBlueCore::Finalize(void)
{
	cEnemyBase::Finalize();

	return this;
}