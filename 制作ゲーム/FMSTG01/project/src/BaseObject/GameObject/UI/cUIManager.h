#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cUIManager.h												*/
/*  @brief		:	UI管理クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/27													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseSingleton.h"
#include "UIID.h"
#include "cUIObject.h"

class cUIManager : public IBaseSingleton<cUIManager>
{
public:

	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 破棄
	IBaseObject* Finalize(void);

	// 生成
	cUIObject* Create(UIID id, cVector2 pos);

private:
};