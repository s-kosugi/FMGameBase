/*==============================================================================*/
/*																				*/
/*	@file title	:	cHomingBullet.cpp											*/
/*  @brief		:	�z�[�~���O�e�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/21													*/
/*																				*/
/*==============================================================================*/

#include "cHomingBullet.h"
#include "..\..\..\..\cGame.h"
#include "..\..\..\..\Utility\utility.h"
#include "..\..\Player\cPlayer.h"
#include "..\..\Enemy\cEnemyManager.h"

const float cHomingBullet::HIT_RANGE = 6.0f;	// �����蔻��傫��
const int	cHomingBullet::PRIORITY = 300;		// �\���D��x
const float cHomingBullet::ROT_LIMIT = 1.5f;	// �������p�x�����l
const int   cHomingBullet::LIFE_TIME = 360;		// �e�̐������ԃf�t�H���g�l
const int	cHomingBullet::DEFAULT_ATK = 50;	// �f�t�H���g�U����

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cHomingBullet::cHomingBullet(IBaseObject * parent)
	: cBulletBase(parent, "HomingBullet", "data\\graphic\\Bullet_01.png"),
	m_fRotLimit(ROT_LIMIT),
	m_bAlwaysSearch( true ),
	m_pTargettingObj( nullptr),
	m_nLifeTime( LIFE_TIME )
{
}

