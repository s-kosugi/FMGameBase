#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBreakEffect.h												*/
/*  @brief		:	�����G�t�F�N�g�N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/12													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// �����G�t�F�N�g�N���X
class cBreakEffect : public cEffectObject
{
public:
	cBreakEffect(IBaseObject* parent);
	~cBreakEffect(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	// �萔	
	// �\���D��x
	const int	PRIORITY = 2500;
};
//================================================================================================