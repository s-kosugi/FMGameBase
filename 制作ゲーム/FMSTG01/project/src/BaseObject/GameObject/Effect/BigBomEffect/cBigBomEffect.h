#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBigBomEffect.h												*/
/*  @brief		:	�唚���G�t�F�N�g�N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/28													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// �唚���G�t�F�N�g�N���X
class cBigBomEffect : public cEffectObject
{
public:
	cBigBomEffect(IBaseObject* parent);
	~cBigBomEffect(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	// �萔	
	// �\���D��x
	static const int	PRIORITY = 500;
};
//================================================================================================