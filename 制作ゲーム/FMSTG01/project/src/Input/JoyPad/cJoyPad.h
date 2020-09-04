#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cJoyPad.h													*/
/*  @brief		:	コントローラー入力クラス									*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/11/24													*/
/*																				*/
/*==============================================================================*/

#include "..\..\BaseObject\IBaseSingleton.h"
#include <DxLib.h>

class cJoyPad : public IBaseSingleton<cJoyPad>
{
public:
	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 破棄
	IBaseObject* Finalize(void);

	// ボタン押下チェック
	bool CheckButton(unsigned int kcode,int InputType = DX_INPUT_PAD1); // 押しているか
	bool CheckTriger(unsigned int kcode, int InputType = DX_INPUT_PAD1); // 押した瞬間
	bool CheckRelease(unsigned int kcode, int InputType = DX_INPUT_PAD1); // 離した瞬間

	// アナログ入力取得
	POINT  GetAnalogInput(int InputType);

	// 接続台数取得
	inline int  GetConnectNum(void) { return m_nJoyPadNum; };


	// DirectInput Joypad state
	int* m_diInputState;
	// 前フレーム情報
	int* m_diPrevInputState;

	// ジョイパッド接続数
	short m_nJoyPadNum;

};