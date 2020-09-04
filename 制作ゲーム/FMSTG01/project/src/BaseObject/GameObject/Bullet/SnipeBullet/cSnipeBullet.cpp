/*==============================================================================*/
/*																				*/
/*	@file title	:	cSnipeBullet.cpp											*/
/*  @brief		:	�z�[�~���O�e�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/21													*/
/*																				*/
/*==============================================================================*/

#include "cSnipeBullet.h"
#include "..\..\..\..\cGame.h"
#include "..\..\..\..\Utility\utility.h"
#include "..\..\Player\cPlayer.h"
#include "..\..\Enemy\cEnemyManager.h"

//==========================================================================================
// �萔
//==========================================================================================
const float cSnipeBullet::HIT_RANGE = 6.0f;		// �����蔻��̑傫��
const int	cSnipeBullet::PRIORITY = 300;		// �\���D��x
const int	cSnipeBullet::DEFAULT_ATK = 50;		// �f�t�H���g�U����

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cSnipeBullet::cSnipeBullet(IBaseObject * parent)
	: cBulletBase(parent, "SnipeBullet", "data\\graphic\\Bullet_01.png")
{
}

cSnipeBullet::cSnipeBullet(IBaseObject * parent, const std::string & name, const std::string & filename)
	: cBulletBase(parent, "SnipeBullet", filename)
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cSnipeBullet::~cSnipeBullet(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cSnipeBullet::Initialize(void)
{
	m_fHitRange = HIT_RANGE;

	m_nHp = 0;
	m_nAtk = DEFAULT_ATK;

	m_vPosUp.x = 0;
	m_vPosUp.y = 0;

	if (m_eHitCate == HIT_ENEMY)
	{
		cSpriteObject* obj = nullptr;
		// �G�e�̏ꍇ�̓v���C���[���^�[�Q�b�g�ɂ���
		if (m_eHitCate == HIT_ENEMY) obj = (cSpriteObject*)m_pParentObject->FindSibling("Player");

		if( obj != nullptr ) CalcTargetVector(obj->GetPos());
	}

	SetPriority(PRIORITY);

	cBulletBase::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cSnipeBullet::Update(void)
{
	// �e�������������̋��ʏ���
	HitProc();

	cBulletBase::Update();

	// �G���A�A�E�g��������e������
	AreaOutAllProc();
}

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject* cSnipeBullet::Finalize(void)
{
	cBulletBase::Finalize();

	return this;
}
//==========================================================================================
// �ǔ��Ώۂֈړ�����x�N�g�������߂�
// tPos : �ǔ��Ώۂ̍��W
//==========================================================================================
void cSnipeBullet::CalcTargetVector(const cVector2 & tPos)
{
	float dist = m_vPos.CalsTwoPointDist(tPos);
	if (dist)
	{
		// �������玩���̈ړ����x�{�����|����
		m_vPosUp.x = (tPos.x - m_vPos.x) / dist * m_fSpeed;
		m_vPosUp.y = (tPos.y - m_vPos.y) / dist * m_fSpeed;
	} else
	{
		// �d�Ȃ��Ă���Ƃ��͐^���ֈړ�����
		m_vPosUp.x = 0;
		m_vPosUp.y = m_fSpeed;
	}
}

//==========================================================================================
// ���ˊp�x�̃Z�b�g
// angle : �x���@�̊p�x,0�x���^��
//==========================================================================================
void cSnipeBullet::SetShootAngle(float angle)
{
	angle += 90.0f;
	m_vPosUp.x = m_fSpeed * cos(DEG_TO_RAD(angle));
	m_vPosUp.y = m_fSpeed * sin(DEG_TO_RAD(angle));
}