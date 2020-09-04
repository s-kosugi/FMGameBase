/*==============================================================================*/
/*																				*/
/*	@file title	:	cJoyPad.cpp													*/
/*  @brief		:	�R���g���[���[���̓N���X									*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/24													*/
/*																				*/
/*==============================================================================*/

#include "cJoyPad.h"
#include "../../Utility/memory.h"

//==========================================================================================
// ������
//==========================================================================================
void cJoyPad::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "JoyPad";

	// �R���g���[���[�ڑ������擾
	m_nJoyPadNum = GetJoypadNum();

	// �ڑ�����Ă���R���g���[���[���������L�[�����쐬����
	m_diInputState = NEW int[m_nJoyPadNum];
	m_diPrevInputState = NEW int[m_nJoyPadNum];

	memset(m_diInputState, 0, m_nJoyPadNum * sizeof(int));
	memset(m_diPrevInputState, 0, m_nJoyPadNum * sizeof(int));


	IBaseObject::Initialize();
}
//==========================================================================================
// �X�V
//==========================================================================================
void cJoyPad::Update(void)
{
	for (int i = 1; i <= m_nJoyPadNum;i++)
	{
		// ���͏�Ԃ��擾����
		memcpy(&m_diPrevInputState[i-1], &m_diInputState[i-1],sizeof(int));
		m_diInputState[i-1] = GetJoypadInputState(i);
	}
	IBaseObject::Update();
}
//==========================================================================================
// �j��
//==========================================================================================
IBaseObject * cJoyPad::Finalize(void)
{
	SAFE_DELETE_ARRAY(m_diInputState);
	SAFE_DELETE_ARRAY(m_diPrevInputState);

	IBaseObject::Finalize();
	return nullptr;
}
//==========================================================================================
// �{�^�������`�F�b�N
// 
//	unsigned int	kcode	�`�F�b�N����{�^���@
//   PAD_INPUT_1 : �{�^��1
//   PAD_INPUT_DOWN : ���L�[
//   �c
//  int				InputType �p�b�h���ʎq
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
//   �c
// 
// �߂�l	true:������Ă����@false:������Ă��Ȃ�
//==========================================================================================
bool cJoyPad::CheckButton(unsigned int kcode, int InputType)
{
	if( InputType > m_nJoyPadNum) return false;

	// �{�^����������Ă��邩�ǂ���
	if (m_diInputState[InputType-1] & kcode)
		return true;

	return false;
}
//==========================================================================================
// �������u�Ԃ��`�F�b�N
// 
//	unsigned int	kcode	�`�F�b�N����{�^���@
//   PAD_INPUT_1 : �{�^��1
//   PAD_INPUT_DOWN : ���L�[
//   �c
//  int				InputType �p�b�h���ʎq
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
//   �c
// 
// �߂�l	true:������Ă���
//==========================================================================================
bool cJoyPad::CheckTriger(unsigned int kcode, int InputType)
{
	if (InputType > m_nJoyPadNum) return false;

	// �{�^���������ꂽ�u��
	if ( !(m_diPrevInputState[InputType-1] & kcode) && (m_diInputState[InputType-1] & kcode)) return true;

	return false;
}
//==========================================================================================
// �������u�Ԃ��`�F�b�N
// 
//	unsigned int	kcode	�`�F�b�N����{�^���@
//   PAD_INPUT_1 : �{�^��1
//   PAD_INPUT_DOWN : ���L�[
//   �c
//  int				InputType �p�b�h���ʎq
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
//    DX_INPUT_PAD1�@�@�@�@: �p�b�h�Q
//   �c
// 
// �߂�l	true:�����ꂽ�u��
//==========================================================================================
bool cJoyPad::CheckRelease(unsigned int kcode, int InputType)
{
	if (InputType > m_nJoyPadNum) return false;

	// �{�^���������ꂽ�u��
	if ((m_diPrevInputState[InputType-1] & kcode) && !(m_diInputState[InputType-1] & kcode)) return true;

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
POINT cJoyPad::GetAnalogInput(int InputType)
{
	POINT pt;
	int x = 0,y = 0;
	pt.y = pt.x = 0;

	if (InputType > m_nJoyPadNum) return pt;

	GetJoypadAnalogInput(&x,&y,InputType);
	pt.x = x;
	pt.y = y;

	return pt;
}
