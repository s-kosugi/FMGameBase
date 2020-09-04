/*==============================================================================*/
/*																				*/
/*	@file title	:	cXController.cpp											*/
/*  @brief		:	XBOXコントローラー入力クラス								*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/03/22													*/
/*																				*/
/*==============================================================================*/

#include "cXController.h"
#include "../../Utility/memory.h"

//==========================================================================================
// 初期化
//==========================================================================================
void cXController::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "XController";

	// コントローラー接続数を取得
	m_nJoyPadNum = GetJoypadNum();

	// 接続されているコントローラー数分だけキー情報を作成する
	m_xiInputState = NEW XINPUT_STATE[m_nJoyPadNum];
	m_xiPrevInputState = NEW XINPUT_STATE[m_nJoyPadNum];

	memset(m_xiInputState, 0, m_nJoyPadNum * sizeof(XINPUT_STATE));
	memset(m_xiPrevInputState, 0, m_nJoyPadNum * sizeof(XINPUT_STATE));


	IBaseObject::Initialize();
}
//==========================================================================================
// 更新
//==========================================================================================
void cXController::Update(void)
{
	for (int i = 1; i <= m_nJoyPadNum;i++)
	{
		// 入力状態を取得する
		memcpy(&m_xiPrevInputState[i - 1], &m_xiInputState[i - 1], sizeof(XINPUT_STATE));
		GetJoypadXInputState(i, &m_xiInputState[i - 1]);
	}
	IBaseObject::Update();
}
//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject * cXController::Finalize(void)
{
	SAFE_DELETE_ARRAY(m_xiInputState);
	SAFE_DELETE_ARRAY(m_xiPrevInputState);

	IBaseObject::Finalize();
	return nullptr;
}
//==========================================================================================
// ボタン押下チェック
// 
//	unsigned int	kcode	チェックするボタン　
//   XINPUT_BUTTON_A : Aボタン
//   XINPUT_BUTTON_DPAD_UP : 上ボタン
//   …
//  int				InputType パッド識別子
//    DX_INPUT_PAD1　　　　: パッド１
//    DX_INPUT_PAD1　　　　: パッド２
//   …
// 
// 戻り値	true:押されていた　false:押されていない
//==========================================================================================
bool cXController::CheckButton(unsigned int kcode, int InputType)
{
	if (InputType > m_nJoyPadNum) return false;

	// ボタンが押されているかどうか
	if (m_xiInputState[InputType - 1].Buttons[kcode])
		return true;

	return false;
}
//==========================================================================================
// 押した瞬間をチェック
// 
//	unsigned int	kcode	チェックするボタン　
//   XINPUT_BUTTON_A : Aボタン
//   XINPUT_BUTTON_DPAD_UP : 上ボタン
//   …
//  int				InputType パッド識別子
//    DX_INPUT_PAD1　　　　: パッド１
//    DX_INPUT_PAD1　　　　: パッド２
//   …
// 
// 戻り値	true:押されていた
//==========================================================================================
bool cXController::CheckTriger(unsigned int kcode, int InputType)
{
	if (InputType > m_nJoyPadNum) return false;

	// ボタンが押された瞬間
	if (!(m_xiPrevInputState[InputType - 1].Buttons[kcode]) && (m_xiInputState[InputType - 1].Buttons[kcode])) return true;

	return false;
}
//==========================================================================================
// 離した瞬間をチェック
// 
//	unsigned int	kcode	チェックするボタン　
//   XINPUT_BUTTON_A : Aボタン
//   XINPUT_BUTTON_DPAD_UP : 上ボタン
//   …
//  int				InputType パッド識別子
//    DX_INPUT_PAD1　　　　: パッド１
//    DX_INPUT_PAD1　　　　: パッド２
//   …
// 
// 戻り値	true:離された瞬間
//==========================================================================================
bool cXController::CheckRelease(unsigned int kcode, int InputType)
{
	if (InputType > m_nJoyPadNum) return false;

	// ボタンが離された瞬間
	if ((m_xiPrevInputState[InputType - 1].Buttons[kcode]) && !(m_xiInputState[InputType - 1].Buttons[kcode])) return true;

	return false;
}

//==========================================================================================
// アナログ入力の取得
// 
//  int				InputType パッド識別子
//    DX_INPUT_PAD1　　　　: パッド１
//    DX_INPUT_PAD1　　　　: パッド２
//   …
// 戻り値 POINT -1000～1000までの値
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
