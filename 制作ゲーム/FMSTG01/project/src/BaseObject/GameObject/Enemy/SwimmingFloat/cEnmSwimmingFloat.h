#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmSwimmingFloat.h											*/
/*  @brief		:	ビート板の敵クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/18													*/
/*																				*/
/*==============================================================================*/

#include "..\cEnemyBase.h"

//================================================================================================
// ビート板の敵クラス
class cEnmSwimmingFloat : public cEnemyBase
{
public:
	cEnmSwimmingFloat(IBaseObject* parent);
	~cEnmSwimmingFloat(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:

	// 行動パターンフラグ
	bool		m_bShot;
	// 行動タイマー
	int			m_nActionTimer;

	// 弾発射間隔
	int			m_nBulletTimer;
	// 弾発射角度
	float		m_nShotAngle;

	// 定数
	const float HIT_RANGE = 32.0f;
	const int   PRIORITY = 100;
	const int   DEF_HP = 3800;
	const int   DEF_ATK = 100;
	const float MOVE_SPEED = 0.8f;
	const int   DEF_SCORE = 500;

	// アニメーション関連
	const int	SIZE_X	= 64;
	const int	SIZE_Y  = 64;
	const int	ANIM_NUM = 4;
	const int	ANIM_TIME = 4;

	// 行動関連
	const int	SHOT_TIME = 600;
	const int	STOP_TIME = 200;

	// 弾関連定数
	const int   SHOOT_INTERVAL = 5;
	const float BULLET_SPEED = 4.0f;
	const int   BULLET_NUM = 1;
	const float BULLET_ANGLE_INTERVAL = 30.0f;
	const unsigned int BULLET_COLOR = COLOR_YELLOW;
	const float BULLET_ANGLE_RANGE = 75.0f;
	const float BULLET_ANGLE_ADD = 5.0f;
};
//================================================================================================