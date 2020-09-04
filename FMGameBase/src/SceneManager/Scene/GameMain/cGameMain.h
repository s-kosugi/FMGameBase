#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cGameMain.h													*/
/*  @brief		:	ゲームメインシーン											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\IBaseScene.h"

//================================================================================================
// ゲームメインシーン
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