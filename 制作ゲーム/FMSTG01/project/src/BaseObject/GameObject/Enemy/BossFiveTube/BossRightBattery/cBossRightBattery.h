#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBossRightBattery.h											*/
/*  @brief		:	ボス戦艦の右砲台クラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/19													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cEnemyBase.h"

//================================================================================================
// ボス戦艦の敵クラス
class cBossRightBattery : public cEnemyBase
{
public:
	cBossRightBattery(IBaseObject* parent);
	~cBossRightBattery(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	inline void SetFollowObject(cEnemyBase* pFollowObj) { m_pFollowObject = pFollowObj;};

private:
	
	// 行動別状態
	enum ACT_STATE
	{
		STATE_WAIT,
		STATE_ATTACK,

		STATE_CRAZYWAIT,
		STATE_CRAZYATTACK,
	};

	ACT_STATE	m_eActionState;			// 行動状態
	int			m_nActionTimer;			// 行動用タイマー

	int			m_nBulletTimer;			// 弾発射タイマー
	cEnemyBase* m_pFollowObject;		// 追従するオブジェクト

	int			m_nCrazyTimer;			// 発狂タイマー

	// 状態別処理
	void Wait( void );
	void Attack( void );
	void CrazyWait( void );
	void CrazyAttack( void );


	void MoveFollow( void );			// 追従処理
	void CheckCrazy( void );			// 発狂状態への移行チェック

	// 定数
	const float HIT_RANGE = 90.0f;
	const int   PRIORITY = 81;
	const int   DEF_HP = 23000;
	const int   DEF_ATK = 100;
	const float MOVE_SPEED = 4.0f;
	const int   DEF_SCORE = 2000;
	const float	DEF_POSX = 100.0f;
	const float	DEF_POSY = 40.0f;
	const int   CRAZY_TIME = 1000;			// 発狂状態への移行タイミング

	// 弾関連定数
	const int   SHOOT_INTERVAL = 15;
	const float BULLET_SPEED = 4.0f;
	const unsigned int BULLET_COLOR = 0xffffffff;
	const float SHOT_POSX = 10.0f;
	const float SHOT_POSY = 5.0f;
	
	// 待機時
	const int	WAIT_NEXTACT_TIME = 120;
	
	// 攻撃時
	const int	ATTACK_NEXTACT_TIME = 30;

	// 発狂待機時
	const int	CRZWAIT_NEXTACT_TIME = 90;

	// 発狂攻撃時
	const int	CRZATTACK_NEXTACT_TIME = 60;
	const int   BULLET_NUM = 12;
	const float BULLET_ANGLE_INTERVAL = 30.0f;
	const unsigned int CRZ_BULLLET_COLOR = 0xffff0000;
};
//================================================================================================