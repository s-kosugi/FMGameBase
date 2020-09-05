#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cGetScoreEffect.h											*/
/*  @brief		:	�X�R�A�擾�G�t�F�N�g�N���X									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/04/07													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// �X�R�A�擾�G�t�F�N�g�N���X
class cGetScoreEffect : public cEffectObject
{
public:
	cGetScoreEffect(IBaseObject* parent);
	~cGetScoreEffect(void);

	void Initialize(void) override;
	void Update(void) override;

private:
	// �萔	
	// �\���D��x
	static const int	PRIORITY;
	static const float	SCALE;
};
//================================================================================================