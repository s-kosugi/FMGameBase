/*==============================================================================*/
/*																				*/
/*	@file title	:	cXController.cpp											*/
/*  @brief		:	XBOX�R���g���[���[���̓N���X								*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/03/22													*/
/*																				*/
/*==============================================================================*/

#include "cXController.h"
#include "../../Utility/memory.h"

//==========================================================================================
// ������
//==========================================================================================
void cXController::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "XController";

	// �R���g���[���[�ڑ������擾
	m_nJoyPadNum = GetJoypadNum();

	// �ڑ�����Ă���R���g���[���[���������L�[�����쐬����
	m_xiInputState = NEW XINPUT_STATE[m_nJoyPadNum];
	m_xiPrevInputState = NEW XINPUT_STATE[m_nJoyPadNum];

	memset(m_xiInputState, 0, m_nJoyPadNum * sizeof(XINPUT_STATE));
	memset(m_xiPrevInputState, 0, m_nJoyPadNum * sizeof(XINPUT_STATE));


	IBaseObject::Initialize();
}
//==========================================================================================
// �X�V
//==========================================================================================
void cXController::Update(void)
{
	for (int i = 1; i <= m_nJoyPadNum;i++)
	{
		// ���͏�Ԃ��擾����
		memcpy(&m_xiPrevInputState[i - 1], &m_xiInputState[i - 1], sizeof(XINPUT_STATE));
		GetJoypadXInputState(i, &m_xiInputState[i - 1]);
	}
	IBaseObject::Update();
}
//==========================================================================================
// �j��
//==========================================================================================
IBaseObject * cXController::Finalize(void)
{
	SAFE_DELETE_ARRAY(m_xiInputState);
	SAFE_DELETE_ARRAY(m_xiPrevInputState);

	IBaseObject::Finalize();
	return nullptr;
}
//==========================================================================================
// �{�^�������`�F�b�N
// 
//	unsigned int	kcode	�`�F�b�N����{�^���@
//   XINPUT_BUTTON_A : A�{�^��
//   XINPUT_BUTTON_DPAD_UP : ��{�^��
//   �c
//  int				InputType �p�b�h���ʎq
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
//   �c
// 
// �߂�l	true:������Ă����@false:������Ă��Ȃ�
//==========================================================================================
bool cXController::CheckButton(unsigned int kcode, int InputType)
{
	if (InputType > m_nJoyPadNum) return false;

	// �{�^����������Ă��邩�ǂ���
	if (m_xiInputState[InputType - 1].Buttons[kcode])
		return true;

	return false;
}
//==========================================================================================
// �������u�Ԃ��`�F�b�N
// 
//	unsigned int	kcode	�`�F�b�N����{�^���@
//   XINPUT_BUTTON_A : A�{�^��
//   XINPUT_BUTTON_DPAD_UP : ��{�^��
//   �c
//  int				InputType �p�b�h���ʎq
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
//   �c
// 
// �߂�l	true:������Ă���
//==========================================================================================
bool cXController::CheckTriger(unsigned int kcode, int InputType)
{
	if (InputType > m_nJoyPadNum) return false;

	// �{�^���������ꂽ�u��
	if (!(m_xiPrevInputState[InputType - 1].Buttons[kcode]) && (m_xiInputState[InputType - 1].Buttons[kcode])) return true;

	return false;
}
//==========================================================================================
// �������u�Ԃ��`�F�b�N
// 
//	unsigned int	kcode	�`�F�b�N����{�^���@
//   XINPUT_BUTTON_A : A�{�^��
//   XINPUT_BUTTON_DPAD_UP : ��{�^��
//   �c
//  int				InputType �p�b�h���ʎq
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
//   �c
// 
// �߂�l	true:�����ꂽ�u��
//==========================================================================================
bool cXController::CheckRelease(unsigned int kcode, int InputType)
{
	if (InputType > m_nJoyPadNum) return false;

	// �{�^���������ꂽ�u��
	if ((m_xiPrevInputState[InputType - 1].Buttons[kcode]) && !(m_xiInputState[InputType - 1].Buttons[kcode])) return true;

	return false;
}

//==========================================================================================
// �A�i���O���͂̎擾
// 
//  int				InputType �p�b�h���ʎq
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
//   �c
// �߂�l POINT -1000�`1000�܂ł̒l
//
//==========================================================================================
POINT cXController::GetAnalogInput(int InputType)
{
	POINT pt;
	int x = 0, y = 0;
	pt.y = pt.x = 0;

	if (InputType > m_nJoyPadNum) return pt;

	GetJoypadAnalogInput(&x, &y, InputType);
	pt.x = x;
	pt.y = y;

	return pt;
}
