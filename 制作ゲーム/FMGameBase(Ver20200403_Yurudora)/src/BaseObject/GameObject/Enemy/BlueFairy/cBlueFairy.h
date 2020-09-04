#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBlueFairy.h												*/
/*  @brief		:	�d���N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/04/23													*/
/*																				*/
/*==============================================================================*/

#include "..\IEnemyBase.h"

//================================================================================================
// �d���N���X
class cBlueFairy : public IEnemyBase
{
public:
	cBlueFairy(IBaseObject* parent);
	~cBlueFairy(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	void Dead( void ) override;

	void StartAttack(void)override;

private:

	//--------------------------------------------------------------------------------------------
	// �萔

	// �\���D��x
	static const int	PRIORITY;

	// �ړ����x
	static const float	MOVE_SPEED;

	// �U�����W�̕␳�l
	static const float	ATTACK_POSY;

	//--------------------------------------------------------------------------------------------

};
//================================================================================================