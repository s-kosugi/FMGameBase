/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmYellowCore.cpp											*/
/*  @brief		:	�C�G���[�R�A�̓G�N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/26													*/
/*																				*/
/*==============================================================================*/

#include "cEnmYellowCore.h"
#include "..\..\..\..\cGame.h"
#include "..\..\Bullet\cBulletManager.h"
#include "..\..\Bullet\SnipeBullet\cSnipeBullet.h"
#include "..\..\Effect\cEffectManager.h"
#include "..\..\..\..\Utility\utility.h"

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cEnmYellowCore::cEnmYellowCore(IBaseObject * parent)
	: cEnemyBase(parent, "EnmYellowCore", "data\\graphic\\enemy_03.png"),
	m_nBulletTimer ( 0 ),
	m_nLifeTimer( 0 )
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cEnmYellowCore::~cEnmYellowCore(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cEnmYellowCore::Initialize(void)
{
	cGame game = cGame::GetInstance();

	m_eHitCate = HIT_ENEMY;
	m_fHitRange = HIT_RANGE;
	m_nHp = DEF_HP;
	m_nAtk = DEF_ATK;
	m_nScore = DEF_SCORE;


	SetPriority(PRIORITY);
	m_vPosUp.y = MOVE_SPEED_Y;
	m_nLifeTimer = 0;

	cEnemyBase::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cEnmYellowCore::Update(void)
{

	m_fAngle += ROTATE_SPEED;

	m_vPosUp.x = sin(DEG_TO_RAD(m_nLifeTimer)) * MOVE_SPEED_X;


	m_nBulletTimer++;
	if (m_nBulletTimer >= SHOOT_INTERVAL)
	{
		cSnipeBullet* bt =  (cSnipeBullet*)cBulletManager::GetInstance().Create(BT_SNIPE_BULLET,m_vPos,HIT_ENEMY,BULLET_SPEED);
		cSpriteObject* obj = (cSpriteObject*)GetParent()->FindSibling("Player");

		// �^�[�Q�b�g���W�̐ݒ�
		if( obj != nullptr ) bt->CalcTargetVector(obj->GetPos());

		bt->SetDrawColor(BULLET_COLOR);

		m_nBulletTimer = 0;
	}

	m_nLifeTimer+=MOVESPEED_ADDTIME;

	// �������ɃG���A�A�E�g������G������
	AreaOutBottomProc();

	cEnemyBase::Update();
}

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject* cEnmYellowCore::Finalize(void)
{
	cEnemyBase::Finalize();

	return this;
}