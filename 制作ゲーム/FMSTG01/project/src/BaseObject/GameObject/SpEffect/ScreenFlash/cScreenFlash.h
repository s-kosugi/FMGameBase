#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cScreenFlash.h												*/
/*  @brief		:	�X�N���[���_�ŃN���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/27													*/
/*																				*/
/*==============================================================================*/

#include "..\cSpEffectObject.h"

//================================================================================================
// �X�N���[���_�ŃG�t�F�N�g�N���X
class cScreenFlash : public cSpEffectObject
{
public:
	cScreenFlash(IBaseObject* parent);
	~cScreenFlash(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	int m_nLifeTime;
	int m_nMaxLifeTime;

	const int DEFAULT_LIFE_TIME = 20;

};
//================================================================================================