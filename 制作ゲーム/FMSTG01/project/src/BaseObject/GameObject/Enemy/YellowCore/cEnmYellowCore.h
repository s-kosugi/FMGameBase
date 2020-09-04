#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmYellowCore.h											*/
/*  @brief		:	イエローコアの敵クラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/26													*/
/*																				*/
/*==============================================================================*/

#include "..\cEnemyBase.h"

//================================================================================================
// イエローコアの敵クラス
class cEnmYellowCore : public cEnemyBase
{
public:
	cEnmYellowCore(IBaseObject* parent);
	~cEnmYellowCore(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	int			m_nBulletTimer;
	int			m_nLifeTimer;

	// 定数
	const float HIT_RANGE = 24.0f;
	const int   PRIORITY = 100;
	const int   DEF_HP = 350;
	const int   DEF_ATK = 100;
	const float MOVE_SPEED_X = 4.0f;
	const float MOVE_SPEED_Y = 1.5f;
	const float ROTATE_SPEED = 3.0f;
	const int   DEF_SCORE = 100;
	const int	MOVESPEED_ADDTIME = 2;

	// 弾関連定数
	const int   SHOOT_INTERVAL = 120;
	const float BULLET_SPEED = 3.0f;
	const int   BULLET_NUM = 3;
	const float BULLET_ANGLE_INTERVAL = 30.0f;
	const unsigned int BULLET_COLOR = 0xffffff77;
};
//================================================================================================