#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cJoyPad.h													*/
/*  @brief		:	�R���g���[���[���̓N���X									*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/24													*/
/*																				*/
/*==============================================================================*/

#include "..\..\BaseObject\IBaseSingleton.h"
#include <DxLib.h>

class cJoyPad : public IBaseSingleton<cJoyPad>
{
public:
	// ������
	void Initialize(void);

	// �X�V
	void Update(void);

	// �j��
	IBaseObject* Finalize(void);

	// �{�^�������`�F�b�N
	bool CheckButton(unsigned int kcode,int InputType = DX_INPUT_PAD1); // �����Ă��邩
	bool CheckTriger(unsigned int kcode, int InputType = DX_INPUT_PAD1); // �������u��
	bool CheckRelease(unsigned int kcode, int InputType = DX_INPUT_PAD1); // �������u��

	// �A�i���O���͎擾
	POINT  GetAnalogInput(int InputType);

	// �ڑ��䐔�擾
	inline int  GetConnectNum(void) { return m_nJoyPadNum; };


	// DirectInput Joypad state
	int* m_diInputState;
	// �O�t���[�����
	int* m_diPrevInputState;

	// �W���C�p�b�h�ڑ���
	short m_nJoyPadNum;

};