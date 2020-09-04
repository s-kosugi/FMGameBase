/*==============================================================================*/
/*																				*/
/*	@file title	:	cBossLaserBullet.cpp										*/
/*  @brief		:	�{�X���[�U�[�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/24													*/
/*																				*/
/*==============================================================================*/

#include "cBossLaserBullet.h"
#include "..\..\..\..\cGame.h"
#include "..\..\..\..\Utility\utility.h"
#include "..\..\Effect\cEffectManager.h"
#include "..\..\Effect\cEffectObject.h"
#include "..\cBulletManager.h"

//==========================================================================================
// �萔
//==========================================================================================
const float cBossLaserBullet::HIT_RANGE = 60.0f;	// �����蔻��
const int	cBossLaserBullet::DEFAULT_ATK = 400;	// �W���U����
const int	cBossLaserBullet::PRIORITY = 300;		// �\���D��
const short cBossLaserBullet::DEFAULT_LIFETIME = 200; // �W����������

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cBossLaserBullet::cBossLaserBullet(IBaseObject * parent)
	: cBulletBase(parent, "BossLaserBullet", "data\\graphic\\Bullet_01.png"),
	m_nLifeCounter(DEFAULT_LIFETIME)
{
}

cBossLaserBullet::cBossLaserBullet(IBaseObject * parent, const std::string & name, const std::string & filename)
	: cBulletBase(parent, "BossLaserBullet", filename),
	m_nLifeCounter(DEFAULT_LIFETIME)
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cBossLaserBullet::~cBossLaserBullet(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cBossLaserBullet::Initialize(void)
{
	cGame game = cGame::GetInstance();

	m_fHitRange = HIT_RANGE;

	m_nHp = 0;
	m_nAtk = DEFAULT_ATK;

	// �{�X���[�U�[�̓G�t�F�N�g�Ƃ��ĕ`�悷�邽�߃X�v���C�g�͕\�����Ȃ�
	m_bVisible = false;

	SetPriority(PRIORITY);

	cBulletBase::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cBossLaserBullet::Update(void)
{
	// ���������e�͏������ɓ����蔻����c��
	m_eState = STATE_NORMAL;

	// �G���A�A�E�g��������e������
	//AreaOutAllProc();

	m_nLifeCounter--;

	if (m_nLifeCounter <= 0)
	{
		DeleteObject();
	}

	cBulletBase::Update();
}
//==========================================================================================
// �j��
//==========================================================================================
IBaseObject* cBossLaserBullet::Finalize(void)
{
	cBulletBase::Finalize();

	return this;
}

//==========================================================================================
// ���ˊp�x�̃Z�b�g
// angle : �x���@�̊p�x,0�x���^��
//==========================================================================================
void cBossLaserBullet::SetShootAngle(float angle)
{
	angle += 90.0f;
	//m_vPosUp.x = m_fSpeed * cos(DEG_TO_RAD(angle));
	//m_vPosUp.y = m_fSpeed * sin(DEG_TO_RAD(angle));
}
//==========================================================================================
// ���[�U�[�z�u�̊J�n
// vAngle : ���[�U�[�̐i�s����
//==========================================================================================
void cBossLaserBullet::StartConfig(float fAngle)
{
	cEffectObject* ef = cEffectManager::GetInstance().Create(EFFECT_BOSSLASER, m_vPos);
	ef->SetAngle({ 0.0f,0.0f,DEG_TO_RAD(fAngle) });

	cVector2 pos = m_vPos;
	fAngle += 90.0f;
	while (1)
	{
		pos.x += HIT_RANGE * cos(DEG_TO_RAD(fAngle));
		pos.y += HIT_RANGE * sin(DEG_TO_RAD(fAngle));


		// �����蔻�肪��ʔ͈͓��Ȃ烌�[�U�[����葱����
		if (pos.x + HIT_RANGE / 2 > cGame::GetInstance().GetPlayArea().left &&
			pos.y + HIT_RANGE / 2 > cGame::GetInstance().GetPlayArea().top &&
			pos.x - HIT_RANGE / 2 < cGame::GetInstance().GetPlayArea().right &&
			pos.y - HIT_RANGE / 2 < cGame::GetInstance().GetPlayArea().bottom)
		{
			cBulletManager::GetInstance().Create(BT_BOSS_LASER, pos, HIT_ENEMY, 0.0f, m_nColor, this->m_sFileName);
		} else
		{
			break;
		}
	}
}