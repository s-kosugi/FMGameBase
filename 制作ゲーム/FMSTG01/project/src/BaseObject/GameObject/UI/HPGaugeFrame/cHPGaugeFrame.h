#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cHPGaugeFrame.h												*/
/*  @brief		:	HP�Q�[�W�g�I�u�W�F�N�g										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/28													*/
/*																				*/
/*==============================================================================*/

#include "..\cUIObject.h"

//================================================================================================
// HP�Q�[�W�g�N���X
class cHPGaugeFrame : public cUIObject
{
public:
	cHPGaugeFrame(IBaseObject* parent);
	~cHPGaugeFrame(void);


	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	static const int PRIORITY = 2001;
};
//================================================================================================