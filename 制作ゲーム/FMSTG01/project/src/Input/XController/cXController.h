#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cXController.h												*/
/*  @brief		:	XBoxコントローラー入力クラス								*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/03/22													*/
/*																				*/
/*==============================================================================*/

#include "..\..\BaseObject\IBaseSingleton.h"
#include <DxLib.h>

class cXController : public IBaseSingleton<cXController>
{
public:
	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 破棄
	IBaseObject* Finalize(void);

	// ボタン押下チェック
	bool CheckButton(unsigned int kcode, int InputType = DX_INPUT_PAD1); // 押しているか
	bool CheckTriger(unsigned int kcode, int InputType = DX_INPUT_PAD1); // 押した瞬間
	bool CheckRelease(unsigned int kcode, int InputType = DX_INPUT_PAD1); // 離した瞬間

	// アナログ入力取得
	POINT  GetAnalogInput(int InputType);

	// 接続台数取得
	inline int  GetConnectNum(void) { return m_nJoyPadNum; };


	// XInput Joypad state
	XINPUT_STATE* m_xiInputState;
	// 前フレーム情報
	XINPUT_STATE* m_xiPrevInputState;

	// Xコントローラー接続数
	short m_nJoyPadNum;

};