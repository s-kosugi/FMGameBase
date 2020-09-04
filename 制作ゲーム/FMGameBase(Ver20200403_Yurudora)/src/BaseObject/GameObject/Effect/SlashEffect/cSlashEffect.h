#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSlashEffect.h												*/
/*  @brief		:	斬撃エフェクトクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/12													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// 斬撃エフェクトクラス
class cSlashEffect : public cEffectObject
{
public:
	cSlashEffect( IBaseObject* parent );
	~cSlashEffect( void );

	void Initialize( void );

private:
	// 定数	
	// 表示優先度
	static const int	PRIORITY;
	static const float	SCALE;
};
//================================================================================================