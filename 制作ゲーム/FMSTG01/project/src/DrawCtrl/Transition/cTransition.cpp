/*==============================================================================*/
/*																				*/
/*	@file title	:	cTransition.cpp												*/
/*  @brief		:	�g�����W�V�������X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/03/11													*/
/*																				*/
/*==============================================================================*/

#include <DxLib.h>
#include "cTransition.h"
#include "..\cDrawCtrl.h"

//==========================================================================================
// �萔
const float cTransition::BORDER_ADD_DEFAULT = 4.0f;
const int	cTransition::BORDER_MAX = 255;
const int	cTransition::DEFAULT_PRIORITY = 30000;

const std::string cTransition::RULE_CHECKSPHERE = "data\\graphic\\rule01.png";
//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cTransition::cTransition(const std::string& filename,IDrawBase* pObj) :
	IDrawBase(filename),
	m_pTransObj(pObj),
	m_eBorderRange(RANGE_64),
	m_fBorderParam(0.0f),
	m_fBorderParam_Add(BORDER_ADD_DEFAULT),
	m_eTransDirection(TRANS_IN)
{
	// �g�����W�V�����̓I�u�W�F�N�g�폜���Ƀ���������A�����[�h����
	m_bUnload = true;

	SetPriority(DEFAULT_PRIORITY);
	// �`�����o�^
	cDrawCtrl::GetInstance().RegistTransition(*this, filename);
}
//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cTransition::~cTransition()
{
	cDrawCtrl::GetInstance().RemoveDrawObject(this);
}
//==========================================================================================
//  ������
//==========================================================================================
void cTransition::Initialize(void)
{
}
//==========================================================================================
//  �X�V
//==========================================================================================
void cTransition::Update(void)
{
	if (m_eTransDirection == TRANS_IN)
	{
		// ���E�ʒu���X�V
		m_fBorderParam += m_fBorderParam_Add;
		if (m_fBorderParam >= BORDER_MAX)
		{
			m_fBorderParam = (float)BORDER_MAX;
		}
	}
	else
	{
		// TRANS_OUT
		// ���E�ʒu���X�V
		m_fBorderParam -= m_fBorderParam_Add;
		if (m_fBorderParam <= 0)
		{
			m_fBorderParam = 0.0f;
		}
	}
}
//==========================================================================================
//  ���
//==========================================================================================
void cTransition::Finalize(void)
{
}
//==========================================================================================
//  �g�����W�V�������I���������ǂ���
//==========================================================================================
bool cTransition::IsEnd(void)
{
	if (m_eTransDirection == TRANS_IN)
	{
		if (m_fBorderParam >= BORDER_MAX) return true;
		return false;
	}
	if (m_eTransDirection == TRANS_OUT)
	{
		if (m_fBorderParam <= 0) return true;
		return false;
	}
	return false;
}
