/*==============================================================================*/
/*																				*/
/*	@file title	:	cBackGroundManager.cpp										*/
/*  @brief		:	�w�i�Ǘ��N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/10													*/
/*																				*/
/*==============================================================================*/

#include "cBackGroundManager.h"
#include "Star\cStar.h"
#include "..\..\..\cGame.h"

//==========================================================================================
// ������
//==========================================================================================
void cBackGroundManager::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "BackGroundManager";

	cGame& game = cGame::GetInstance();

	for (int i = 0; i < STAR_POP_NUM; i++)
	{
		cStar* obj = CreateObject<cStar>(this);
		// �����ʒu�������_���ɐݒ�
		obj->SetPos((float)game.Random(0,game.GetPlayAreaWidth()), (float)game.Random(0, game.GetPlayAreaHeight()) );
	}

	IBaseObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cBackGroundManager::Update(void)
{

	IBaseObject::Update();
}

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject * cBackGroundManager::Finalize(void)
{
	IBaseObject::Finalize();
	return nullptr;
}