#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cGameMain.h													*/
/*  @brief		:	�Q�[�����C���V�[��											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\IBaseScene.h"

//================================================================================================
// �Q�[�����C���V�[��
class cGameMain : public IBaseScene
{
public:
	cGameMain(IBaseObject* parent);
	~cGameMain(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

};
//================================================================================================