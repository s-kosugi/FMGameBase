/*==============================================================================*/
/*																				*/
/*	@file title	:	cHomingLaserTale.cpp										*/
/*  @brief		:	�z�[�~���O���[�U�[(���Ђ�t)�N���X							*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/211													*/
/*																				*/
/*==============================================================================*/

#include "cHomingLaserTale.h"
#include "..\..\cBulletManager.h"
#include "..\..\..\Effect\cEffectManager.h"

//==========================================================================================
// �萔
const float cHomingLaserTale::HIT_RANGE = 6.0f;	// �����蔻��̑傫��
const int cHomingLaserTale::PRIORITY = 300;		// �\���D��x
const int cHomingLaserTale::NEXT_LASER_TIME = 5;// �����[�U�[�̃|�b�v���ԏ����l
const int cHomingLaserTale::DEFAULT_ATK = 50;	// �f�t�H���g�U����

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cHomingLaserTale::cHomingLaserTale(IBaseObject * parent)
	: cHomingBullet(parent, "HomingLaserTale", "data\\graphic\\Bullet_04.png"),
	m_nNextPopTime(NEXT_LASER_TIME),
	m_nLaserLifeTime(0),
	m_nLaserNum(0)
{
}

cHomingLaserTale::cHomingLaserTale(IBaseObject * parent, const std::string & name, const std::string & filename)
	: cHomingBullet(parent, "HomingLaserTale", filename),
	m_nNextPopTime(NEXT_LASER_TIME),
	m_nLaserLifeTime(0),
	m_nLaserNum(0)
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cHomingLaserTale::~cHomingLaserTale(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cHomingLaserTale::Initialize(void)
{
	cHomingBullet::Initialize();

	m_listHistory.clear();
	m_listTaleCreateTime.clear();
	m_nNextPopTime = NEXT_LASER_TIME;

	m_fHitRange = HIT_RANGE;

	m_nHp = 0;
	m_nAtk = DEFAULT_ATK;

	m_vPosUp.x = 0;
	m_vPosUp.y = 0;

	SetPriority(PRIORITY);

}

//==========================================================================================
// �X�V
//==========================================================================================
void cHomingLaserTale::Update(void)
{
	HitProc();

	// �I�u�W�F�N�g�����S��Ԃ�������ړ����������Ȃ��悤�ɂ���
	if (m_eState == STATE_DEAD)
	{
		// �q�����Ȃ����ɓ��������炻�̂܂܍폜
		if (m_listChildObject.empty() && m_eState == STATE_DEAD){
			m_eObjectState = OBJECT_STATE_DEAD;
			return;
		}

		// ��~���Č����Ȃ���Ԃɂ��Ă���
		m_bVisible = false;
		m_vPosUp.x = m_vPosUp.y = m_fSpeed = 0.0f;

		// �G���A�O�܂��͎q�����鎞�̓I�u�W�F�N�g�������Ȃ��B
		m_eObjectState = OBJECT_STATE_ACTIVE;
	}

	cHomingBullet::Update();

	// �ړ������̕ۑ�
	SaveHistory();

	// ���[�U�[�̔��̈ړ�
	if (MoveLaserTale())
	{
		// �S�Ă̎q�����Ȃ��Ȃ����^�C�~���O�ŃI�u�W�F�N�g���폜����
		if (m_listChildObject.empty())
		{
			m_eObjectState = OBJECT_STATE_DEAD;
			return;
		}
	}

	// �ő吔���z������Ō×������폜
	// �ő吔�̓��[�U�[�����������[�U�[�����Ԋu
	if (m_listHistory.size() > m_nNextPopTime * m_nLaserNum)
		m_listHistory.erase(m_listHistory.begin());

	// �����[�U�[�̔�����
	CreateLaserTale();
}

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject* cHomingLaserTale::Finalize(void)
{
	cHomingBullet::Finalize();

	return this;
}
//==========================================================================================
// �ړ������̕ۑ�
//==========================================================================================
void cHomingLaserTale::SaveHistory(void)
{
	History vh;
	vh.vPos = m_vPos;
	vh.fAngle = m_fAngle;
	m_listHistory.push_back(vh);
}
//==========================================================================================
// ���[�U�[�̔��ړ�
// return : �폜�������[�U�[������ꍇ��true
//==========================================================================================
bool cHomingLaserTale::MoveLaserTale(void)
{
	int i = 0;
	for (auto it = m_listChildObject.begin(); it != m_listChildObject.end();it++, i++)
	{
		cSpriteObject* obj = (cSpriteObject*)(*it);
		History hs = m_listHistory[m_listHistory.size() - 1 - m_listTaleCreateTime[i]];
		obj->SetPos(hs.vPos);
		obj->SetAngle(hs.fAngle);

		if (hs.vPos.x == m_vPos.x && hs.vPos.y == m_vPos.y)
		{
			cEffectObject* ef = cEffectManager::GetInstance().Create(EFFECT_HIT, obj->GetPos());
			ef->SetDrawColor(obj->GetDrawColor());

			// ���[�U�[�̔��̍폜
			obj->Finalize();
			SAFE_DELETE(obj);
			it = m_listChildObject.erase(it);
			m_listTaleCreateTime.erase(m_listTaleCreateTime.begin() + i);

			return true;
		}
	}
	return false;
}
//==========================================================================================
// ���[�U�[�̔�����
//==========================================================================================
void cHomingLaserTale::CreateLaserTale(void)
{
	m_nLaserLifeTime++;
	// ��莞�Ԃ��o�߂����玟���[�U�[�̔��𐶐�����
	if (m_nLaserLifeTime % m_nNextPopTime == m_nNextPopTime -1 && m_nLaserNum * m_nNextPopTime > m_nLaserLifeTime)
	{
		// ���t���[���ڂŐ������ꂽ�����L������
		m_listTaleCreateTime.push_back((unsigned int)m_nLaserLifeTime);

		// ���[�U�[�̔��̉摜�𐶐�
		cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this,"LaserTale" + m_listTaleCreateTime.size(),m_sFileName);
		obj->SetDrawColor(m_nColor);
		// �������Ԃ���ǂ̈ʒu�̗������g�p���Ĉʒu���Z�b�g���邩�����肷��
		obj->SetPos(m_listHistory[m_listHistory.size() - m_nLaserLifeTime].vPos);
		obj->SetAngle(m_listHistory[m_listHistory.size() - m_nLaserLifeTime].fAngle);
		obj->SetPriority(GetPriority());
	}
}
