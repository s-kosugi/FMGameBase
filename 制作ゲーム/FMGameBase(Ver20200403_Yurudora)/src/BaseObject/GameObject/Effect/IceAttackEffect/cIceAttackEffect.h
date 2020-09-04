#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cIceAttackEffect.h											*/
/*  @brief		:	�X�U���G�t�F�N�g�N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/04/10													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// �X�U���G�t�F�N�g�N���X
class cIceAttackEffect : public cEffectObject
{
public:
	cIceAttackEffect(IBaseObject* parent);
	~cIceAttackEffect(void);

	void Initialize(void);

private:
	// �萔	
	// �\���D��x
	static const int	PRIORITY;
	static const float	SCALE;
};
//================================================================================================