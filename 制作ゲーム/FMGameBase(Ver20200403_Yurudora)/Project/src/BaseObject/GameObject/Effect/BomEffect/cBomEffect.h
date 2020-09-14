#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBomEffect.h												*/
/*  @brief		:	�����G�t�F�N�g�N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/01/24													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// �����G�t�F�N�g�N���X
class cBomEffect : public cEffectObject
{
public:
	cBomEffect(IBaseObject* parent);
	~cBomEffect(void);

	void Initialize(void);

private:
	// �萔	
	// �\���D��x
	static const int	PRIORITY;
	static const float	SCALE;
};
//================================================================================================