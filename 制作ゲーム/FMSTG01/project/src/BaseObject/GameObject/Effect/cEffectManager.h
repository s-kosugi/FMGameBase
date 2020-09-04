#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEffectManager.h											*/
/*  @brief		:	エフェクト管理クラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/12													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseSingleton.h"
#include "EffectID.h"
#include "cEffectObject.h"

class cEffectManager : public IBaseSingleton<cEffectManager>
{
public:

	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 破棄
	IBaseObject* Finalize(void);

	// 生成
	cEffectObject* Create(EffectID id, cVector2 pos);

private:
};