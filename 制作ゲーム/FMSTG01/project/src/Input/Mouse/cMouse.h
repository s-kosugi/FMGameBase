#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cMouse.h													*/
/*  @brief		:	マウス入力クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/24													*/
/*																				*/
/*==============================================================================*/

#include "..\..\BaseObject\IBaseSingleton.h"
#include <DxLib.h>

class cMouse : public IBaseSingleton<cMouse>
{
public :
	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// マウスボタン押下チェック
	bool CheckButton(unsigned int kcode); // 押しているか
	bool CheckTriger(unsigned int kcode); // 押した瞬間
	bool CheckRelease(unsigned int kcode); // 離した瞬間

	// マウス座標の設定
	void SetPoint( int x, int y);
	void SetPoint( POINT pt);

	// マウス座標の取得
	POINT GetPoint( void );

	// MouseButton state
	int m_nButtonState;
	int m_nPrevButtonState;
};