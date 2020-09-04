/*==============================================================================*/
/*																				*/
/*	@file title	:	cBossLeftBattery.cpp										*/
/*  @brief		:	ボス戦艦の左砲台クラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/22													*/
/*																				*/
/*==============================================================================*/

#include "cBossLeftBattery.h"
#include "..\..\..\Bullet\cBulletManager.h"
#include "..\..\..\Bullet\SnipeBullet\cSnipeBullet.h"
#include "..\..\..\Player\cPlayer.h"
#include "..\..\..\Effect\cEffectManager.h"
#include "..\..\cEnemyManager.h"

#include "..\..\..\..\..\Utility\utility.h"

//==========================================================================================
// コンストラクタ
//==========================================================================================
cBossLeftBattery::cBossLeftBattery(IBaseObject * parent)
	: cEnemyBase(parent, "BossFiveTube", "data\\graphic\\boss_01_leftBattery.png"),
	m_eActionState(STATE_WAIT),
	m_nActionTimer(0),
	m_nBulletTimer(0),
	m_pFollowObject(nullptr),
	m_nCrazyTimer(0)
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cBossLeftBattery::~cBossLeftBattery(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cBossLeftBattery::Initialize(void)
{
	m_eHitCate = HIT_ENEMY;
	m_fHitRange = HIT_RANGE;
	m_nHp = DEF_HP;
	m_nAtk = DEF_ATK;
	m_nScore = DEF_SCORE;

	// 追従オブジェクトが決定するまでは画面外に置く
	m_vPos = cVector2 (-200.0f,-200.0f );

	SetPriority(PRIORITY);

	cEnemyBase::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cBossLeftBattery::Update(void)
{

	// 状態別行動
	switch (m_eActionState)
	{

	case STATE_WAIT:
		Wait();
		break;

	case STATE_ATTACK:
		Attack();
		break;

	case STATE_CRAZYWAIT:
		CrazyWait();
		break;

	case STATE_CRAZYATTACK:
		CrazyAttack();
		break;
	}

	// 発狂状態への移行チェック
	CheckCrazy();

	// 追従処理
	MoveFollow();

	cEnemyBase::Update();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cBossLeftBattery::Finalize(void)
{
	cEnemyBase::Finalize();

	return this;
}

//==========================================================================================
// 待機
//==========================================================================================
void cBossLeftBattery::Wait(void)
{
	m_nActionTimer++;
	if (m_nActionTimer >= WAIT_NEXTACT_TIME)
	{
		m_eActionState = STATE_ATTACK;
		m_nActionTimer = 0;
	}
}
//==========================================================================================
// 攻撃
//==========================================================================================
void cBossLeftBattery::Attack(void)
{
	m_nBulletTimer++;
	if (m_nBulletTimer >= SHOOT_INTERVAL)
	{
		cVector2 shotPos = m_vPos;
		shotPos.x += SHOT_POSX;
		shotPos.y += SHOT_POSY;
		cBulletManager::GetInstance().Create(BT_SNIPE_BULLET, shotPos, HIT_ENEMY, BULLET_SPEED, BULLET_COLOR, "data\\graphic\\Bullet_02.png");
		m_nBulletTimer = 0;
	}

	m_nActionTimer++;
	if (m_nActionTimer >= ATTACK_NEXTACT_TIME)
	{
		m_eActionState = STATE_WAIT;
		m_nActionTimer = 0;
	}
}
//==========================================================================================
// 発狂状態待機
//==========================================================================================
void cBossLeftBattery::CrazyWait(void)
{
	m_nActionTimer++;
	if (m_nActionTimer >= CRZWAIT_NEXTACT_TIME)
	{
		m_eActionState = STATE_CRAZYATTACK;
		m_nActionTimer = 0;
	}
}
//==========================================================================================
// 発狂状態待機
//==========================================================================================
void cBossLeftBattery::CrazyAttack(void)
{
	m_nBulletTimer++;
	if (m_nBulletTimer >= SHOOT_INTERVAL)
	{
		cVector2 shotPos = m_vPos;
		shotPos.x += SHOT_POSX;
		shotPos.y += SHOT_POSY;
		cBulletManager::GetInstance().Create(BT_SNIPE_BULLET, shotPos, HIT_ENEMY, BULLET_SPEED, BULLET_COLOR, "data\\graphic\\Bullet_02.png");
		// nWay弾生成
		cBulletManager::GetInstance().CreateNWayBullet(m_vPos, HIT_ENEMY, BULLET_SPEED, BULLET_NUM, BULLET_ANGLE_INTERVAL, 0, CRZ_BULLLET_COLOR);
		m_nBulletTimer = 0;
	}

	m_nActionTimer++;
	if (m_nActionTimer >= CRZATTACK_NEXTACT_TIME)
	{
		m_eActionState = STATE_CRAZYWAIT;
		m_nActionTimer = 0;
	}
}

//==========================================================================================
// 追従処理
//==========================================================================================
void cBossLeftBattery::MoveFollow(void)
{
	if (nullptr != m_pFollowObject)
	{
		bool find = false;
		for (auto it = cEnemyManager::GetInstance().GetChildList()->begin(); it != cEnemyManager::GetInstance().GetChildList()->end(); it++)
		{
			if ((*it) == m_pFollowObject)
			{
				find = true;
				break;
			}
		}
		// 追従オブジェクトが見つかった場合
		if (find)
		{
			m_vPos.x = m_pFollowObject->GetPos().x + DEF_POSX;
			m_vPos.y = m_pFollowObject->GetPos().y + DEF_POSY;

			// 親が死んでいたら弾をうたない
			if(STATE_DEAD == m_pFollowObject->GetState())
			{
				m_eState = STATE_FLASH;
				m_eActionState = STATE_WAIT;
				m_nActionTimer = 0;

			}
		}
		else
		{
			// 追従オブジェクトが見つからなかった為削除する
			m_eObjectState = OBJECT_STATE_DEAD;
		}
	}
	else
	{
		// 追従オブジェクトが見つからなかった為削除する
		m_eObjectState = OBJECT_STATE_DEAD;
	}
}

//==========================================================================================
// 発狂状態への移行チェック
//==========================================================================================
void cBossLeftBattery::CheckCrazy(void)
{
	m_nCrazyTimer++;
	// 発狂チェック
	if (m_nCrazyTimer >= CRAZY_TIME && m_eActionState < STATE_CRAZYWAIT)
	{
		m_eActionState = STATE_CRAZYWAIT;
	}
}
