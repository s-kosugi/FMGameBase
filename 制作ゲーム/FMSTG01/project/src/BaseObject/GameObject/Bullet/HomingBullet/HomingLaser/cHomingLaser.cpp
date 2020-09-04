/*==============================================================================*/
/*																				*/
/*	@file title	:	cHomingLaser.cpp											*/
/*  @brief		:	�z�[�~���O���[�U�[�N���X									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/21													*/
/*																				*/
/*==============================================================================*/

#include "cHomingLaser.h"
#include "..\..\cBulletManager.h"

//==========================================================================================
// �萔
//==========================================================================================
const float cHomingLaser::HIT_RANGE = 6.0f;		// �����蔻��̑傫��
const int cHomingLaser::PRIORITY = 300;			// �\���D��x
const int cHomingLaser::NEXT_LASER_TIME = 5;	// �����[�U�[�̃|�b�v���ԏ����l
const int cHomingLaser::DEFAULT_ATK = 50;		// �f�t�H���g�U����

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cHomingLaser::cHomingLaser(IBaseObject * parent)
	: cHomingBullet(parent, "HomingLaser", "data\\graphic\\Bullet_04.png"),
	m_pPrevLaser( nullptr ),
	m_nNextPopTime(NEXT_LASER_TIME),
	m_nLaserLifeTime(0),
	m_nLaserNum(0)
{
}

cHomingLaser::cHomingLaser(IBaseObject * parent, const std::string & name, const std::string & filename)
	: cHomingBullet(parent, "HomingLaser", filename),
	m_pPrevLaser(nullptr),
	m_nNextPopTime(NEXT_LASER_TIME),
	m_nLaserLifeTime(0),
	m_nLaserNum(0)
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cHomingLaser::~cHomingLaser(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cHomingLaser::Initialize(void)
{
	m_listVectorHistory.clear();
	m_nNextPopTime = NEXT_LASER_TIME;

	m_fHitRange = HIT_RANGE;

	m_nHp = 0;
	m_nAtk = DEFAULT_ATK;

	m_vPosUp.x = 0;
	m_vPosUp.y = 0;

	SetPriority(PRIORITY);

	cHomingBullet::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cHomingLaser::Update(void)
{
	if(!IsSearchPrevLaserAlive() ) m_pPrevLaser = nullptr;

	if (m_pPrevLaser == nullptr)
	{
		// �擪���[�U�[�͒ʏ�̃z�[�~���O�e�Ɠ�������������
		cHomingBullet::Update();

		// �ړ������̕ۑ�
		VectorHistory vh;
		vh.vPos = m_vPos;
		vh.vPosUp = m_vPosUp;
		m_listVectorHistory.push_back(vh);
	}
	else
	{
		// �O���[�U�[�̓����ɒǏ]������
		VectorHistory vh = m_pPrevLaser->GetVectorHistory();
		m_vPos = vh.vPos;
		m_vPosUp = vh.vPosUp;
		m_listVectorHistory.push_back(vh);

		// �ړ���̕\���p�x�ݒ菈��
		RotateMoveAfter();

		// �x�[�X�N���X��ʂ�Ȃ��׎q���[�U�[�͎����ō폜����������
		m_nLifeTime--;
		if (m_nLifeTime <= 0) m_eObjectState = OBJECT_STATE_DEAD;

		// �G���A�A�E�g��������e������
		AreaOutAllProc();
	}
	// �ő吔���z������Ō×������폜
	// �ő吔�̓��[�U�[�o���t���[���Ɠ�����
	if (m_listVectorHistory.size() > m_nNextPopTime)
		m_listVectorHistory.erase(m_listVectorHistory.begin());

	// �����[�U�[�̐���
	CreateNextLaser();	
}

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject* cHomingLaser::Finalize(void)
{
	cHomingBullet::Finalize();

	return this;
}

//==========================================================================================
// �O���[�U�[�������Ă��邩�ǂ����𒲂ׂ�
//==========================================================================================
bool cHomingLaser::IsSearchPrevLaserAlive(void)
{
	for (auto it = cBulletManager::GetInstance().GetChildList()->begin(); it != cBulletManager::GetInstance().GetChildList()->end(); it++)
	{
		if ((cSpriteObject*)m_pPrevLaser == (cSpriteObject*)*it) return true;
	}

	return false;
}
//==========================================================================================
// �����[�U�[�̐���
//==========================================================================================
void cHomingLaser::CreateNextLaser(void)
{
	m_nLaserLifeTime++;
	// ��莞�Ԃ��o�߂����玟���[�U�[�𐶐�����
	if (m_nLaserLifeTime == m_nNextPopTime && m_nLaserNum > 0)
	{
		m_nLaserNum--;
		VectorHistory vh = m_listVectorHistory[m_listVectorHistory.size() - 1];
		cHomingLaser* bul = (cHomingLaser*)cBulletManager::GetInstance().Create(
			BT_HOMING_LASER, vh.vPos, HIT_PLAYER, m_fSpeed);
		bul->SetDrawColor(m_nColor);
		bul->SetPosUp(vh.vPosUp);
		bul->SetRotLimit(m_fRotLimit);
		bul->SetPrevLaserPointer(this);
		bul->SetLaserNum(m_nLaserNum);
		bul->SetNextPopTime(m_nNextPopTime);
		bul->SetAreaOutAdjust( m_nAreaOutAdjust );
	}
}
