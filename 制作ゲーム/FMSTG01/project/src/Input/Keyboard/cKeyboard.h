#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cKeyboard.h													*/
/*  @brief		:	キーボード入力クラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/24													*/
/*																				*/
/*==============================================================================*/

#include "..\..\BaseObject\IBaseSingleton.h"

class cKeyboard : public IBaseSingleton<cKeyboard>
{
public:
	// 初期化
	void Initialize(void);

	// 更新
	void Update( void );

	// 破棄
	IBaseObject* Finalize( void );

	// キー押下チェック
	bool CheckButton(unsigned int kcode); // 押しているか
	bool CheckTriger(unsigned int kcode); // 押した瞬間
	bool CheckRelease(unsigned int kcode); // 離した瞬間

	// DirectInput keyboard state
	char m_diKeyState[256];
	// 前フレーム情報
	char m_diPrevKeyState[256];

	// 定数
	const int KEY_STATE_NUM = 256;
};