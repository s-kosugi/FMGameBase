/*==============================================================================*/
/*																				*/
/*	@file title	:	cJoyPad.cpp													*/
/*  @brief		:	コントローラー入力クラス									*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/24													*/
/*																				*/
/*==============================================================================*/

#include "cJoyPad.h"
#include "../../Utility/memory.h"

//==========================================================================================
// 初期化
//==========================================================================================
void cJoyPad::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "JoyPad";

	// コントローラー接続数を取得
	m_nJoyPadNum = GetJoypadNum();

	// 接続されているコントローラー数分だけキー情報を作成する
	m_diInputState = NEW int[m_nJoyPadNum];
	m_diPrevInputState = NEW int[m_nJoyPadNum];

	memset(m_diInputState, 0, m_nJoyPadNum * sizeof(int));
	memset(m_diPrevInputState, 0, m_nJoyPadNum * sizeof(int));


	IBaseObject::Initialize();
}
//==========================================================================================
// 更新
//==========================================================================================
void cJoyPad::Update(void)
{
	for (int i = 1; i <= m_nJoyPadNum;i++)
	{
		// 入力状態を取得する
		memcpy(&m_diPrevInputState[i-1], &m_diInputState[i-1],sizeof(int));
		m_diInputState[i-1] = GetJoypadInputState(i);
	}
	IBaseObject::Update();
}
//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject * cJoyPad::Finalize(void)
{
	SAFE_DELETE_ARRAY(m_diInputState);
	SAFE_DELETE_ARRAY(m_diPrevInputState);

	IBaseObject::Finalize();
	return nullptr;
}
//==========================================================================================
// ボタン押下チェック
// 
//	unsigned int	kcode	チェックするボタン　
//   PAD_INPUT_1 : ボタン1
//   PAD_INPUT_DOWN : ↓キー
//   …
//  int				InputType パッド識別子
//    DX_INPUT_PAD1　　　　: パッド１
//    DX_INPUT_PAD1　　　　: パッド２
//   …
// 
// 戻り値	true:押されていた　false:押されていない
//==========================================================================================
bool cJoyPad::CheckButton(unsigned int kcode, int InputType)
{
	if( InputType > m_nJoyPadNum) return false;

	// ボタンが押されているかどうか
	if (m_diInputState[InputType-1] & kcode)
		return true;

	return false;
}
//==========================================================================================
// 押した瞬間をチェック
// 
//	unsigned int	kcode	チェックするボタン　
//   PAD_INPUT_1 : ボタン1
//   PAD_INPUT_DOWN : ↓キー
//   …
//  int				InputType パッド識別子
//    DX_INPUT_PAD1　　　　: パッド１
//    DX_INPUT_PAD1　　　　: パッド２
//   …
// 
// 戻り値	true:押されていた
//==========================================================================================
bool cJoyPad::CheckTriger(unsigned int kcode, int InputType)
{
	if (InputType > m_nJoyPadNum) return false;

	// ボタンが押された瞬間
	if ( !(m_diPrevInputState[InputType-1] & kcode) && (m_diInputState[InputType-1] & kcode)) return true;

	return false;
}
//==========================================================================================
// 離した瞬間をチェック
// 
//	unsigned int	kcode	チェックするボタン　
//   PAD_INPUT_1 : ボタン1
//   PAD_INPUT_DOWN : ↓キー
//   …
//  int				InputType パッド識別子
//    DX_INPUT_PAD1　　　　: パッド１
//    DX_INPUT_PAD1　　　　: パッド２
//   …
// 
// 戻り値	true:離された瞬間
//==========================================================================================
bool cJoyPad::CheckRelease(unsigned int kcode, int InputType)
{
	if (InputType > m_nJoyPadNum) return false;

	// ボタンが離された瞬間
	if ((m_diPrevInputState[InputType-1] & kcode) && !(m_diInputState[InputType-1] & kcode)) return true;

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
