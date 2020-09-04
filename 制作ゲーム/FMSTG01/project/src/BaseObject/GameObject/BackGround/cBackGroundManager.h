#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBackGroundManager.h										*/
/*  @brief		:	”wŒiŠÇ—ƒNƒ‰ƒX												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/10													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseSingleton.h"

class cBackGroundManager : public IBaseSingleton<cBackGroundManager>
{
public:
	// ‰Šú‰»
	void Initialize(void);

	// XV
	void Update( void );

	// ”jŠü
	IBaseObject* Finalize(void);

private:
	// ’è”
	// ¯‚ÌoŒ»”
	const int STAR_POP_NUM = 100;

	// ¯‚Ì¶¬ŠÔŠu
	const int STAR_GENERATE_INTERVAL = 5;
};