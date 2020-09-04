#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmBlueCore.h												*/
/*  @brief		:	�u���[�R�A�̓G�N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/21													*/
/*																				*/
/*==============================================================================*/

#include "..\cEnemyBase.h"

//================================================================================================
// �u���[�R�A�̓G�N���X
class cEnmBlueCore : public cEnemyBase
{
public:
	cEnmBlueCore(IBaseObject* parent);
	~cEnmBlueCore(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	int			m_nBulletTimer;

	// �萔
	const float HIT_RANGE = 24.0f;
	const int   PRIORITY = 100;
	const int   DEF_HP = 1500;
	const int   DEF_ATK = 100;
	const float MOVE_SPEED = 1.0f;
	const float ROTATE_SPEED = 1.5f;
	const int   DEF_SCORE = 300;

	// �e�֘A�萔
	const int   SHOOT_INTERVAL = 5;
	const float BULLET_SPEED = 4.0f;
	const unsigned int BULLET_COLOR = 0xffff7777;
};
//================================================================================================