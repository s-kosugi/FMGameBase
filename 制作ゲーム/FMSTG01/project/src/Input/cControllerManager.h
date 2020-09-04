#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cControllerManager.h										*/
/*  @brief		:	入力管理クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "..\BaseObject\IBaseSingleton.h"

class cControllerManager : public IBaseSingleton<cControllerManager>
{
public:
	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 破棄
	IBaseObject* Finalize(void);

	// キー定義
	enum KEY_DEFINE
	{
		KEY_LEFT = 0,
		KEY_UP,
		KEY_RIGHT,
		KEY_DOWN,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_PAUSE,


		KEY_ANY,		// 全てのキー

		KEY_MAX = KEY_ANY
	};

	// キー押下チェック(1P+キーボード用)
	bool CheckButton(KEY_DEFINE kcode);
	bool CheckTriger(KEY_DEFINE kcode);
	bool CheckRelease(KEY_DEFINE kcode);
};