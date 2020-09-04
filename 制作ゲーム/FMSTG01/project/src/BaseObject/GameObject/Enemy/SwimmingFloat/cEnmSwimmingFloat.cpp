/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmSwimmingFloat.cpp										*/
/*  @brief		:	ビート版の敵クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/18													*/
/*																				*/
/*==============================================================================*/

#include "cEnmSwimmingFloat.h"
#include "..\..\..\..\cGame.h"
#include "..\..\Bullet\cBulletManager.h"
#include "..\..\Bullet\AngleBullet\cAngleBullet.h"
#include "..\..\Effect\cEffectManager.h"
#include "..\..\..\..\Utility\utility.h"

//==========================================================================================
// コンストラクタ
//==========================================================================================
cEnmSwimmingFloat::cEnmSwimmingFloat(IBaseObject * parent)
	: cEnemyBase(parent, "EnmSwimmingFloat", "data\\graphic\\enemy_11.png"),
	m_nBulletTimer(0),
	m_nActionTimer(0),
	m_bShot(false),
	m_nShotAngle(0.0f)
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cEnmSwimmingFloat::~cEnmSwimmingFloat(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cEnmSwimmingFloat::Initialize(void)
{
	cGame game = cGame::GetInstance();

	m_eHitCate = HIT_ENEMY;
	m_fHitRange = HIT_RANGE;
	m_nHp = DEF_HP;
	m_nAtk = DEF_ATK;
	m_nScore = DEF_SCORE;
	SetAnimation(0, 0, SIZE_X, SIZE_Y, ANIM_NUM, ANIM_TIME);


	SetPriority(PRIORITY);

	cEnemyBase::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cEnmSwimmingFloat::Update(void)
{

	m_nActionTimer++;
	if (m_nActionTimer == STOP_TIME)
	{
		// ショット開始
		m_bShot = true;
	}
	if(m_bShot)
	{
		m_nBulletTimer++;
		if (m_nBulletTimer >= SHOOT_INTERVAL)
		{
			// 発射角度を作成
			float angle = (float)sin(DEG_TO_RAD(m_nShotAngle)) * BULLET_ANGLE_RANGE;
			// nWay弾生成
			cBulletManager::GetInstance().CreateNWayBullet(m_vPos, HIT_ENEMY, BULLET_SPEED, BULLET_NUM, BULLET_ANGLE_INTERVAL, angle , BULLET_COLOR);
			m_nBulletTimer = 0;
			m_nShotAngle += BULLET_ANGLE_ADD;
		}
		// ショット終了
		if (SHOT_TIME + STOP_TIME <= m_nActionTimer)
		{
			m_bShot = false;
		}
	} else
	{
		// ショットを撃っていないときに移動する
		m_vPos.y += MOVE_SPEED;
	}

	// 下方向にエリアアウトしたら敵を消す
	AreaOutBottomProc();

	cEnemyBase::Update();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cEnmSwimmingFloat::Finalize(void)
{
	cEnemyBase::Finalize();

	return this;
}