#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cUIManager.h												*/
/*  @brief		:	UI�Ǘ��N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/27													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseSingleton.h"
#include "UIID.h"
#include "cUIObject.h"

class cUIManager : public IBaseSingleton<cUIManager>
{
public:

	// ������
	void Initialize(void);

	// �X�V
	void Update(void);

	// �j��
	IBaseObject* Finalize(void);

	// ����
	cUIObject* Create(UIID id, cVector2 pos);

private:
};