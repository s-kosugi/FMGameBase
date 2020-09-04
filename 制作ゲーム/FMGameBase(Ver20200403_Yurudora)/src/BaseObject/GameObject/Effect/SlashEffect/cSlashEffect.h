#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSlashEffect.h												*/
/*  @brief		:	�a���G�t�F�N�g�N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/12													*/
/*																				*/
/*==============================================================================*/

#include "..\cEffectObject.h"

//================================================================================================
// �a���G�t�F�N�g�N���X
class cSlashEffect : public cEffectObject
{
public:
	cSlashEffect( IBaseObject* parent );
	~cSlashEffect( void );

	void Initialize( void );

private:
	// �萔	
	// �\���D��x
	static const int	PRIORITY;
	static const float	SCALE;
};
//================================================================================================