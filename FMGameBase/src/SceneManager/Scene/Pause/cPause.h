#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cPause.h													*/
/*  @brief		:	�|�[�Y�V�[��												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/04/20													*/
/*																				*/
/*==============================================================================*/

#include "..\IBaseScene.h"

//================================================================================================
// �|�[�Y�V�[��
class cPause : public IBaseScene
{
public:
	cPause(IBaseObject* parent);
	~cPause(void);

	void Initialize(void) override;
	void Update(void) override;
	IBaseObject* Finalize(void) override;

};
//================================================================================================