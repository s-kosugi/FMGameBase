#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cKeyboard.h													*/
/*  @brief		:	�L�[�{�[�h���̓N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/24													*/
/*																				*/
/*==============================================================================*/

#include "..\..\BaseObject\IBaseSingleton.h"

class cKeyboard : public IBaseSingleton<cKeyboard>
{
public:
	// ������
	void Initialize(void);

	// �X�V
	void Update( void );

	// �j��
	IBaseObject* Finalize( void );

	// �L�[�����`�F�b�N
	bool CheckButton(unsigned int kcode); // �����Ă��邩
	bool CheckTriger(unsigned int kcode); // �������u��
	bool CheckRelease(unsigned int kcode); // �������u��

	// DirectInput keyboard state
	char m_diKeyState[256];
	// �O�t���[�����
	char m_diPrevKeyState[256];

	// �萔
	const int KEY_STATE_NUM = 256;
};