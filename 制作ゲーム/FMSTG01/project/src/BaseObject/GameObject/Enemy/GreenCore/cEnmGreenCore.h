#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmGreenCore.h												*/
/*  @brief		:	�O���[���R�A�̓G�N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/31													*/
/*																				*/
/*==============================================================================*/

#include "..\cEnemyBase.h"

//================================================================================================
// �O���[���R�A�̓G�N���X
class cEnmGreenCore : public cEnemyBase
{
public:
	cEnmGreenCore(IBaseObject* parent);
	~cEnmGreenCore(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	inline void SetAiNo(int n) { m_eAiNo = (AI_NO)n; };

private:
	enum AI_NO {
		AI_LEFT_APPER,
		AI_RIGHT_APPER,
	};

	int			m_nBulletTimer;
	cVector2	m_vPosUp;
	int			m_nMoveTimer;

	AI_NO		m_eAiNo;

	// �萔
	static const float HIT_RANGE;
	static const int   PRIORITY = 100;
	static const int   DEF_HP = 400;
	static const int   DEF_ATK = 100;
	static const float MOVE_SPEED;
	static const float ROTATE_SPEED;
	static const int   DEF_SCORE = 250;

	// �e�֘A�萔
	static const int   SHOOT_INTERVAL = 90;
	static const float BULLET_SPEED;
	static const int   BULLET_NUM = 5;
	static const float BULLET_ANGLE_INTERVAL;
	static const unsigned int BULLET_COLOR = 0xff77ff77;
};
//================================================================================================