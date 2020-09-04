#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cUIWindow.h													*/
/*  @brief		:	UI�E�B���h�E�I�u�W�F�N�g									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/27													*/
/*																				*/
/*==============================================================================*/

#include "..\cUIObject.h"

//================================================================================================
// UI�p�E�B���h�E�N���X
class cUIWindow : public cUIObject
{
public:
	cUIWindow(IBaseObject* parent);
	~cUIWindow(void);


	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	const int PRIORITY = 2000;
};
//================================================================================================