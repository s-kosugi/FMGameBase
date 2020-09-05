#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cLandingEffect.h											*/
/*  @brief		:	���n�G�t�F�N�g�N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/04/10													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// ���n�G�t�F�N�g�N���X
class cLandingEffect : public cEffectObject
{
public:
	cLandingEffect(IBaseObject* parent);
	~cLandingEffect(void);

	void Initialize(void);

private:
	// �萔	
	// �\���D��x
	static const int	PRIORITY;
	static const float	SCALE;
};
//================================================================================================