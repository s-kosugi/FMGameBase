#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cWarning.h													*/
/*  @brief		:	���[�j���O�G�t�F�N�g�N���X									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/27													*/
/*																				*/
/*==============================================================================*/

#include "..\cSpEffectObject.h"

//================================================================================================
// �X�N�t�F�N�g�N���X
class cWarning : public cSpEffectObject
{
public:
	cWarning(IBaseObject* parent);
	~cWarning(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:

	int m_nCounter;

	static const int PRIORITY = 900;
};
//================================================================================================