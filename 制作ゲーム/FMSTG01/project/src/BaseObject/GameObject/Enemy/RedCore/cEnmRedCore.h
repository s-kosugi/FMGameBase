#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmRedCore.h												*/
/*  @brief		:	レッドコアの敵クラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/01/31													*/
/*																				*/
/*==============================================================================*/

#include "..\cEnemyBase.h"

//================================================================================================
// レッドの敵クラス
class cEnmRedCore : public cEnemyBase
{
public:
	cEnmRedCore(IBaseObject* parent);
	~cEnmRedCore(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	int			m_nBulletTimer;

	// 定数
	static const float HIT_RANGE;
	static const int   PRIORITY = 100;
	static const int   DEF_HP = 600;
	static const int   DEF_ATK = 100;
	static const float MOVE_SPEED;
	static const float ROTATE_SPEED;
	static const int   DEF_SCORE = 100;

	// 弾関連定数
	static const int   SHOOT_INTERVAL = 90;
	static const float BULLET_SPEED;
	static const int   BULLET_NUM = 3;
	static const float BULLET_ANGLE_INTERVAL;
	static const unsigned int BULLET_COLOR = 0xffff7777;
};
//================================================================================================