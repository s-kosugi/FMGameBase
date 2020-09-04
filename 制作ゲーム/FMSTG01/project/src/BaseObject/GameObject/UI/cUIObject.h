#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cUIObject.h													*/
/*  @brief		:	UIベースオブジェクト										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/27													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cSpriteObject.h"

//================================================================================================
// UIベースオブジェクト
class cUIObject : public cSpriteObject
{
public:
	cUIObject(IBaseObject* parent, const std::string& objectname, const std::string& filename);
	~cUIObject(void);


	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:

};
//================================================================================================