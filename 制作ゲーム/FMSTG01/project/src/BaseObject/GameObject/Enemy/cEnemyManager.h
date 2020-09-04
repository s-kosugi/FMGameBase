#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnemyManager.h												*/
/*  @brief		:	“GŠÇ—ƒNƒ‰ƒX												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "..\..\IBaseSingleton.h"
#include "EnemyID.h"
#include "cEnemyBase.h"

class cEnemyManager : public IBaseSingleton<cEnemyManager>
{
public:
	// ‰Šú‰»
	void Initialize(void);

	// XV
	void Update(void);

	// ”jŠü
	IBaseObject* Finalize(void);

	// “G¶¬
	cEnemyBase* Create( EnemyID id);
private:
};