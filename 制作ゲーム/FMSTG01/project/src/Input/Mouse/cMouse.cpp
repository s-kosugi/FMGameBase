/*==============================================================================*/
/*																				*/
/*	@file title	:	cMouse.cpp													*/
/*  @brief		:	マウス入力クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/24													*/
/*																				*/
/*==============================================================================*/

#include "cMouse.h"

//==========================================================================================
// 初期化
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
// 更新
//==========================================================================================
void cMouse::Update(void)
{
	// 前フレーム情報の保存
	memcpy(&m_nPrevButtonState, &m_nButtonState, sizeof(int));

	// マウス入力状態の取得
	m_nButtonState = GetMouseInput();

	IBaseObject::Update();
}
//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject * cMouse::Finalize(void)
{
	IBaseObject::Finalize();
	return nullptr;
}
//==========================================================================================
// キー押下チェック
// 
//	unsigned int	kcode	チェックするキーコード
//   MOUSE_INPUT_LEFT   : 左ボタン
//   MOUSE_INPUT_RIGHT  : 右ボタン
//   MOUSE_INPUT_MIDDLE : マウス中央ボタン
// 
// 戻り値	true:押されていた　FALSE:押されていない
//==========================================================================================
bool cMouse::CheckButton(unsigned int kcode)
{
	// ボタンが押されているかどうか
	if (m_nButtonState & kcode) return true;

	return false;
}

//==========================================================================================
// 押した瞬間をチェック
// 
//	unsigned int	kcode	チェックするキーコード　
// 
// 戻り値	true:押されていた　FALSE:押されていない
//==========================================================================================
bool cMouse::CheckTriger(unsigned int kcode)
{
	if (!(m_nPrevButtonState & kcode) && (m_nButtonState & kcode)) return true;

	return false;
}

//==========================================================================================
// 離した瞬間をチェック
// 
//	unsigned int	kcode	チェックするキーコード　
// 
// 戻り値	true:押されていた　FALSE:押されていない
//==========================================================================================
bool cMouse::CheckRelease(unsigned int kcode)
{
	if ((m_nPrevButtonState & kcode) && !(m_nButtonState & kcode)) return true;

	return false;
}

//==========================================================================================
// マウス座標の設定
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
// マウス座標の取得
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
