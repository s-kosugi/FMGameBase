#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBackGroundManager.h										*/
/*  @brief		:	�w�i�Ǘ��N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/10													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseSingleton.h"

class cBackGroundManager : public IBaseSingleton<cBackGroundManager>
{
public:
	// ������
	void Initialize(void);

	// �X�V
	void Update( void );

	// �j��
	IBaseObject* Finalize(void);

private:
	// �萔
	// ���̏o����
	const int STAR_POP_NUM = 100;

	// ���̐����Ԋu
	const int STAR_GENERATE_INTERVAL = 5;
};