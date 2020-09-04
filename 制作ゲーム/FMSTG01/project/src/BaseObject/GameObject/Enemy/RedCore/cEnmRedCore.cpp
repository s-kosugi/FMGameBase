/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmRedCore.cpp												*/
/*  @brief		:	レッドコアの敵クラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/01/31													*/
/*																				*/
/*==============================================================================*/

#include "cEnmRedCore.h"
#include "..\..\..\..\cGame.h"
#include "..\..\Bullet\cBulletManager.h"
#include "..\..\Bullet\AngleBullet\cAngleBullet.h"
#include "..\..\Effect\cEffectManager.h"

//==========================================================================================
// 定数
//==========================================================================================
const float cEnmRedCore::HIT_RANGE = 24.0f;

const float cEnmRedCore::MOVE_SPEED = 1.0f;
const float cEnmRedCore::ROTATE_SPEED = 3.0f;

const float cEnmRedCore::BULLET_SPEED = 5.0f;
const float cEnmRedCore::BULLET_ANGLE_INTERVAL = 30.0f;

//==========================================================================================
// コンストラクタ
//==========================================================================================
cEnmRedCore::cEnmRedCore(IBaseObject * parent)
	: cEnemyBase(parent, "EnmWhiteCore", "data\\graphic\\enemy_04.png"),
	m_nBulletTimer ( 0 )
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cEnmRedCore::~cEnmRedCore(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cEnmRedCore::Initialize(void)
{
	cGame game = cGame::GetInstance();

	m_eHitCate = HIT_ENEMY;
	m_fHitRange = HIT_RANGE;
	m_nHp = DEF_HP;
	m_nAtk = DEF_ATK;
	m_nScore = DEF_SCORE;


	SetPriority(PRIORITY);

	cEnemyBase::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cEnmRedCore::Update(void)
{
	m_fAngle += ROTATE_SPEED;
	m_vPos.y += MOVE_SPEED;


	m_nBulletTimer++;
	if (m_nBulletTimer >= SHOOT_INTERVAL)
	{
		// nWay弾生成
		cBulletManager::GetInstance().CreateNWayBullet(m_vPos,HIT_ENEMY,BULLET_SPEED,BULLET_NUM, BULLET_ANGLE_INTERVAL,0,BULLET_COLOR);
		m_nBulletTimer = 0;
	}

	// 下方向にエリアアウトしたら敵を消す
	AreaOutBottomProc();

	cEnemyBase::Update();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cEnmRedCore::Finalize(void)
{
	cEnemyBase::Finalize();

	return this;
}