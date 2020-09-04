/*==============================================================================*/
/*																				*/
/*	@file title	:	cTargetEffect.cpp											*/
/*  @brief		:	�^�[�Q�b�g�G�t�F�N�g�N���X									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/24													*/
/*																				*/
/*==============================================================================*/

#include "cTargetEffect.h"
#include "..\..\Enemy\cEnemyManager.h"
#include "..\..\..\..\Utility\utility.h"
#include "..\..\..\..\SoundCtrl\cSoundCtrl.h"
#include "..\cSpEffectManager.h"

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cTargetEffect::cTargetEffect(IBaseObject * parent)
	: cSpEffectObject(parent, "Target", "data\\graphic\\target01.png"),
	m_pTargetObj( nullptr ),
	m_nLifeTime(LIFE_TIME),
	m_pCircleSprite( nullptr ),
	m_eAnimState(TG_APPEAR)
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cTargetEffect::~cTargetEffect(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cTargetEffect::Initialize(void)
{
	m_pTargetObj = nullptr;
	m_eAnimState = TG_APPEAR;

	SetPriority(PRIORITY);
	m_BlendMode = DX_BLENDMODE_ADD;
	m_nColor = SPRITE_COLOR;

	SetScale(SCALE_RATE);
	SetAlpha( 0 );

	m_pCircleSprite = CreateDrawObject<cSpriteObject>(this,"TargetCircle","data\\graphic\\target02.png");

	// �^�[�Q�b�g�T�C�g�̉~�����̐ݒ�
	if (m_pCircleSprite)
	{
		m_pCircleSprite->SetDrawColor(SPRITE_COLOR);
		m_pCircleSprite->SetPriority(GetPriority());
		m_pCircleSprite->SetBlendMode(DX_BLENDMODE_ADD);
		m_pCircleSprite->SetScale( 0.0f );
	}

	cSoundCtrl::GetInstance().Play(SOUND_LOCK);
	cSpEffectObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cTargetEffect::Update(void)
{
	
	m_fAngle += ANGLE_ADD;

	switch (m_eAnimState)
	{
	case TG_APPEAR:
		Appear();
		break;
	case TG_FLASH:
		Flash();
		break;
	case TG_NORMAL:
		Normal();
		break;

	}

	// �~�����̃X�v���C�g�̍X�V
	if (m_pCircleSprite)
	{
		m_pCircleSprite->SetAngle(m_pCircleSprite->GetAngle() - ANGLE_ADD);
		m_pCircleSprite->SetPos(m_vPos);
	}

	// ���Ԍo�߂ŏ���
	m_nLifeTime--;
	if (m_nLifeTime <= 0)
	{
		m_eObjectState = OBJECT_STATE_DEAD;
		m_bVisible = false;
	}

	// �ǔ��Ώۂ������Ă���Βǔ�����
	if (IsSearchTargetAlive()) {
		m_vPos = m_pTargetObj->GetPos();
	} else
	{
		m_eObjectState = OBJECT_STATE_DEAD;
		m_bVisible = false;
	}

	cSpEffectObject::Update();
}

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject* cTargetEffect::Finalize(void)
{
	cSpEffectObject::Finalize();

	return this;
}

//==========================================================================================
// �ǔ��Ώۂ������Ă��邩�ǂ���
//==========================================================================================
bool cTargetEffect::IsSearchTargetAlive(void)
{
	for (auto it = cEnemyManager::GetInstance().GetChildList()->begin(); it != cEnemyManager::GetInstance().GetChildList()->end(); it++)
	{
		if (m_pTargetObj == (cSpriteObject*)*it) return true;
	}
	if((cSpriteObject*)m_pParentObject->FindSibling("Player") == m_pTargetObj) return true;

	return false;
}
//==========================================================================================
// �ǔ��Ώۂ̏d���`�F�b�N
// pObj : �d���Ώۂ̃I�u�W�F�N�g
// return true : �d�� false : �d���Ȃ�
//==========================================================================================
bool cTargetEffect::CheckDupulication(cSpriteObject* pObj)
{
	
	// �d�����ē����Ώۂɏo���Ă��邩�𒲂ׂ�
	for (auto it = cSpEffectManager::GetInstance().GetChildList()->begin(); it != cSpEffectManager::GetInstance().GetChildList()->end(); it++)
	{
		if (((cSpriteObject*)*it)->GetObjectName() == "Target")
		{
			if (pObj == ((cTargetEffect*)*it)->GetTargetObject())
			{
				return true;
			}
		}
	}
	return false;

}

//==========================================================================================
// �o��������
//==========================================================================================
void cTargetEffect::Appear(void)
{
	unsigned int alpha = GetAlpha() + ALPHA_MAX / APPEAR_TIME;

	SetAlpha(alpha);
	SetScale(GetScale().x - SCALE_RATE / APPEAR_TIME);

	if (alpha > ALPHA_MAX) SetAlpha(ALPHA_MAX);
	if (GetScale().x < 1.0f) SetScale(1.0f);

	// �~�����̏���
	if (m_pCircleSprite)
	{
		m_pCircleSprite->SetScale(m_pCircleSprite->GetScale().x + CIRCLE_SCALE_MAX / APPEAR_TIME);
		if(m_pCircleSprite->GetScale().x > CIRCLE_SCALE_MAX) m_pCircleSprite->SetScale(CIRCLE_SCALE_MAX);
	}

	// ���̏�Ԃֈڍs
	if (m_nLifeTime <= LIFE_TIME - APPEAR_TIME)
	{
		SetAlpha(ALPHA_MAX);
		SetScale(1.0f);
		m_eAnimState = TG_FLASH;
		// �^�[�Q�b�g���b�N�I����ԂŐF��ύX
		if(m_pCircleSprite) m_pCircleSprite->SetDrawColor(CIRCLE_DICISION_COLOR);
	}
}
//==========================================================================================
// �_�Ŏ�����
//==========================================================================================
void cTargetEffect::Flash(void)
{
	float angle = 360.0f / FLASH_INTERVAL * (float)(m_nLifeTime % FLASH_INTERVAL + 1);
	float theta = sin(DEG_TO_RAD(angle));
	unsigned int alpha = (unsigned int)((theta + 1.0f) * 127.5f);
	SetAlpha(alpha);

	// �~�����̏���
	if (m_pCircleSprite)
	{
		//m_pCircleSprite->SetAlpha(alpha);
		angle = 360.0f / CIRCLE_SCALE_INTERVAL * (float)(m_nLifeTime % CIRCLE_SCALE_INTERVAL + 1);
		theta = sin(DEG_TO_RAD(angle));
		m_pCircleSprite->SetScale(CIRCLE_SCALE_MAX + theta * CIRCLE_SCALE_RANGE);
	}
	// ���̏�Ԃֈڍs
	if (m_nLifeTime <= LIFE_TIME - APPEAR_TIME - FLASH_TIME)
	{
		if(m_pCircleSprite) m_pCircleSprite->SetAlpha(ALPHA_MAX);
		SetAlpha(ALPHA_MAX);
		m_eAnimState = TG_NORMAL;
	}
}
//==========================================================================================
// �ʏ펩����
//==========================================================================================
void cTargetEffect::Normal(void)
{
}
