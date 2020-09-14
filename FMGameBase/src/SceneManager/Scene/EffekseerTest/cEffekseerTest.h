#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cEffekseerTest.h											*/
/*  @brief		:	エフェクシアテストシーン									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/01/24													*/
/*																				*/
/*==============================================================================*/

#include "..\IBaseScene.h"
#include "BaseObject/GameObject/Effect/EffectID.h"

//================================================================================================
// エフェクシアテストシーン
class cEffekseerTest : public IBaseScene
{
public:
	cEffekseerTest(IBaseObject* parent);
	~cEffekseerTest(void);

	void Initialize(void) override;
	void Update(void) override;
	IBaseObject* Finalize(void) override;

private:
	EFFECT_ID	m_ePlayEffectID;
	cVector2	m_vPlayPos;
	float		m_fPlayScale;

};
//================================================================================================