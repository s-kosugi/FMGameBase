#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBossLaserEffect.h											*/
/*  @brief		:	�{�X���[�U�[�G�t�F�N�g�N���X								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/23													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// �{�X���[�U�[�G�t�F�N�g�N���X
class cBossLaserEffect : public cEffectObject
{
public:
	cBossLaserEffect(IBaseObject* parent);
	~cBossLaserEffect(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	// �萔	
	// �\���D��x
	static const int	PRIORITY = 500;
};
//================================================================================================