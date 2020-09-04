/*==============================================================================*/
/*																				*/
/*	@file title	:	cControllerManager.cpp										*/
/*  @brief		:	���͊Ǘ��N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "cControllerManager.h"
#include "Keyboard\cKeyboard.h"
#include "Mouse\cMouse.h"
#include "JoyPad\cJoyPad.h"
#include "XController/cXController.h"

//==========================================================================================
// ������
//==========================================================================================
void cControllerManager::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE::ACTIVE;
	m_sObjectName = "ControllerManager";

	// �L�[�{�[�h�N���X
	AddChild(&cKeyboard::GetInstance());

	// �}�E�X�N���X
	AddChild(&cMouse::GetInstance());

	// �W���C�p�b�h�N���X
	AddChild(&cJoyPad::GetInstance());

	//�@X�R���g���[���[�N���X
	AddChild(&cXController::GetInstance());

	IBaseObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cControllerManager::Update(void)
{
	IBaseObject::Update();
}
//==========================================================================================
// �L�[�����`�F�b�N(1P+�L�[�{�[�h�p)
// 
//	KEY_DEFINE	kcode	�`�F�b�N����L�[�R�[�h
//   MOUSE_INPUT_LEFT   : ���{�^��
//   MOUSE_INPUT_RIGHT  : �E�{�^��
// 
// �߂�l	true:������Ă����@FALSE:������Ă��Ȃ�
//==========================================================================================
bool cControllerManager::CheckButton(KEY_DEFINE kcode)
{
	// �{�^����������Ă��邩�ǂ���
	bool ret = false;
	switch (kcode)
	{
	case KEY_DEFINE::KEY_LEFT:
		ret |= cKeyboard::GetInstance().CheckButton(KEY_INPUT_LEFT);
		ret |= cJoyPad::GetInstance().CheckButton(PAD_INPUT_LEFT);
		ret |= cXController::GetInstance().CheckButton(XINPUT_BUTTON_DPAD_LEFT);
		break;
	case KEY_DEFINE::KEY_UP:
		ret |= cKeyboard::GetInstance().CheckButton(KEY_INPUT_UP);
		ret |= cJoyPad::GetInstance().CheckButton(PAD_INPUT_UP);
		ret |= cXController::GetInstance().CheckButton(XINPUT_BUTTON_DPAD_UP);
		break;
	case KEY_DEFINE::KEY_RIGHT:
		ret |= cKeyboard::GetInstance().CheckButton(KEY_INPUT_RIGHT);
		ret |= cJoyPad::GetInstance().CheckButton(PAD_INPUT_RIGHT);
		ret |= cXController::GetInstance().CheckButton(XINPUT_BUTTON_DPAD_RIGHT);
		break;
	case KEY_DEFINE::KEY_DOWN:
		ret |= cKeyboard::GetInstance().CheckButton(KEY_INPUT_DOWN);
		ret |= cJoyPad::GetInstance().CheckButton(PAD_INPUT_DOWN);
		ret |= cXController::GetInstance().CheckButton(XINPUT_BUTTON_DPAD_DOWN);
		break;
	case KEY_DEFINE::KEY_1:
		ret |= cKeyboard::GetInstance().CheckButton(KEY_INPUT_Z);
		ret |= cJoyPad::GetInstance().CheckButton(PAD_INPUT_1);
		ret |= cXController::GetInstance().CheckButton(XINPUT_BUTTON_A);
		break;
	case KEY_DEFINE::KEY_2:
		ret |= cKeyboard::GetInstance().CheckButton(KEY_INPUT_X);
		ret |= cJoyPad::GetInstance().CheckButton(PAD_INPUT_2);
		ret |= cXController::GetInstance().CheckButton(XINPUT_BUTTON_B);
		break;
	case KEY_DEFINE::KEY_3:
		ret |= cKeyboard::GetInstance().CheckButton(KEY_INPUT_C);
		ret |= cJoyPad::GetInstance().CheckButton(PAD_INPUT_3);
		ret |= cXController::GetInstance().CheckButton(XINPUT_BUTTON_X);
		break;
	case KEY_DEFINE::KEY_4:
		ret |= cKeyboard::GetInstance().CheckButton(KEY_INPUT_V);
		ret |= cJoyPad::GetInstance().CheckButton(PAD_INPUT_4);
		ret |= cXController::GetInstance().CheckButton(XINPUT_BUTTON_Y);
		break;
	case KEY_DEFINE::KEY_PAUSE:
		ret |= cKeyboard::GetInstance().CheckButton(KEY_INPUT_P);
		ret |= cKeyboard::GetInstance().CheckButton(KEY_INPUT_SPACE);
		ret |= cJoyPad::GetInstance().CheckButton(PAD_INPUT_5);
		ret |= cXController::GetInstance().CheckButton(XINPUT_BUTTON_START);
		break;
	case KEY_DEFINE::KEY_ANY:
		for (int i = 0; i < (int)KEY_DEFINE::KEY_MAX; i++)
		{
			ret |= CheckButton((KEY_DEFINE)i);
		}
		break;
	}

	return ret;
}

//==========================================================================================
// �������u�Ԃ��`�F�b�N(1P+�L�[�{�[�h�p)
// 
//	KEY_DEFINE	kcode	�`�F�b�N����L�[�R�[�h�@
// 
// �߂�l	true:������Ă����@FALSE:������Ă��Ȃ�
//==========================================================================================
bool cControllerManager::CheckTrigger(KEY_DEFINE kcode)
{
	bool ret = false;
	switch (kcode)
	{
	case KEY_DEFINE::KEY_LEFT:
		ret |= cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_LEFT);
		ret |= cJoyPad::GetInstance().CheckTrigger(PAD_INPUT_LEFT);
		ret |= cXController::GetInstance().CheckTrigger(XINPUT_BUTTON_DPAD_LEFT);
		break;
	case KEY_DEFINE::KEY_UP:
		ret |= cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_UP);
		ret |= cJoyPad::GetInstance().CheckTrigger(PAD_INPUT_UP);
		ret |= cXController::GetInstance().CheckTrigger(XINPUT_BUTTON_DPAD_UP);
		break;
	case KEY_DEFINE::KEY_RIGHT:
		ret |= cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_RIGHT);
		ret |= cJoyPad::GetInstance().CheckTrigger(PAD_INPUT_RIGHT);
		ret |= cXController::GetInstance().CheckTrigger(XINPUT_BUTTON_DPAD_RIGHT);
		break;
	case KEY_DEFINE::KEY_DOWN:
		ret |= cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_DOWN);
		ret |= cJoyPad::GetInstance().CheckTrigger(PAD_INPUT_DOWN);
		ret |= cXController::GetInstance().CheckTrigger(XINPUT_BUTTON_DPAD_DOWN);
		break;
	case KEY_DEFINE::KEY_1:
		ret |= cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_Z);
		ret |= cJoyPad::GetInstance().CheckTrigger(PAD_INPUT_1);
		ret |= cXController::GetInstance().CheckTrigger(XINPUT_BUTTON_A);
		break;
	case KEY_DEFINE::KEY_2:
		ret |= cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_X);
		ret |= cJoyPad::GetInstance().CheckTrigger(PAD_INPUT_2);
		ret |= cXController::GetInstance().CheckTrigger(XINPUT_BUTTON_B);
		break;
	case KEY_DEFINE::KEY_3:
		ret |= cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_C);
		ret |= cJoyPad::GetInstance().CheckTrigger(PAD_INPUT_3);
		ret |= cXController::GetInstance().CheckTrigger(XINPUT_BUTTON_X);
		break;
	case KEY_DEFINE::KEY_4:
		ret |= cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_V);
		ret |= cJoyPad::GetInstance().CheckTrigger(PAD_INPUT_4);
		ret |= cXController::GetInstance().CheckTrigger(XINPUT_BUTTON_Y);
		break;
	case KEY_DEFINE::KEY_PAUSE:
		ret |= cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_P);
		ret |= cKeyboard::GetInstance().CheckTrigger(KEY_INPUT_SPACE);
		ret |= cJoyPad::GetInstance().CheckTrigger(PAD_INPUT_5);
		ret |= cXController::GetInstance().CheckTrigger(XINPUT_BUTTON_START);
		break;
	case KEY_DEFINE::KEY_ANY:
		for (int i = 0; i < (int)KEY_DEFINE::KEY_MAX; i++)
		{
			ret |= CheckTrigger((KEY_DEFINE)i);
		}
		break;
	}

	return ret;
}

//==========================================================================================
// �������u�Ԃ��`�F�b�N(1P+�L�[�{�[�h�p)
// 
//	KEY_DEFINE	kcode	�`�F�b�N����L�[�R�[�h�@
// 
// �߂�l	true:������Ă����@FALSE:������Ă��Ȃ�
//==========================================================================================
bool cControllerManager::CheckRelease(KEY_DEFINE kcode)
{
	bool ret = false;
	switch (kcode)
	{
	case KEY_DEFINE::KEY_LEFT:
		ret |= cKeyboard::GetInstance().CheckRelease(KEY_INPUT_LEFT);
		ret |= cJoyPad::GetInstance().CheckRelease(PAD_INPUT_LEFT);
		ret |= cXController::GetInstance().CheckRelease(XINPUT_BUTTON_DPAD_LEFT);
		break;
	case KEY_DEFINE::KEY_UP:
		ret |= cKeyboard::GetInstance().CheckRelease(KEY_INPUT_UP);
		ret |= cJoyPad::GetInstance().CheckRelease(PAD_INPUT_UP);
		ret |= cXController::GetInstance().CheckRelease(XINPUT_BUTTON_DPAD_UP);
		break;
	case KEY_DEFINE::KEY_RIGHT:
		ret |= cKeyboard::GetInstance().CheckRelease(KEY_INPUT_RIGHT);
		ret |= cJoyPad::GetInstance().CheckRelease(PAD_INPUT_RIGHT);
		ret |= cXController::GetInstance().CheckRelease(XINPUT_BUTTON_DPAD_RIGHT);
		break;
	case KEY_DEFINE::KEY_DOWN:
		ret |= cKeyboard::GetInstance().CheckRelease(KEY_INPUT_DOWN);
		ret |= cJoyPad::GetInstance().CheckRelease(PAD_INPUT_DOWN);
		ret |= cXController::GetInstance().CheckRelease(XINPUT_BUTTON_DPAD_DOWN);
		break;
	case KEY_DEFINE::KEY_1:
		ret |= cKeyboard::GetInstance().CheckRelease(KEY_INPUT_Z);
		ret |= cJoyPad::GetInstance().CheckRelease(PAD_INPUT_1);
		ret |= cXController::GetInstance().CheckRelease(XINPUT_BUTTON_A);
		break;
	case KEY_DEFINE::KEY_2:
		ret |= cKeyboard::GetInstance().CheckRelease(KEY_INPUT_X);
		ret |= cJoyPad::GetInstance().CheckRelease(PAD_INPUT_2);
		ret |= cXController::GetInstance().CheckRelease(XINPUT_BUTTON_B);
		break;
	case KEY_DEFINE::KEY_3:
		ret |= cKeyboard::GetInstance().CheckRelease(KEY_INPUT_C);
		ret |= cJoyPad::GetInstance().CheckRelease(PAD_INPUT_3);
		ret |= cXController::GetInstance().CheckRelease(XINPUT_BUTTON_X);
		break;
	case KEY_DEFINE::KEY_4:
		ret |= cKeyboard::GetInstance().CheckRelease(KEY_INPUT_V);
		ret |= cJoyPad::GetInstance().CheckRelease(PAD_INPUT_4);
		ret |= cXController::GetInstance().CheckRelease(XINPUT_BUTTON_Y);
		break;
	case KEY_DEFINE::KEY_PAUSE:
		ret |= cKeyboard::GetInstance().CheckRelease(KEY_INPUT_P);
		ret |= cKeyboard::GetInstance().CheckRelease(KEY_INPUT_SPACE);
		ret |= cJoyPad::GetInstance().CheckRelease(PAD_INPUT_5);
		ret |= cXController::GetInstance().CheckRelease(XINPUT_BUTTON_START);
		break;
	case KEY_DEFINE::KEY_ANY:
		for (int i = 0; i < (int)KEY_DEFINE::KEY_MAX; i++)
		{
			ret |= CheckRelease((KEY_DEFINE)i);
		}
		break;
	}

	return ret;
}

//==========================================================================================
// �U���̊J�n
// InputType : �p�b�h���ʎq DX_INPUT_PAD1�`4
// Power : 0 �` 1000
// Time : �U������
//==========================================================================================
void cControllerManager::StartVibration(int InputType, int Power, int Time)
{
	StartJoypadVibration(InputType, Power, Time);
}

//==========================================================================================
// �U���̊J�n
// InputType : �p�b�h���ʎq DX_INPUT_PAD1�`4
//==========================================================================================
void cControllerManager::StopVibration(int InputType)
{
	StopJoypadVibration(InputType);
}