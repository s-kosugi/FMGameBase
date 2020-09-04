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
// 定数
const int cXController::LIMIT_CANT_ANALOG = 30000;
const int cXController::LIMIT_CANT_TRIGGER = 200;

//==========================================================================================
// 初期化
//==========================================================================================
void cXController::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE::ACTIVE;
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
bool cXController::CheckTrigger(unsigned int kcode, int InputType)
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
// 振動の開始
// Power : 0 ～ 1000
// Time : 振動時間
// InputType : パッド識別子 DX_INPUT_PAD1～4
//==========================================================================================
void cXController::StartVibration(int Power, int Time , int InputType )
{
	StartJoypadVibration(InputType, Power, Time);
}

//==========================================================================================
// 振動の停止
// InputType : パッド識別子 DX_INPUT_PAD1～4
//==========================================================================================
void cXController::StopVibration(int InputType)
{
	StopJoypadVibration(InputType);
}

//==========================================================================================
// 左スティックの取得
// 
//  int				InputType パッド識別子
//    DX_INPUT_PAD1　　　　: パッド１
//    DX_INPUT_PAD1　　　　: パッド２
//   …
// 戻り値 POINT -32768 ～ 32767までの値
//
//==========================================================================================
POINT cXController::GetLeftAnalogInput(int InputType)
{
	POINT pt;
	pt.x = pt.y = 0;
	if (InputType > m_nJoyPadNum) return pt;

	pt.x = m_xiInputState[InputType - 1].ThumbLX;
	pt.y = m_xiInputState[InputType - 1].ThumbLY;
	return pt;
}

//==========================================================================================
// 右スティックの取得
// 
//  int				InputType パッド識別子
//    DX_INPUT_PAD1　　　　: パッド１
//    DX_INPUT_PAD1　　　　: パッド２
//   …
// 戻り値 POINT -32768 ～ 32767までの値
//
//==========================================================================================
POINT cXController::GetRightAnalogInput(int InputType)
{
	POINT pt;
	pt.x = pt.y = 0;
	if (InputType > m_nJoyPadNum) return pt;

	pt.x = m_xiInputState[InputType - 1].ThumbRX;
	pt.y = m_xiInputState[InputType - 1].ThumbRY;
	return pt;
}

//==========================================================================================
// 左アナログスティックのトリガー判定
//  STICK_DIRECTION direction 方向ID
//  int				InputType パッド識別子
//    DX_INPUT_PAD1　　　　: パッド１
//    DX_INPUT_PAD1　　　　: パッド２
//   …
//  戻り値 : true 倒された瞬間
//==========================================================================================
bool cXController::IsTriggerLeftAnalog(STICK_DIRECTION direction , int InputType )
{
	if (InputType > m_nJoyPadNum) return false;
	switch (direction)
	{
	case STICK_DIRECTION::LEFT:
		return (m_xiInputState[InputType-1].ThumbLX < LIMIT_CANT_ANALOG && m_xiPrevInputState[InputType-1].ThumbLX > LIMIT_CANT_ANALOG);
	case STICK_DIRECTION::RIGHT:
		return (m_xiInputState[InputType-1].ThumbLX > LIMIT_CANT_ANALOG && m_xiPrevInputState[InputType-1].ThumbLX < LIMIT_CANT_ANALOG);
	case STICK_DIRECTION::UP:
		return (m_xiInputState[InputType-1].ThumbLY < LIMIT_CANT_ANALOG && m_xiPrevInputState[InputType-1].ThumbLY > LIMIT_CANT_ANALOG);
	case STICK_DIRECTION::DOWN:
		return (m_xiInputState[InputType-1].ThumbLY > LIMIT_CANT_ANALOG && m_xiPrevInputState[InputType-1].ThumbLY < LIMIT_CANT_ANALOG);
	}
	return false;
}

//==========================================================================================
// 右アナログスティックのトリガー判定
//  STICK_DIRECTION	direction 方向ID
//  int				InputType パッド識別子
//    DX_INPUT_PAD1　　　　: パッド１
//    DX_INPUT_PAD1　　　　: パッド２
//   …
//  戻り値 : true 倒された瞬間
//==========================================================================================
bool cXController::IsTriggerRightAnalog( STICK_DIRECTION direction, int InputType )
{
	if (InputType > m_nJoyPadNum) return false;

	switch (direction)
	{
	case STICK_DIRECTION::LEFT:
		return (m_xiInputState[InputType-1].ThumbRX < LIMIT_CANT_ANALOG && m_xiPrevInputState[InputType-1].ThumbRX > LIMIT_CANT_ANALOG);
	case STICK_DIRECTION::RIGHT:
		return (m_xiInputState[InputType-1].ThumbRX > LIMIT_CANT_ANALOG && m_xiPrevInputState[InputType-1].ThumbRX < LIMIT_CANT_ANALOG);
	case STICK_DIRECTION::UP:
		return (m_xiInputState[InputType-1].ThumbRY < LIMIT_CANT_ANALOG && m_xiPrevInputState[InputType-1].ThumbRY > LIMIT_CANT_ANALOG);
	case STICK_DIRECTION::DOWN:
		return (m_xiInputState[InputType-1].ThumbRY > LIMIT_CANT_ANALOG && m_xiPrevInputState[InputType-1].ThumbRY < LIMIT_CANT_ANALOG);
	}
	return false;
}

