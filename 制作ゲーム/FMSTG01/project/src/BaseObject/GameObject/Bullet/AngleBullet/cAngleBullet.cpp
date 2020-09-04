/*==============================================================================*/
/*																				*/
/*	@file title	:	cAngleBullet.cpp											*/
/*  @brief		:	�p�x�w��e�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/07													*/
/*																				*/
/*==============================================================================*/

#include "cAngleBullet.h"
#include "..\..\..\..\cGame.h"
#include "..\..\..\..\Utility\utility.h"
#include "..\..\Effect\cEffectManager.h"
#include "..\..\Effect\cEffectObject.h"

//==========================================================================================
// �萔
//==========================================================================================
const float cAngleBullet::HIT_RANGE = 12.0f;	// �����蔻��
const int	cAngleBullet::DEFAULT_ATK = 50;		// �W���U����
const int	cAngleBullet::PRIORITY = 300;		// �\���D��

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cAngleBullet::cAngleBullet(IBaseObject * parent)
	: cBulletBase(parent, "AngleBullet", "data\\graphic\\Bullet_01.png")
{
}

cAngleBullet::cAngleBullet(IBaseObject * parent, const std::string & name, const std::string & filename)
	: cBulletBase(parent, "AngleBullet",filename)
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cAngleBullet::~cAngleBullet(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cAngleBullet::Initialize(void)
{
	cGame game = cGame::GetInstance();

	m_fHitRange = HIT_RANGE;

	m_nHp = 0;
	m_nAtk = DEFAULT_ATK;


	SetPriority(PRIORITY);

	cBulletBase::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cAngleBullet::Update(void)
{
	// ���������e�͏�����
	HitProc();

	// �G���A�A�E�g��������e������
	AreaOutAllProc();

	cBulletBase::Update();
}

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject* cAngleBullet::Finalize(void)
{
	cBulletBase::Finalize();

	return this;
}

//==========================================================================================
// ���ˊp�x�̃Z�b�g
// angle : �x���@�̊p�x,0�x���^��
//==========================================================================================
void cAngleBullet::SetShootAngle(float angle)
{
	angle += 90.0f;
	m_vPosUp.x = m_fSpeed * cos( DEG_TO_RAD(angle) );
	m_vPosUp.y = m_fSpeed * sin( DEG_TO_RAD(angle) );
}