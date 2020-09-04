/*==============================================================================*/
/*																				*/
/*	@file title	:	cControllerManager.cpp										*/
/*  @brief		:	入力管理クラス												*/
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
// 初期化
//==========================================================================================
void cControllerManager::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE::ACTIVE;
	m_sObjectName = "ControllerManager";

	// キーボードクラス
	AddChild(&cKeyboard::GetInstance());

	// マウスクラス
	AddChild(&cMouse::GetInstance());

	// ジョイパッドクラス
	AddChild(&cJoyPad::GetInstance());

	//　Xコントローラークラス
	AddChild(&cXController::GetInstance());

	IBaseObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cControllerManager::Update(void)
{
	IBaseObject::Update();
}
//==========================================================================================
// キー押下チェック(1P+キーボード用)
// 
//	KEY_DEFINE	kcode	チェックするキーコード
//   MOUSE_INPUT_LEFT   : 左ボタン
//   MOUSE_INPUT_RIGHT  : 右ボタン
// 
// 戻り値	true:押されていた　FALSE:押されていない
//==========================================================================================
bool cControllerManager::CheckButton(KEY_DEFINE kcode)
{
	// ボタンが押されているかどうか
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
// 押した瞬間をチェック(1P+キーボード用)
// 
//	KEY_DEFINE	kcode	チェックするキーコード　
// 
// 戻り値	true:押されていた　FALSE:押されていない
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
// 離した瞬間をチェック(1P+キーボード用)
// 
//	KEY_DEFINE	kcode	チェックするキーコード　
// 
// 戻り値	true:押されていた　FALSE:押されていない
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
// 振動の開始
// InputType : パッド識別子 DX_INPUT_PAD1～4
// Power : 0 ～ 1000
// Time : 振動時間
//==========================================================================================
void cControllerManager::StartVibration(int InputType, int Power, int Time)
{
	StartJoypadVibration(InputType, Power, Time);
}

//==========================================================================================
// 振動の開始
// InputType : パッド識別子 DX_INPUT_PAD1～4
//==========================================================================================
void cControllerManager::StopVibration(int InputType)
{
	StopJoypadVibration(InputType);
}