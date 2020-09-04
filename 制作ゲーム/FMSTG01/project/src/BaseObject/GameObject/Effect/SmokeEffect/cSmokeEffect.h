#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSmokeEffect.h												*/
/*  @brief		:	���G�t�F�N�g�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/19													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"
#include "..\..\..\cSpriteObject.h"

//================================================================================================
// ���G�t�F�N�g�N���X
class cSmokeEffect : public cEffectObject
{
public:
	cSmokeEffect(IBaseObject* parent);
	~cSmokeEffect(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	inline void SetFollowingObj(cSpriteObject* pObj) {m_pFollowingObj = pObj;};

private:
	// �Ǐ]�I�u�W�F�N�g
	cSpriteObject* m_pFollowingObj;

	// �萔	
	// �\���D��x
	const int	PRIORITY = 400;
};
//================================================================================================