//==========================================================================================
// 左トリガーの取得
// 
//  int				InputType パッド識別子
//    DX_INPUT_PAD1　　　　: パッド１
//    DX_INPUT_PAD1　　　　: パッド２
//   …
// 戻り値 unsigned char 0 ～ 255までの値
//
//==========================================================================================
unsigned char cXController::GetLeftTriggerInput(int InputType)
{
	if (InputType > m_nJoyPadNum) return 0;

	return m_xiInputState[InputType - 1].LeftTrigger;
}

//==========================================================================================
// 右トリガーの取得
// 
//  int				InputType パッド識別子
//    DX_INPUT_PAD1　　　　: パッド１
//    DX_INPUT_PAD1　　　　: パッド２
//   …
// 戻り値 unsigned char 0 ～ 255までの値
//
//==========================================================================================
unsigned char cXController::GetRightTriggerInput(int InputType)
{
	if (InputType > m_nJoyPadNum) return 0;

	return m_xiInputState[InputType - 1].RightTrigger;
}
//==========================================================================================
// 左トリガーのトリガー判定
// 
//  int				InputType パッド識別子
//    DX_INPUT_PAD1　　　　: パッド１
//    DX_INPUT_PAD1　　　　: パッド２
//   …
// 戻り値 bool true 押した瞬間
//
//==========================================================================================
bool cXController::IsTriggerLeftTrigger( int InputType )
{
	if (InputType > m_nJoyPadNum) return false;

	return ( m_xiInputState[InputType-1].LeftTrigger > LIMIT_CANT_TRIGGER && m_xiPrevInputState[InputType-1].LeftTrigger < LIMIT_CANT_TRIGGER );
}

//==========================================================================================
// 右トリガーのトリガー判定
// 
//  int				InputType パッド識別子
//    DX_INPUT_PAD1　　　　: パッド１
//    DX_INPUT_PAD1　　　　: パッド２
//   …
// 戻り値 bool true 押した瞬間
//
//==========================================================================================
bool cXController::IsTriggerRightTrigger( int InputType )
{
	if (InputType > m_nJoyPadNum) return false;

	return ( m_xiInputState[InputType-1].RightTrigger > LIMIT_CANT_TRIGGER && m_xiPrevInputState[InputType-1].RightTrigger < LIMIT_CANT_TRIGGER );
}
//==========================================================================================
// 左トリガーのボタン判定
// 
//  int				InputType パッド識別子
//    DX_INPUT_PAD1　　　　: パッド１
//    DX_INPUT_PAD1　　　　: パッド２
//   …
// 戻り値 bool true 押している間
//
//==========================================================================================
bool cXController::IsButtonLeftTrigger( int InputType )
{
	if (InputType > m_nJoyPadNum) return false;

	return ( m_xiInputState[InputType-1].LeftTrigger > LIMIT_CANT_TRIGGER );
}
//==========================================================================================
// 右トリガーのボタン判定
// 
//  int				InputType パッド識別子
//    DX_INPUT_PAD1　　　　: パッド１
//    DX_INPUT_PAD1　　　　: パッド２
//   …
// 戻り値 bool true 押している間
//
//==========================================================================================
bool cXController::IsButtonRightTrigger( int InputType )
{
	if (InputType > m_nJoyPadNum) return false;

	return ( m_xiInputState[InputType-1].RightTrigger > LIMIT_CANT_TRIGGER );
}
//==========================================================================================
// 左トリガーのリリース判定
// 
//  int				InputType パッド識別子
//    DX_INPUT_PAD1　　　　: パッド１
//    DX_INPUT_PAD1　　　　: パッド２
//   …
// 戻り値 bool true 離された瞬間
//
//==========================================================================================
bool cXController::IsReleaseLeftTrigger(int InputType)
{
	if (InputType > m_nJoyPadNum) return false;

	return (m_xiInputState[InputType - 1].LeftTrigger < LIMIT_CANT_TRIGGER && m_xiPrevInputState[InputType - 1].LeftTrigger > LIMIT_CANT_TRIGGER);
}
//==========================================================================================
// 右トリガーのリリース判定
// 
//  int				InputType パッド識別子
//    DX_INPUT_PAD1　　　　: パッド１
//    DX_INPUT_PAD1　　　　: パッド２
//   …
// 戻り値 bool true 離された瞬間
//
//==========================================================================================
bool cXController::IsReleaseRightTrigger(int InputType)
{
	if (InputType > m_nJoyPadNum) return false;

	return (m_xiInputState[InputType - 1].RightTrigger < LIMIT_CANT_TRIGGER && m_xiPrevInputState[InputType - 1].RightTrigger > LIMIT_CANT_TRIGGER);
}

//==========================================================================================
// コンストラクタ
//==========================================================================================
cXController::cXController(void):
	m_xiInputState(nullptr),
	m_xiPrevInputState(nullptr),
	m_nJoyPadNum(0)
{
}

//==========================================================================================
// コンストラクタ
//==========================================================================================
cXController::cXController(IBaseObject* parent):
	cXController::cXController()
{
}

//==========================================================================================
// コンストラクタ
//==========================================================================================
cXController::cXController(IBaseObject* parent, const std::string& name):
	cXController::cXController(parent)
{
}

//==========================================================================================
// コピーコンストラクタ
//==========================================================================================
cXController::cXController(const cXController& t):
	cXController::cXController()
{
}
