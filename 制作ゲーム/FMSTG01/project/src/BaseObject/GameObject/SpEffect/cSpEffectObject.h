#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cSpEffectObject.h											*/
/*  @brief		:	スプライトエフェクトオブジェクト							*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/24													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cSpriteObject.h"

//================================================================================================
// スプライトエフェクトオブジェクト
// １クラスにつき１つのエフェクトを持ちたい場合に使用する。
class cSpEffectObject : public cSpriteObject
{
public:
	cSpEffectObject(IBaseObject* parent, const std::string& objectname, const std::string& filename);
	~cSpEffectObject(void);


	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:

};
//================================================================================================