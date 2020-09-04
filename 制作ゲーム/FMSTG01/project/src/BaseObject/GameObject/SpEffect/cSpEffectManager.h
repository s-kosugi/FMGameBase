#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSpEffectManager.h											*/
/*  @brief		:	スプライトエフェクト管理クラス								*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/24													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseSingleton.h"
#include "SpEffectID.h"
#include "cSpEffectObject.h"

class cSpEffectManager : public IBaseSingleton<cSpEffectManager>
{
public:

	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 破棄
	IBaseObject* Finalize(void);

	// 生成
	cSpEffectObject* Create(SpEffectID id, cVector2 pos);

private:
};