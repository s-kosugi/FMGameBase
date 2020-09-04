/*==============================================================================*/
/*																				*/
/*	@file title	:	cHPGauge.cpp												*/
/*  @brief		:	HP�Q�[�W�I�u�W�F�N�g										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/28													*/
/*																				*/
/*==============================================================================*/

#include "cHPGauge.h"
#include "..\..\..\GameObject\Player\cPlayer.h"
#include "..\..\Effect\cEffectManager.h"
#include "..\..\..\..\Utility\utility.h"

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cHPGauge::cHPGauge(IBaseObject* parent) :
	cUIObject(parent, "HPGauge", "data\\graphic\\HPGauge.png")
{

}

//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cHPGauge::~cHPGauge(void)
{
}

//==========================================================================================
//  ������
//==========================================================================================
void
cHPGauge::
Initialize(void)
{
	m_eSpType = cSprite::SPTYPE_CIRCLEGAUGE;
	m_fStartAngle = START_ANGLE;
	m_fEndAngle = END_ANGLE;
	SetPriority(PRIORITY);

	cUIObject::Initialize();
}

//==========================================================================================
//  �X�V
//==========================================================================================
void cHPGauge::Update(void)
{
	cPlayer* pl = (cPlayer*)GetParent()->FindSibling("Player");
	if (pl)
	{
		float afterangle= END_ANGLE - ((float)pl->GetHp()) / ((float)pl->GetMaxHp()) * m_fEndAngle;
		if (afterangle != m_fStartAngle)
		{
			cVector2 effectPos = m_vPos;
			// 100%��360�x�ɕϊ�
			float angle = m_fStartAngle * 3.6f;
			// �p�x���ォ��N�_�ɂ���
			angle -= 90.0f;
			effectPos.x = effectPos.x + cos(DEG_TO_RAD(angle)) * EFFECT_START_DIFF;
			effectPos.y = effectPos.y + sin(DEG_TO_RAD(angle)) * EFFECT_START_DIFF;
			cEffectObject* obj = cEffectManager::GetInstance().Create(EFFECT_BREAK, effectPos);
			obj->SetDrawColor(COLOR_RED);

			m_fStartAngle = afterangle;
		}
	}
	cUIObject::Update();
}

//==========================================================================================
//  ���
//==========================================================================================
IBaseObject* cHPGauge::Finalize(void)
{
	cUIObject::Finalize();
	return this;
}