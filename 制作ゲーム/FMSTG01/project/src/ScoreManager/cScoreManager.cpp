/*==============================================================================*/
/*																				*/
/*	@file title	:	cScoreManager.cpp											*/
/*  @brief		:	�X�R�A�Ǘ��N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/01/13													*/
/*																				*/
/*==============================================================================*/

#include "cScoreManager.h"

//==========================================================================================
// ������
//==========================================================================================
void cScoreManager::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "ScoreManager";

	m_nCurrentScore = 0;
	m_nHiScore = 0;
	m_nTimeBonus = 0;

	IBaseObject::Initialize();
}

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject * cScoreManager::Finalize(void)
{
	IBaseObject::Finalize();
	return nullptr;
}