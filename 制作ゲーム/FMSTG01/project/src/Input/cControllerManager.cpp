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
	m_eObjectState = OBJECT_STATE_ACTIVE;
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
// 破棄
//==========================================================================================
IBaseObject * cControllerManager::Finalize(void)
{
	IBaseObject::Finalize();
	return nullptr;
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
	case KEY_LEFT:
		ret |= cKeyboard::GetInstance().CheckButton(KEY_INPUT_LEFT);
		ret |= cJoyPad::GetInstance().CheckButton(PAD_INPUT_LEFT);
		ret |= cXController::GetInstance().CheckButton(XINPUT_BUTTON_DPAD_LEFT);
		break;
	case KEY_UP:
		ret |= cKeyboard::GetInstance().CheckButton(KEY_INPUT_UP);
		ret |= cJoyPad::GetInstance().CheckButton(PAD_INPUT_UP);
		ret |= cXController::GetInstance().CheckButton(XINPUT_BUTTON_DPAD_UP);
		break;
	case KEY_RIGHT:
		ret |= cKeyboard::GetInstance().CheckButton(KEY_INPUT_RIGHT);
		ret |= cJoyPad::GetInstance().CheckButton(PAD_INPUT_RIGHT);
		ret |= cXController::GetInstance().CheckButton(XINPUT_BUTTON_DPAD_RIGHT);
		break;
	case KEY_DOWN:
		ret |= cKeyboard::GetInstance().CheckButton(KEY_INPUT_DOWN);
		ret |= cJoyPad::GetInstance().CheckButton(PAD_INPUT_DOWN);
		ret |= cXController::GetInstance().CheckButton(XINPUT_BUTTON_DPAD_DOWN);
		break;
	case KEY_1:
		ret |= cKeyboard::GetInstance().CheckButton(KEY_INPUT_Z);
		ret |= cJoyPad::GetInstance().CheckButton(PAD_INPUT_1);
		ret |= cXController::GetInstance().CheckButton(XINPUT_BUTTON_A);
		break;
	case KEY_2:
		ret |= cKeyboard::GetInstance().CheckButton(KEY_INPUT_X);
		ret |= cJoyPad::GetInstance().CheckButton(PAD_INPUT_2);
		ret |= cXController::GetInstance().CheckButton(XINPUT_BUTTON_B);
		break;
	case KEY_3:
		ret |= cKeyboard::GetInstance().CheckButton(KEY_INPUT_C);
		ret |= cJoyPad::GetInstance().CheckButton(PAD_INPUT_3);
		ret |= cXController::GetInstance().CheckButton(XINPUT_BUTTON_X);
		break;
	case KEY_4:
		ret |= cKeyboard::GetInstance().CheckButton(KEY_INPUT_V);
		ret |= cJoyPad::GetInstance().CheckButton(PAD_INPUT_4);
		ret |= cXController::GetInstance().CheckButton(XINPUT_BUTTON_Y);
		break;
	case KEY_PAUSE:
		ret |= cKeyboard::GetInstance().CheckButton(KEY_INPUT_P);
		ret |= cKeyboard::GetInstance().CheckButton(KEY_INPUT_SPACE);
		ret |= cJoyPad::GetInstance().CheckButton(PAD_INPUT_5);
		ret |= cXController::GetInstance().CheckButton(XINPUT_BUTTON_START);
		break;
	case KEY_ANY:
		for (int i = 0; i < KEY_MAX; i++)
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
bool cControllerManager::CheckTriger(KEY_DEFINE kcode)
{
	bool ret = false;
	switch (kcode)
	{
	case KEY_LEFT:
		ret |= cKeyboard::GetInstance().CheckTriger(KEY_INPUT_LEFT);
		ret |= cJoyPad::GetInstance().CheckTriger(PAD_INPUT_LEFT);
		ret |= cXController::GetInstance().CheckTriger(XINPUT_BUTTON_DPAD_LEFT);
		break;
	case KEY_UP:
		ret |= cKeyboard::GetInstance().CheckTriger(KEY_INPUT_UP);
		ret |= cJoyPad::GetInstance().CheckTriger(PAD_INPUT_UP);
		ret |= cXController::GetInstance().CheckTriger(XINPUT_BUTTON_DPAD_UP);
		break;
	case KEY_RIGHT:
		ret |= cKeyboard::GetInstance().CheckTriger(KEY_INPUT_RIGHT);
		ret |= cJoyPad::GetInstance().CheckTriger(PAD_INPUT_RIGHT);
		ret |= cXController::GetInstance().CheckTriger(XINPUT_BUTTON_DPAD_RIGHT);
		break;
	case KEY_DOWN:
		ret |= cKeyboard::GetInstance().CheckTriger(KEY_INPUT_DOWN);
		ret |= cJoyPad::GetInstance().CheckTriger(PAD_INPUT_DOWN);
		ret |= cXController::GetInstance().CheckTriger(XINPUT_BUTTON_DPAD_DOWN);
		break;
	case KEY_1:
		ret |= cKeyboard::GetInstance().CheckTriger(KEY_INPUT_Z);
		ret |= cJoyPad::GetInstance().CheckTriger(PAD_INPUT_1);
		ret |= cXController::GetInstance().CheckTriger(XINPUT_BUTTON_A);
		break;
	case KEY_2:
		ret |= cKeyboard::GetInstance().CheckTriger(KEY_INPUT_X);
		ret |= cJoyPad::GetInstance().CheckTriger(PAD_INPUT_2);
		ret |= cXController::GetInstance().CheckTriger(XINPUT_BUTTON_B);
		break;
	case KEY_3:
		ret |= cKeyboard::GetInstance().CheckTriger(KEY_INPUT_C);
		ret |= cJoyPad::GetInstance().CheckTriger(PAD_INPUT_3);
		ret |= cXController::GetInstance().CheckTriger(XINPUT_BUTTON_X);
		break;
	case KEY_4:
		ret |= cKeyboard::GetInstance().CheckTriger(KEY_INPUT_V);
		ret |= cJoyPad::GetInstance().CheckTriger(PAD_INPUT_4);
		ret |= cXController::GetInstance().CheckTriger(XINPUT_BUTTON_Y);
		break;
	case KEY_PAUSE:
		ret |= cKeyboard::GetInstance().CheckTriger(KEY_INPUT_P);
		ret |= cKeyboard::GetInstance().CheckTriger(KEY_INPUT_SPACE);
		ret |= cJoyPad::GetInstance().CheckTriger(PAD_INPUT_5);
		ret |= cXController::GetInstance().CheckTriger(XINPUT_BUTTON_START);
		break;
	case KEY_ANY:
		for (int i = 0; i < KEY_MAX; i++)
		{
			ret |= CheckTriger((KEY_DEFINE)i);
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
	case KEY_LEFT:
		ret |= cKeyboard::GetInstance().CheckRelease(KEY_INPUT_LEFT);
		ret |= cJoyPad::GetInstance().CheckRelease(PAD_INPUT_LEFT);
		ret |= cXController::GetInstance().CheckRelease(XINPUT_BUTTON_DPAD_LEFT);
		break;
	case KEY_UP:
		ret |= cKeyboard::GetInstance().CheckRelease(KEY_INPUT_UP);
		ret |= cJoyPad::GetInstance().CheckRelease(PAD_INPUT_UP);
		ret |= cXController::GetInstance().CheckRelease(XINPUT_BUTTON_DPAD_UP);
		break;
	case KEY_RIGHT:
		ret |= cKeyboard::GetInstance().CheckRelease(KEY_INPUT_RIGHT);
		ret |= cJoyPad::GetInstance().CheckRelease(PAD_INPUT_RIGHT);
		ret |= cXController::GetInstance().CheckRelease(XINPUT_BUTTON_DPAD_RIGHT);
		break;
	case KEY_DOWN:
		ret |= cKeyboard::GetInstance().CheckRelease(KEY_INPUT_DOWN);
		ret |= cJoyPad::GetInstance().CheckRelease(PAD_INPUT_DOWN);
		ret |= cXController::GetInstance().CheckRelease(XINPUT_BUTTON_DPAD_DOWN);
		break;
	case KEY_1:
		ret |= cKeyboard::GetInstance().CheckRelease(KEY_INPUT_Z);
		ret |= cJoyPad::GetInstance().CheckRelease(PAD_INPUT_1);
		ret |= cXController::GetInstance().CheckRelease(XINPUT_BUTTON_A);
		break;
	case KEY_2:
		ret |= cKeyboard::GetInstance().CheckRelease(KEY_INPUT_X);
		ret |= cJoyPad::GetInstance().CheckRelease(PAD_INPUT_2);
		ret |= cXController::GetInstance().CheckRelease(XINPUT_BUTTON_B);
		break;
	case KEY_3:
		ret |= cKeyboard::GetInstance().CheckRelease(KEY_INPUT_C);
		ret |= cJoyPad::GetInstance().CheckRelease(PAD_INPUT_3);
		ret |= cXController::GetInstance().CheckRelease(XINPUT_BUTTON_X);
		break;
	case KEY_4:
		ret |= cKeyboard::GetInstance().CheckRelease(KEY_INPUT_V);
		ret |= cJoyPad::GetInstance().CheckRelease(PAD_INPUT_4);
		ret |= cXController::GetInstance().CheckRelease(XINPUT_BUTTON_Y);
		break;
	case KEY_PAUSE:
		ret |= cKeyboard::GetInstance().CheckRelease(KEY_INPUT_P);
		ret |= cKeyboard::GetInstance().CheckRelease(KEY_INPUT_SPACE);
		ret |= cJoyPad::GetInstance().CheckRelease(PAD_INPUT_5);
		ret |= cXController::GetInstance().CheckRelease(XINPUT_BUTTON_START);
		break;
	case KEY_ANY:
		for (int i = 0; i < KEY_MAX; i++)
		{
			ret |= CheckRelease((KEY_DEFINE)i);
		}
		break;
	}

	return ret;
}