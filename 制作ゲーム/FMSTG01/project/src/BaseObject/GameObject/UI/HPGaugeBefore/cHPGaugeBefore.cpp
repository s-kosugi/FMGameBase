/*==============================================================================*/
/*																				*/
/*	@file title	:	cHPGaugeBefore.cpp											*/
/*  @brief		:	HP�Q�[�W�I�u�W�F�N�g										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/28													*/
/*																				*/
/*==============================================================================*/

#include "cHPGaugeBefore.h"
#include "..\..\..\GameObject\Player\cPlayer.h"

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cHPGaugeBefore::cHPGaugeBefore(IBaseObject* parent) :
	cUIObject(parent, "HPGaugeBefore", "data\\graphic\\HPGauge.png")
{

}

//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cHPGaugeBefore::~cHPGaugeBefore(void)
{
}

//==========================================================================================
//  ������
//==========================================================================================
void
cHPGaugeBefore::
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
void cHPGaugeBefore::Update(void)
{
	cSpriteObject* obj = (cSpriteObject*)FindSibling("HPGauge");
	if (obj)
	{
		SetVisible(true);
		if (m_fStartAngle < obj->GetStartAngle())
		{
			m_fEndAngle = obj->GetStartAngle();
			// �Q�[�W�����炷
			m_fStartAngle += 0.1f;
			if (m_fStartAngle > obj->GetStartAngle())
			{
				m_fStartAngle = obj->GetStartAngle();
			}
			SetDrawColor(COLOR_RED);
		}
		else
		{
			SetVisible(false);
		}
	}
	cUIObject::Update();
}

//==========================================================================================
//  ���
//==========================================================================================
IBaseObject* cHPGaugeBefore::Finalize(void)
{
	cUIObject::Finalize();
	return this;
}