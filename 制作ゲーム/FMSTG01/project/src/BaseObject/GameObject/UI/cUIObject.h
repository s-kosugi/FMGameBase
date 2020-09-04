#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cUIObject.h													*/
/*  @brief		:	UI�x�[�X�I�u�W�F�N�g										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/27													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cSpriteObject.h"

//================================================================================================
// UI�x�[�X�I�u�W�F�N�g
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