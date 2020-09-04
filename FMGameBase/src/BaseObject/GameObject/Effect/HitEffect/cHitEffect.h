#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cHitEffect.h												*/
/*  @brief		:	�V���b�g�q�b�g�G�t�F�N�g�N���X								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/12													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// �V���b�g�q�b�g�G�t�F�N�g�N���X
class cHitEffect : public cEffectObject
{
public:
	cHitEffect(IBaseObject* parent);
	~cHitEffect(void);

	void Initialize(void);

private:
	// �萔	
	// �\���D��x
	static const int	PRIORITY;
	static const float	SCALE;
};
//================================================================================================