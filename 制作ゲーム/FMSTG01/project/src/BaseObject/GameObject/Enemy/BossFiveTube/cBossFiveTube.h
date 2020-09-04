#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBossFiveTube.h												*/
/*  @brief		:	�{�X��͂̓G�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/19													*/
/*																				*/
/*==============================================================================*/

#include "..\cEnemyBase.h"

//================================================================================================
// �{�X��͂̓G�N���X
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

	short		m_nAttackType;		// ���݂̍U���s��

	int			m_nDeadTimer;

	int			m_nTimeBonusCount;

	// ��ԕʏ���
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

	// �萔
	const float HIT_RANGE = 220.0f;
	const int   PRIORITY = 80;
	const int   DEF_HP = 75000;
	const int   DEF_ATK = 100;
	const float MOVE_SPEED = 4.0f;
	const int   DEF_SCORE = 10000;
	const int	TIME_BONUS_MAXSCORE = 10000;	// �^�C���{�[�i�X�ő�X�R�A
	const int	TIME_BONUS_LOWER_LIMIT = 60 * 60 * 4;		// �^�C���{�[�i�X�̎��Ԑ؂�
	const int	TIME_BONUS_HIGHER_LIMIT = 60 * 60 * 1;	// �^�C���{�[�i�X�̍ő�ۏ᎞��

	// �~�T�C���C��ʒu
	const float	MIS_POS_X = 130.0f;
	const float	MIS_POS_Y = -100.0f;

	// �e�֘A�萔
	const int   SHOOT_INTERVAL = 20;
	const float BULLET_SPEED = 4.0f;
	const int   BULLET_NUM = 9;
	const float BULLET_ANGLE_INTERVAL = 20.0f;
	const unsigned int BULLET_COLOR = 0xffff4444;

	const int	SIDEATTACK_BULLET_NUM = 18;
	const float SIDEATTACK_BULLET_ANGLE_INTERVAL = 20.0f;
	const unsigned int SIDEATTACK_BULLET_COLOR = 0xff77ffff;

	// �o����
	const float APPEA_NEXTACT_LINE = 180.0f;
	const float APPEA_INIT_SPEED = 12.5f;
	const float APPEA_BREAK = -0.15f;
	const float APPEA_BREAK_SPEED_LIMIT = -1.5f;

	// �ړ���
	const int	MOVE_NEXTACT_TIME = 260;
	const float	MOVE_SPEED_RATE = 2.0f;
	const float MOVE_UPDOWNSPEED_RATE = 0.55f;
	const float MOVE_TIMER_RATE = 0.8f;
	const float MOVE_UPDOWNTIMER_RATE = 0.5f;

	// �ҋ@��
	const int	WAIT_NEXTACT_TIME = 30;
	
	// �U����
	const int	ATTACK_NEXTACT_TIME = 120;

	// �G���A�A�E�g��
	const float	AREAOUT_SPEED = 0.5f;
	const float AREAOUT_LINE = -400.0f;
	const int	AREAOUT_ACTION_TIME = 450;
	const float AREAIN_SPEED = 15.0f;
	const float AREAIN_BREAK = -0.15f;
	const float AREAIN_BACKSPEED_LIMIT = -3.0f;
	const int	AREAOUT_ATTACK_INTERVAL = 10;
	const float AREAOUT_BULLET_SPEED = 8.0f;
	const int	AREAOUT_BULLET_NUM = 4;

	// �ړ��U����
	const int	MOVEATTACK_TIME = 600;
	const int	MOVEATTACK_BUL_INTERVAL = 15;
	const int MOVEATTACK_BUL_NUM = 4;
	const float MOVEATTACK_BUL_ANGLE = 25.0f;

	// �`���[�W��
	const int	CHARGE_TIME = 120;

	// ���[�U�[��
	const int	LASER_TIME = 200;

	// �U���p�^�[���ω����E
	const int	PATTERN_CHANGE_BORDER = (int)(DEF_HP * 0.65f);

	// ���S��
	const int	DEAD_TIME = 200;
	const int	BOM_INTERVAL = 10;
	const int	BIG_BOM_TIME = 180;
};
//================================================================================================