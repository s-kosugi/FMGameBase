#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cFlameHitEffect.h											*/
/*  @brief		:	���U���q�b�g�G�t�F�N�g�N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/04/10													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// ���U���΂��ƃG�t�F�N�g�N���X
class cFlameHitEffect : public cEffectObject
{
public:
	cFlameHitEffect(IBaseObject* parent);
	~cFlameHitEffect(void);

	void Initialize(void);

private:
	// �萔	
	// �\���D��x
	static const int	PRIORITY;
	static const float	SCALE;
};
//================================================================================================