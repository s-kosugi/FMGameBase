#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cChargeEffect.h												*/
/*  @brief		:	�`���[�W�G�t�F�N�g�N���X									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/22													*/
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

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	// �萔	
	// �\���D��x
	static const int	PRIORITY = 300;
};
//================================================================================================