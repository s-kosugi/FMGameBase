#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSpEffectManager.h											*/
/*  @brief		:	�X�v���C�g�G�t�F�N�g�Ǘ��N���X								*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/24													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseSingleton.h"
#include "SpEffectID.h"
#include "cSpEffectObject.h"

class cSpEffectManager : public IBaseSingleton<cSpEffectManager>
{
public:

	// ������
	void Initialize(void);

	// �X�V
	void Update(void);

	// �j��
	IBaseObject* Finalize(void);

	// ����
	cSpEffectObject* Create(SpEffectID id, cVector2 pos);

private:
};