/*==============================================================================*/
/*																				*/
/*	@file title	:	cBulletBase.cpp												*/
/*  @brief		:	�e�x�[�X�N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/07													*/
/*																				*/
/*==============================================================================*/

#include "cBulletBase.h"
#include "..\..\..\cGame.h"
#include "..\Effect\cEffectManager.h"
#include "..\Effect\cEffectObject.h"

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cBulletBase::cBulletBase(IBaseObject * parent, const std::string object_name, const std::string graphic_file_name)
	: cHitObject(parent, object_name, graphic_file_name), m_fSpeed(0.0f), m_vPosUp(0.0f,0.0f)
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cBulletBase::~cBulletBase(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cBulletBase::Initialize(void)
{

	cHitObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cBulletBase::Update(void)
{
	// �ړ���̉�]����
	RotateMoveAfter();

	m_vPos.x += m_vPosUp.x;
	m_vPos.y += m_vPosUp.y;

	cHitObject::Update();
}

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject* cBulletBase::Finalize(void)
{
	cHitObject::Finalize();

	return this;
}

//==========================================================================================
// �e�������������̏���
//==========================================================================================
void cBulletBase::HitProc(void)
{
	// ���������e�͏�����
	if (m_eState == STATE_HIT)
	{
		// �q�b�g�G�t�F�N�g���o��
		cEffectObject* obj = cEffectManager::GetInstance().Create(EFFECT_HIT, m_vPos);
		obj->SetDrawColor(m_nColor);
		m_eState = STATE_DEAD;
		m_eObjectState = OBJECT_STATE_DEAD;
	}
}

//==========================================================================================
// �ړ���̃X�v���C�g��]����
//==========================================================================================
void cBulletBase::RotateMoveAfter(void)
{
	cVector2 afterPos;		// �ړ�����W
	afterPos = m_vPos + m_vPosUp;

	// �ړ��O�ƈړ���̍��W����\���p�x�����߂�
	m_fAngle = m_vPos.CalcTwoPointAngle(afterPos) + 90.0f;
}