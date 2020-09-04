/*==============================================================================*/
/*																				*/
/*	@file title	:	cSpEffectManager.cpp										*/
/*  @brief		:	�X�v���C�g�G�t�F�N�g�Ǘ��N���X								*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/24													*/
/*																				*/
/*==============================================================================*/

#include "cSpEffectManager.h"
#include "TargetEffect\cTargetEffect.h"
#include "ScreenFlash\cScreenFlash.h"
#include "Warning\cWarning.h"

//==========================================================================================
// ������
//==========================================================================================
void cSpEffectManager::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "EffectManager";

	IBaseObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cSpEffectManager::Update(void)
{
	IBaseObject::Update();
}

//==========================================================================================
// �j��
//==========================================================================================
IBaseObject * cSpEffectManager::Finalize(void)
{
	IBaseObject::Finalize();
	return nullptr;
}

//==========================================================================================
// ����
//==========================================================================================
cSpEffectObject* cSpEffectManager::Create(SpEffectID id, cVector2 pos)
{
	cSpEffectObject* obj = nullptr;
	switch (id)
	{
	case SPEFFECT_TARGET: obj = CreateObject<cTargetEffect>(this); break;
	case SPEFFECT_SCREENFLASH: obj = CreateObject<cScreenFlash>(this); break;
	case SPEFFECT_WARNING: obj = CreateObject<cWarning>(this); break;
	}

	if (obj != nullptr)
	{
		obj->Initialize();
		obj->SetPos(pos);
	}
	return obj;
}
