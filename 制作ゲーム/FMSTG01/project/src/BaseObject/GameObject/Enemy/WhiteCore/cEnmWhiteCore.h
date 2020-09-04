#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmWhiteCore.h												*/
/*  @brief		:	ホワイトコアの敵クラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "..\cEnemyBase.h"

//================================================================================================
// ホワイトコアの敵クラス
class cEnmWhiteCore : public cEnemyBase
{
public:
	cEnmWhiteCore(IBaseObject* parent);
	~cEnmWhiteCore(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	int			m_nBulletTimer;

	// 定数
	static const float HIT_RANGE;
	static const int   PRIORITY = 100;
	static const int   DEF_HP = 500;
	static const int   DEF_ATK = 100;
	static const float MOVE_SPEED;
	static const float ROTATE_SPEED;
	static const int   DEF_SCORE = 100;

	// 弾関連定数
	static const int   SHOOT_INTERVAL = 150;
	static const int   SHOOT_WAIT = 30;
	static const float BULLET_SPEED;
	static const int   BULLET_NUM = 8;
	static const float BULLET_ANGLE_INTERVAL;
	static const unsigned int BULLET_COLOR = 0xffff7777;
};
//================================================================================================