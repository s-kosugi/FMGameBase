#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cTitle.h													*/
/*  @brief		:	�^�C�g���V�[��												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\IBaseScene.h"

//================================================================================================
// �^�C�g���V�[��
class cTitle : public IBaseScene
{
public:
	cTitle(IBaseObject* parent);
	~cTitle(void);

	void Initialize(void) override;
	void Update(void) override;
	IBaseObject* Finalize(void) override;

};
//================================================================================================