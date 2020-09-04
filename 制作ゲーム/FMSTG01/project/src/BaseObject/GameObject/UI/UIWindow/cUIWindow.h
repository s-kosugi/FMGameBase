#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cUIWindow.h													*/
/*  @brief		:	UIウィンドウオブジェクト									*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/27													*/
/*																				*/
/*==============================================================================*/

#include "..\cUIObject.h"

//================================================================================================
// UI用ウィンドウクラス
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