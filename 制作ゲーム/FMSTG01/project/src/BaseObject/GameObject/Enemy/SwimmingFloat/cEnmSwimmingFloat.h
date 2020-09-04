#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmSwimmingFloat.h											*/
/*  @brief		:	�r�[�g�̓G�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/18													*/
/*																				*/
/*==============================================================================*/

#include "..\cEnemyBase.h"

//================================================================================================
// �r�[�g�̓G�N���X
class cEnmSwimmingFloat : public cEnemyBase
{
public:
	cEnmSwimmingFloat(IBaseObject* parent);
	~cEnmSwimmingFloat(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:

	// �s���p�^�[���t���O
	bool		m_bShot;
	// �s���^�C�}�[
	int			m_nActionTimer;

	// �e���ˊԊu
	int			m_nBulletTimer;
	// �e���ˊp�x
	float		m_nShotAngle;

	// �萔
	const float HIT_RANGE = 32.0f;
	const int   PRIORITY = 100;
	const int   DEF_HP = 3800;
	const int   DEF_ATK = 100;
	const float MOVE_SPEED = 0.8f;
	const int   DEF_SCORE = 500;

	// �A�j���[�V�����֘A
	const int	SIZE_X	= 64;
	const int	SIZE_Y  = 64;
	const int	ANIM_NUM = 4;
	const int	ANIM_TIME = 4;

	// �s���֘A
	const int	SHOT_TIME = 600;
	const int	STOP_TIME = 200;

	// �e�֘A�萔
	const int   SHOOT_INTERVAL = 5;
	const float BULLET_SPEED = 4.0f;
	const int   BULLET_NUM = 1;
	const float BULLET_ANGLE_INTERVAL = 30.0f;
	const unsigned int BULLET_COLOR = COLOR_YELLOW;
	const float BULLET_ANGLE_RANGE = 75.0f;
	const float BULLET_ANGLE_ADD = 5.0f;
};
//================================================================================================