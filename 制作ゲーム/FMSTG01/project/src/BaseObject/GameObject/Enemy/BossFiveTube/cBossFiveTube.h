#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBossFiveTube.h												*/
/*  @brief		:	ボス戦艦の敵クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/19													*/
/*																				*/
/*==============================================================================*/

#include "..\cEnemyBase.h"

//================================================================================================
// ボス戦艦の敵クラス
class cBossFiveTube : public cEnemyBase
{
public:
	cBossFiveTube(IBaseObject* parent);
	~cBossFiveTube(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	
	// 
	enum ACT_STATE
	{
		STATE_APPEA,
		STATE_MOVE,
		STATE_WAIT,
		STATE_ATTACK,
		STATE_SIDEATTACK,
		STATE_AREAOUT,
		STATE_AREAOUTATTACK,
		STATE_AREAOUTAPPEAR,
		STATE_MOVEATTACK,
		STATE_CHARGE,
		STATE_LASER,

		STATE_STOP,
	};

	ACT_STATE	m_eActionState;
	int			m_nActionTimer;

	int			m_nBulletTimer;
	int			m_nMoveTimer;
	int			m_nMoveUpDownTimer;

	short		m_nAttackType;		// 現在の攻撃行動

	int			m_nDeadTimer;

	int			m_nTimeBonusCount;

	// 状態別処理
	void Appea( void );
	void Move( void );
	void Wait( void );
	void Attack( void );
	void SideAttack( void );
	void AreaOut( void );
	void AreaOutAttack( void );
	void AreaOutAppear(void);
	void MoveAttack(void);
	void Charge( void );
	void Laser( void );

	void AttackChoice( void );

	void ProcTimeBonus(void);
	void Dead(void);

	// 定数
	const float HIT_RANGE = 220.0f;
	const int   PRIORITY = 80;
	const int   DEF_HP = 75000;
	const int   DEF_ATK = 100;
	const float MOVE_SPEED = 4.0f;
	const int   DEF_SCORE = 10000;
	const int	TIME_BONUS_MAXSCORE = 10000;	// タイムボーナス最大スコア
	const int	TIME_BONUS_LOWER_LIMIT = 60 * 60 * 4;		// タイムボーナスの時間切れ
	const int	TIME_BONUS_HIGHER_LIMIT = 60 * 60 * 1;	// タイムボーナスの最大保障時間

	// ミサイル砲台位置
	const float	MIS_POS_X = 130.0f;
	const float	MIS_POS_Y = -100.0f;

	// 弾関連定数
	const int   SHOOT_INTERVAL = 20;
	const float BULLET_SPEED = 4.0f;
	const int   BULLET_NUM = 9;
	const float BULLET_ANGLE_INTERVAL = 20.0f;
	const unsigned int BULLET_COLOR = 0xffff4444;

	const int	SIDEATTACK_BULLET_NUM = 18;
	const float SIDEATTACK_BULLET_ANGLE_INTERVAL = 20.0f;
	const unsigned int SIDEATTACK_BULLET_COLOR = 0xff77ffff;

	// 出現時
	const float APPEA_NEXTACT_LINE = 180.0f;
	const float APPEA_INIT_SPEED = 12.5f;
	const float APPEA_BREAK = -0.15f;
	const float APPEA_BREAK_SPEED_LIMIT = -1.5f;

	// 移動時
	const int	MOVE_NEXTACT_TIME = 260;
	const float	MOVE_SPEED_RATE = 2.0f;
	const float MOVE_UPDOWNSPEED_RATE = 0.55f;
	const float MOVE_TIMER_RATE = 0.8f;
	const float MOVE_UPDOWNTIMER_RATE = 0.5f;

	// 待機時
	const int	WAIT_NEXTACT_TIME = 30;
	
	// 攻撃時
	const int	ATTACK_NEXTACT_TIME = 120;

	// エリアアウト時
	const float	AREAOUT_SPEED = 0.5f;
	const float AREAOUT_LINE = -400.0f;
	const int	AREAOUT_ACTION_TIME = 450;
	const float AREAIN_SPEED = 15.0f;
	const float AREAIN_BREAK = -0.15f;
	const float AREAIN_BACKSPEED_LIMIT = -3.0f;
	const int	AREAOUT_ATTACK_INTERVAL = 10;
	const float AREAOUT_BULLET_SPEED = 8.0f;
	const int	AREAOUT_BULLET_NUM = 4;

	// 移動攻撃時
	const int	MOVEATTACK_TIME = 600;
	const int	MOVEATTACK_BUL_INTERVAL = 15;
	const int MOVEATTACK_BUL_NUM = 4;
	const float MOVEATTACK_BUL_ANGLE = 25.0f;

	// チャージ時
	const int	CHARGE_TIME = 120;

	// レーザー時
	const int	LASER_TIME = 200;

	// 攻撃パターン変化境界
	const int	PATTERN_CHANGE_BORDER = (int)(DEF_HP * 0.65f);

	// 死亡時
	const int	DEAD_TIME = 200;
	const int	BOM_INTERVAL = 10;
	const int	BIG_BOM_TIME = 180;
};
//================================================================================================