cHomingBullet::cHomingBullet(IBaseObject * parent, const std::string & name, const std::string & filename)
	: cBulletBase(parent, "HomingBullet", filename),
	m_fRotLimit(ROT_LIMIT),
	m_bAlwaysSearch( true ),
	m_pTargettingObj(nullptr),
	m_nLifeTime( LIFE_TIME )
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cHomingBullet::~cHomingBullet(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cHomingBullet::Initialize(void)
{
	m_fHitRange = HIT_RANGE;

	m_nHp = 0;
	m_nAtk = DEFAULT_ATK;

	m_vPosUp.x = 0;
	m_vPosUp.y = 0;

	m_fRotLimit = ROT_LIMIT;
	m_bAlwaysSearch = true;
	m_nLifeTime = LIFE_TIME;
	m_pTargettingObj = nullptr;

	SetPriority(PRIORITY);

	cBulletBase::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cHomingBullet::Update(void)
{
	// �e�������������̋��ʏ���
	HitProc();

	// �^�[�Q�b�g��T��
	// �펞�T�[�`�����Ȃ��ꍇ�̓^�[�Q�b�g�������Ă��邩���m�F����
	if( m_bAlwaysSearch ) m_pTargettingObj = SearchTargettingObject( );
	else if( m_pTargettingObj != nullptr && !IsSearchTargetAlive() ) m_pTargettingObj = nullptr;

	if (m_pTargettingObj != nullptr)
	{
		// �z�[�~���O��̈ړ��x�N�g�������߂�
		CalcHomingMove(m_vPosUp, m_pTargettingObj->GetPos());
	} else
	{
		if (m_vPosUp.x == 0 && m_vPosUp.y == 0)
		{
			// �����Ǐ]���Ȃ��ꍇ�͒����ɓ���
			if (m_eHitCate == HIT_ENEMY) m_vPosUp.y = m_fSpeed;
			if (m_eHitCate == HIT_PLAYER) m_vPosUp.y = -m_fSpeed;
		}
	}

	// ��莞�Ԍo�����������
	m_nLifeTime--;
	if( m_nLifeTime <= 0 ) m_eObjectState = OBJECT_STATE_DEAD;

	cBulletBase::Update();

	// �G���A�A�E�g��������e������
	AreaOutAllProc();
}

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject* cHomingBullet::Finalize(void)
{
	cBulletBase::Finalize();

	return this;
}

//==========================================================================================
// �z�[�~���O�̈ړ��x�N�g�������߂�
// hVec : �z�[�~���O��̈ړ��x�N�g����Ԃ�
// trgPos : �z�[�~���O�Ώۂ̍��W
//==========================================================================================
void cHomingBullet::CalcHomingMove(cVector2 & hVec, const cVector2& trgPos)
{
	cVector2 tPos = trgPos;	// �Ώۂ̍��W
	cVector2 srVec = m_vPosUp;	// ���̈ړ��x�N�g��
	cVector2 trVec;			// �ǔ��Ώۂւ̈ړ��x�N�g��

											// �ǔ��Ώۂւ̈ړ��x�N�g�������߂�
	CalcTargetVector(tPos, trVec);

	// ����p�x����̃x�N�g�������߂�
	CalcRotateLimit(hVec, srVec, trVec, tPos);
}
//==========================================================================================
// �ǔ��Ώۂֈړ�����x�N�g�������߂�
// tPos : �ǔ��Ώۂ̍��W
// tVec : �ړ��x�N�g��
//==========================================================================================
void cHomingBullet::CalcTargetVector(const cVector2 & tPos, cVector2& tVec)
{
	float dist = m_vPos.CalsTwoPointDist(tPos);
	if (dist)
	{
		// �������玩���̈ړ����x�{�����|����
		tVec.x = (tPos.x - m_vPos.x) / dist * m_fSpeed;
		tVec.y = (tPos.y - m_vPos.y) / dist * m_fSpeed;
	} else
	{
		// �d�Ȃ��Ă���Ƃ��͐^���ֈړ�����
		tVec.x = 0;
		tVec.y = m_fSpeed;
	}
}
//==========================================================================================
// �������p�x�����������ړ��x�N�g�������߂�
// rVec : �������̉��������ړ��x�N�g����Ԃ�
// srcVec : ���݂̈ړ��x�N�g��
// trgVec : �ǔ��Ώۂւ̈ړ��x�N�g��
// trgPos : �ǔ��Ώۂ̍��W
//==========================================================================================
void cHomingBullet::CalcRotateLimit(cVector2 & rVec, const cVector2& srcVec, const cVector2& trgVec, const cVector2& trgPos)
{
	// ����p�x����̑��x�x�N�g��
	cVector2 vLimit,vComp;
	float limAngle = DEG_TO_RAD(m_fRotLimit);
	vLimit.x = cos(limAngle) * srcVec.x - sin(limAngle) * srcVec.y;
	vLimit.y = sin(limAngle) * srcVec.x + cos(limAngle) * srcVec.y;

	// �ǔ��Ώە����Ɛ���p�x����̂ǂ���ɂ܂��邩�����߂�
	if (vComp.DotProduct(srcVec,trgVec) >= vComp.DotProduct(srcVec,vLimit))
	{
		// ����͈͓��Ȃ̂Œǔ��Ώە����ւ��̂܂܈ړ�
		rVec = trgVec;
	} else
	{
		//����͈͊O�̏ꍇ�͍�������p�x�̃x�N�g�������߂�
		cVector2 vRevLimit;
		vRevLimit.x = cos(limAngle) * srcVec.x + sin(limAngle) * srcVec.y;
		vRevLimit.y = -sin(limAngle) * srcVec.x + cos(limAngle) * srcVec.y;

		// �e���玩�@�ւ̑��΃x�N�g��
		cVector2 sVec;
		sVec.x = trgPos.x - m_vPos.x;
		sVec.y = trgPos.y - m_vPos.y;

		// �E��肩���������߂�
		if (sVec.DotProduct(vLimit) >= sVec.DotProduct(vRevLimit))
		{
			// �E���
			rVec = vLimit;
		} else
		{
			// �����
			rVec = vRevLimit;
		}
	}
}
//==========================================================================================
// �ǔ��Ώۂ̃I�u�W�F�N�g��T��
//==========================================================================================
cSpriteObject * cHomingBullet::SearchTargettingObject(void)
{
	cSpriteObject* obj = nullptr;
	// �G�e�̏ꍇ�̓v���C���[���^�[�Q�b�g�ɂ���
	if (m_eHitCate == HIT_ENEMY) obj = (cSpriteObject*)m_pParentObject->FindSibling("Player");
	// ���e�̏ꍇ�͈�ԋ߂��G��T��
	if (m_eHitCate == HIT_PLAYER) obj = SearchTargettingEnemy();

	return obj;
}

//==========================================================================================
// �ǔ��Ώۂ̓G��T��
//==========================================================================================
cSpriteObject* cHomingBullet::SearchTargettingEnemy(void)
{
	cSpriteObject* min = nullptr;
	float dist = 3000.0f;

	for (auto it = cEnemyManager::GetInstance().GetChildList()->begin(); it != cEnemyManager::GetInstance().GetChildList()->end(); it++)
	{
		// ��ԋ߂��G��T��
		float temp = m_vPos.CalsTwoPointDist(((cSpriteObject*)(*it))->GetPos());
		if (dist > temp)
		{
			dist = temp;
			min = (cSpriteObject*)(*it);
		}
	}
	return min;
}
//==========================================================================================
// �ǔ��Ώۂ������Ă��邩�ǂ���
//==========================================================================================
bool cHomingBullet::IsSearchTargetAlive(void)
{
	if (m_eHitCate == HIT_PLAYER)
	{
		for (auto it = cEnemyManager::GetInstance().GetChildList()->begin(); it != cEnemyManager::GetInstance().GetChildList()->end(); it++)
		{
			if (m_pTargettingObj == (cSpriteObject*)*it) return true;
		}
	}
	if (m_eHitCate == HIT_ENEMY)
	{
		if ((cSpriteObject*)m_pParentObject->FindSibling("Player") != nullptr) return true;
	}

	return false;
}
//==========================================================================================
// �����_���^�[�Q�b�g�ݒ�
//==========================================================================================
cSpriteObject* cHomingBullet::SetRandomTarget(void)
{
	// �G�e�̏ꍇ�̓v���C���[���^�[�Q�b�g�ɂ���
	if (m_eHitCate == HIT_ENEMY)
	{
		m_pTargettingObj = (cSpriteObject*)m_pParentObject->FindSibling("Player");
	}
	// ���e�̏ꍇ�̓����_���ȃ^�[�Q�b�g��ݒ肷��
	if (m_eHitCate == HIT_PLAYER)
	{
		int random = cGame::Random(0,cEnemyManager::GetInstance().GetChildList()->size()-1);
		int i = 0;
		for (auto it = cEnemyManager::GetInstance().GetChildList()->begin(); it != cEnemyManager::GetInstance().GetChildList()->end(); it++,i++)
		{
			if (i == random)
			{
				m_pTargettingObj = (cSpriteObject*)(*it);
			}
		}
	}
	return m_pTargettingObj;
}

//==========================================================================================
// ���ˊp�x�̃Z�b�g
// angle : �x���@�̊p�x,0�x���^��
//==========================================================================================
void cHomingBullet::SetShootAngle(float angle)
{
	angle += 90.0f;
	m_vPosUp.x = m_fSpeed * cos(DEG_TO_RAD(angle));
	m_vPosUp.y = m_fSpeed * sin(DEG_TO_RAD(angle));
}