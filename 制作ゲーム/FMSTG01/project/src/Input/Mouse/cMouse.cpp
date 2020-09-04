/*==============================================================================*/
/*																				*/
/*	@file title	:	cMouse.cpp													*/
/*  @brief		:	�}�E�X���̓N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/24													*/
/*																				*/
/*==============================================================================*/

#include "cMouse.h"

//==========================================================================================
// ������
//==========================================================================================
void cMouse::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "Mouse";

	m_nButtonState = 0;
	m_nPrevButtonState = 0;

	IBaseObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cMouse::Update(void)
{
	// �O�t���[�����̕ۑ�
	memcpy(&m_nPrevButtonState, &m_nButtonState, sizeof(int));

	// �}�E�X���͏�Ԃ̎擾
	m_nButtonState = GetMouseInput();

	IBaseObject::Update();
}
//==========================================================================================
// �j��
//==========================================================================================
IBaseObject * cMouse::Finalize(void)
{
	IBaseObject::Finalize();
	return nullptr;
}
//==========================================================================================
// �L�[�����`�F�b�N
// 
//	unsigned int	kcode	�`�F�b�N����L�[�R�[�h
//   MOUSE_INPUT_LEFT   : ���{�^��
//   MOUSE_INPUT_RIGHT  : �E�{�^��
//   MOUSE_INPUT_MIDDLE : �}�E�X�����{�^��
// 
// �߂�l	true:������Ă����@FALSE:������Ă��Ȃ�
//==========================================================================================
bool cMouse::CheckButton(unsigned int kcode)
{
	// �{�^����������Ă��邩�ǂ���
	if (m_nButtonState & kcode) return true;

	return false;
}

//==========================================================================================
// �������u�Ԃ��`�F�b�N
// 
//	unsigned int	kcode	�`�F�b�N����L�[�R�[�h�@
// 
// �߂�l	true:������Ă����@FALSE:������Ă��Ȃ�
//==========================================================================================
bool cMouse::CheckTriger(unsigned int kcode)
{
	if (!(m_nPrevButtonState & kcode) && (m_nButtonState & kcode)) return true;

	return false;
}

//==========================================================================================
// �������u�Ԃ��`�F�b�N
// 
//	unsigned int	kcode	�`�F�b�N����L�[�R�[�h�@
// 
// �߂�l	true:������Ă����@FALSE:������Ă��Ȃ�
//==========================================================================================
bool cMouse::CheckRelease(unsigned int kcode)
{
	if ((m_nPrevButtonState & kcode) && !(m_nButtonState & kcode)) return true;

	return false;
}

//==========================================================================================
// �}�E�X���W�̐ݒ�
//==========================================================================================
void cMouse::SetPoint(int x, int y)
{
	SetMousePoint(x,y);
}
void cMouse::SetPoint(POINT pt)
{
	SetPoint(pt.x,pt.y);
}

//==========================================================================================
// �}�E�X���W�̎擾
//==========================================================================================
POINT cMouse::GetPoint(void)
{
	int x = 0 , y = 0;
	POINT pt;
	GetMousePoint(&x,&y);
	pt.x = x;
	pt.y = y;

	return pt;
}
