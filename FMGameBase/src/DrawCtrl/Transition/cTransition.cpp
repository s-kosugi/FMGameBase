/*==============================================================================*/
/*																				*/
/*	@file title	:	cTransition.cpp												*/
/*	@brief		:	�g�����W�V�����N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/03/11													*/
/*																				*/
/*==============================================================================*/

#include "cTransition.h"
#include "..\cDrawCtrl.h"
#include "Utility/Easing/Easing.h"

//==========================================================================================
// �萔
const float	cTransition::BORDER_MAX = 255;
const int	cTransition::DEFAULT_PRIORITY = 30000;

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cTransition::cTransition(const std::string& filename, IDrawBase* pObj, TransDirection dir, float transtime) :
	IDrawBase(filename),
	m_pTransObj(pObj),
	m_eBorderRange(BorderRange::RANGE_64),
	m_fBorderParam(0.0f),
	m_eTransDirection(dir),
	m_fTransTime(transtime),
	m_cTimer(nullptr, "TransTimer")
{
	// �g�����W�V���������ɂ���ď������E�ʒu��ύX����
	if (dir == TransDirection::TRANS_IN) m_fBorderParam = 0.0f;
	else m_fBorderParam = (float)BORDER_MAX;

	// �g�����W�V�����̓I�u�W�F�N�g�폜���Ƀ���������A�����[�h����
	m_bUnload = true;

	// �^�C�}�[�̃Z�b�g
	m_cTimer.Setup(m_fTransTime);

	SetPriority(DEFAULT_PRIORITY);
	// �`�����o�^
	cDrawCtrl::GetInstance().RegistTransition(*this, filename);
}
//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cTransition::~cTransition()
{
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
	m_cTimer.Update();
	if (m_eTransDirection == TransDirection::TRANS_IN)
	{
		m_fBorderParam = Easing::Linear(m_cTimer.GetTime(), m_cTimer.GetLimit(), BORDER_MAX, 0.0f);
	}
	else
	{
		m_fBorderParam = Easing::Linear(m_cTimer.GetTime(), m_cTimer.GetLimit(), 0.0f, BORDER_MAX);
	}
}
//==========================================================================================
//  ���
//==========================================================================================
void cTransition::Finalize(void)
{
	m_cTimer.Finalize();
}
//==========================================================================================
//  �g�����W�V�������I���������ǂ���
//==========================================================================================
bool cTransition::IsEnd(void)
{
	if (m_eTransDirection == TransDirection::TRANS_IN)
	{
		if (m_fBorderParam >= BORDER_MAX) return true;
		return false;
	}
	if (m_eTransDirection == TransDirection::TRANS_OUT)
	{
		if (m_fBorderParam <= 0) return true;
		return false;
	}
	return false;
}
