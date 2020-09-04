/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnemyBase.cpp												*/
/*  @brief		:	�G�x�[�X�N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "cEnemyBase.h"
#include "..\..\..\ScoreManager\cScoreManager.h"
#include "..\Effect\cEffectManager.h"

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cEnemyBase::cEnemyBase(IBaseObject * parent, const std::string object_name, const std::string graphic_file_name)
	: cHitObject(parent, object_name, graphic_file_name),
	m_vPosUp(0.0f,0.0f),
	m_nScore(0)
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cEnemyBase::~cEnemyBase(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cEnemyBase::Initialize(void)
{
	cHitObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cEnemyBase::Update(void)
{
	m_vPos.x += m_vPosUp.x;
	m_vPos.y += m_vPosUp.y;


	switch (m_eState)
	{
	case STATE_HIT:
		// �c��HP�����ăI�u�W�F�N�g�̏�Ԃ�ύX����
		if (m_nHp <= 0)
		{
			m_eState = STATE_DEAD;


			// �X�R�A���Z
			cScoreManager::GetInstance().AddScore(m_nScore);
			// �G�t�F�N�g���Đ�
			cEffectManager::GetInstance().Create(EFFECT_BOM, m_vPos);
		}
		else m_eState = STATE_NORMAL;
		break;
	case STATE_DEAD:
		// �I�u�W�F�N�g�̍폜������
		m_eObjectState = OBJECT_STATE_DEAD;
		break;
	}
	cHitObject::Update();
}

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject* cEnemyBase::Finalize(void)
{
	cHitObject::Finalize();

	return this;
}