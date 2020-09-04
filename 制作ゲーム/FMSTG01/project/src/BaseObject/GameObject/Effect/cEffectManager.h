#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEffectManager.h											*/
/*  @brief		:	�G�t�F�N�g�Ǘ��N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/12													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseSingleton.h"
#include "EffectID.h"
#include "cEffectObject.h"

class cEffectManager : public IBaseSingleton<cEffectManager>
{
public:

	// ������
	void Initialize(void);

	// �X�V
	void Update(void);

	// �j��
	IBaseObject* Finalize(void);

	// ����
	cEffectObject* Create(EffectID id, cVector2 pos);

private:
};