#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cFlameEffect.h												*/
/*  @brief		:	���U���G�t�F�N�g�N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/04/10													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// ���U���G�t�F�N�g�N���X
class cFlameEffect : public cEffectObject
{
public:
	cFlameEffect(IBaseObject* parent);
	~cFlameEffect(void);

	void Initialize(void);

private:
	// �萔	
	// �\���D��x
	static const int	PRIORITY;
	static const float	SCALE;
};
//================================================================================================