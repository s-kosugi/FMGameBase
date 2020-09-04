#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cBossRightBattery.h											*/
/*  @brief		:	�{�X��͂̉E�C��N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/19													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cEnemyBase.h"

//================================================================================================
// �{�X��͂̓G�N���X
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
	
	// �s���ʏ��
	enum ACT_STATE
	{
		STATE_WAIT,
		STATE_ATTACK,

		STATE_CRAZYWAIT,
		STATE_CRAZYATTACK,
	};

	ACT_STATE	m_eActionState;			// �s�����
	int			m_nActionTimer;			// �s���p�^�C�}�[

	int			m_nBulletTimer;			// �e���˃^�C�}�[
	cEnemyBase* m_pFollowObject;		// �Ǐ]����I�u�W�F�N�g

	int			m_nCrazyTimer;			// �����^�C�}�[

	// ��ԕʏ���
	void Wait( void );
	void Attack( void );
	void CrazyWait( void );
	void CrazyAttack( void );


	void MoveFollow( void );			// �Ǐ]����
	void CheckCrazy( void );			// ������Ԃւ̈ڍs�`�F�b�N

	// �萔
	const float HIT_RANGE = 90.0f;
	const int   PRIORITY = 81;
	const int   DEF_HP = 23000;
	const int   DEF_ATK = 100;
	const float MOVE_SPEED = 4.0f;
	const int   DEF_SCORE = 2000;
	const float	DEF_POSX = 100.0f;
	const float	DEF_POSY = 40.0f;
	const int   CRAZY_TIME = 1000;			// ������Ԃւ̈ڍs�^�C�~���O

	// �e�֘A�萔
	const int   SHOOT_INTERVAL = 15;
	const float BULLET_SPEED = 4.0f;
	const unsigned int BULLET_COLOR = 0xffffffff;
	const float SHOT_POSX = 10.0f;
	const float SHOT_POSY = 5.0f;
	
	// �ҋ@��
	const int	WAIT_NEXTACT_TIME = 120;
	
	// �U����
	const int	ATTACK_NEXTACT_TIME = 30;

	// �����ҋ@��
	const int	CRZWAIT_NEXTACT_TIME = 90;

	// �����U����
	const int	CRZATTACK_NEXTACT_TIME = 60;
	const int   BULLET_NUM = 12;
	const float BULLET_ANGLE_INTERVAL = 30.0f;
	const unsigned int CRZ_BULLLET_COLOR = 0xffff0000;
};
//================================================================================================