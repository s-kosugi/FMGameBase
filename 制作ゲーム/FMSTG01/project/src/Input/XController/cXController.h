#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cXController.h												*/
/*  @brief		:	XBox�R���g���[���[���̓N���X								*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/03/22													*/
/*																				*/
/*==============================================================================*/

#include "..\..\BaseObject\IBaseSingleton.h"
#include <DxLib.h>

class cXController : public IBaseSingleton<cXController>
{
public:
	// ������
	void Initialize(void);

	// �X�V
	void Update(void);

	// �j��
	IBaseObject* Finalize(void);

	// �{�^�������`�F�b�N
	bool CheckButton(unsigned int kcode, int InputType = DX_INPUT_PAD1); // �����Ă��邩
	bool CheckTriger(unsigned int kcode, int InputType = DX_INPUT_PAD1); // �������u��
	bool CheckRelease(unsigned int kcode, int InputType = DX_INPUT_PAD1); // �������u��

	// �A�i���O���͎擾
	POINT  GetAnalogInput(int InputType);

	// �ڑ��䐔�擾
	inline int  GetConnectNum(void) { return m_nJoyPadNum; };


	// XInput Joypad state
	XINPUT_STATE* m_xiInputState;
	// �O�t���[�����
	XINPUT_STATE* m_xiPrevInputState;

	// X�R���g���[���[�ڑ���
	short m_nJoyPadNum;

};