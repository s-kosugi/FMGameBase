/*==============================================================================*/
/*																				*/
/*	@file title	:	cKeyboard.cpp												*/
/*  @brief		:	キーボード入力クラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/24													*/
/*																				*/
/*==============================================================================*/

#include "cKeyboard.h"
#include <DxLib.h>

//==========================================================================================
// 初期化
//==========================================================================================
void cKeyboard::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "Keyboard";
	memset(m_diKeyState,0, KEY_STATE_NUM);
	memset(m_diPrevKeyState, 0, KEY_STATE_NUM);

	IBaseObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cKeyboard::Update(void)
{
	// 前フレーム情報の保存
	memcpy(m_diPrevKeyState,m_diKeyState, KEY_STATE_NUM);

	// キー状態の取得
	GetHitKeyStateAll(m_diKeyState);

	IBaseObject::Update();
}
//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject * cKeyboard::Finalize(void)
{
	IBaseObject::Finalize();
	return nullptr;
}

//==========================================================================================
// キー押下チェック
// 
//	unsigned int	kcode	チェックするキーコード　
//   KEY_INPUT_A : キーボードAキー
//   KEY_INPUT_B : キーボードBキー
//   …
// 
// 戻り値	true:押されていた　false:押されていない
//==========================================================================================
bool cKeyboard::CheckButton(unsigned int kcode)
{
	// キーが押されているかどうか
	if(m_diKeyState[kcode] == 1) return true;

	return false;
}

//==========================================================================================
// 押した瞬間をチェック
// 
//	unsigned int	kcode	チェックするキーコード　
//   KEY_INPUT_A : キーボードAキー
//   KEY_INPUT_B : キーボードBキー
//   …
// 
// 戻り値	true:押した瞬間
//==========================================================================================
bool cKeyboard::CheckTriger(unsigned int kcode)
{
	if (m_diPrevKeyState[kcode] == 0 && m_diKeyState[kcode] == 1) return true;

	return false;
}

//==========================================================================================
// 離した瞬間をチェック
// 
//	unsigned int	kcode	チェックするキーコード　
//   KEY_INPUT_A : キーボードAキー
//   KEY_INPUT_B : キーボードBキー　
//   …
// 
// 戻り値	true:離した瞬間
//==========================================================================================
bool cKeyboard::CheckRelease(unsigned int kcode)
{
	if (m_diPrevKeyState[kcode] == 1 && m_diKeyState[kcode] == 0) return true;

	return false;
}
