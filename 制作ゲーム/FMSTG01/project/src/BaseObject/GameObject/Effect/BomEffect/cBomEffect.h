#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBomEffect.h												*/
/*  @brief		:	�����G�t�F�N�g�N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/12													*/
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
	void Update(void);
	IBaseObject* Finalize(void);

private:
	// �萔	
	// �\���D��x
	static const int	PRIORITY = 500;
};
//================================================================================================