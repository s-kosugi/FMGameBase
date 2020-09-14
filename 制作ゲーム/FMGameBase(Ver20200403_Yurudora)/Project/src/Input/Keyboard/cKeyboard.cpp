/*==============================================================================*/
/*																				*/
/*	@file title	:	cKeyboard.cpp												*/
/*  @brief		:	�L�[�{�[�h���̓N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/24													*/
/*																				*/
/*==============================================================================*/

#include "cKeyboard.h"
#include <DxLib.h>

//==========================================================================================
// ������
//==========================================================================================
void cKeyboard::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE::ACTIVE;
	m_sObjectName = "Keyboard";

	IBaseObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cKeyboard::Update(void)
{
	// �O�t���[�����̕ۑ�
	memcpy(m_diPrevKeyState,m_diKeyState, KEY_STATE_NUM);

	// �L�[��Ԃ̎擾
	GetHitKeyStateAll(m_diKeyState);

	IBaseObject::Update();
}

//==========================================================================================
// �L�[�����`�F�b�N
// 
//	unsigned int	kcode	�`�F�b�N����L�[�R�[�h�@
//   KEY_INPUT_A : �L�[�{�[�hA�L�[
//   KEY_INPUT_B : �L�[�{�[�hB�L�[
//   �c
// 
// �߂�l	true:������Ă����@false:������Ă��Ȃ�
//==========================================================================================
bool cKeyboard::CheckButton(unsigned int kcode)
{
	// �L�[��������Ă��邩�ǂ���
	if(m_diKeyState[kcode] == 1) return true;

	return false;
}

//==========================================================================================
// �������u�Ԃ��`�F�b�N
// 
//	unsigned int	kcode	�`�F�b�N����L�[�R�[�h�@
//   KEY_INPUT_A : �L�[�{�[�hA�L�[
//   KEY_INPUT_B : �L�[�{�[�hB�L�[
//   �c
// 
// �߂�l	true:�������u��
//==========================================================================================
bool cKeyboard::CheckTrigger(unsigned int kcode)
{
	if (m_diPrevKeyState[kcode] == 0 && m_diKeyState[kcode] == 1) return true;

	return false;
}

//==========================================================================================
// �������u�Ԃ��`�F�b�N
// 
//	unsigned int	kcode	�`�F�b�N����L�[�R�[�h�@
//   KEY_INPUT_A : �L�[�{�[�hA�L�[
//   KEY_INPUT_B : �L�[�{�[�hB�L�[�@
//   �c
// 
// �߂�l	true:�������u��
//==========================================================================================
bool cKeyboard::CheckRelease(unsigned int kcode)
{
	if (m_diPrevKeyState[kcode] == 1 && m_diKeyState[kcode] == 0) return true;

	return false;
}

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cKeyboard::cKeyboard(void):
	m_diKeyState(""),
	m_diPrevKeyState("")
{
	memset(m_diKeyState, 0, KEY_STATE_NUM);
	memset(m_diPrevKeyState, 0, KEY_STATE_NUM);
}

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cKeyboard::cKeyboard(IBaseObject* parent):
	cKeyboard::cKeyboard()
{
}

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cKeyboard::cKeyboard(IBaseObject* parent, const std::string& name):
	cKeyboard::cKeyboard(parent)
{
}

//==========================================================================================
// �R�s�[�R���X�g���N�^
//==========================================================================================
cKeyboard::cKeyboard(const cKeyboard& t):
	cKeyboard::cKeyboard()
{
}
