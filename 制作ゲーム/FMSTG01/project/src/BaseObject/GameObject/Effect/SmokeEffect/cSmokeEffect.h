#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSmokeEffect.h												*/
/*  @brief		:	煙エフェクトクラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/19													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"
#include "..\..\..\cSpriteObject.h"

//================================================================================================
// 煙エフェクトクラス
class cSmokeEffect : public cEffectObject
{
public:
	cSmokeEffect(IBaseObject* parent);
	~cSmokeEffect(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	inline void SetFollowingObj(cSpriteObject* pObj) {m_pFollowingObj = pObj;};

private:
	// 追従オブジェクト
	cSpriteObject* m_pFollowingObj;

	// 定数	
	// 表示優先度
	const int	PRIORITY = 400;
};
//================================================================================================