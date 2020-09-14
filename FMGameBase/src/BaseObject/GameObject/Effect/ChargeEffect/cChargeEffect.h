#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cChargeEffect.h												*/
/*  @brief		:	�`���[�W�G�t�F�N�g�N���X									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/01/24													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// �`���[�W�G�t�F�N�g�N���X
class cChargeEffect : public cEffectObject
{
public:
	cChargeEffect(IBaseObject* parent);
	~cChargeEffect(void);

	void Initialize(void) override;

private:
	// �萔	
	// �\���D��x
	static const int	PRIORITY;
	static const float	SCALE;
};
//================================================================================================