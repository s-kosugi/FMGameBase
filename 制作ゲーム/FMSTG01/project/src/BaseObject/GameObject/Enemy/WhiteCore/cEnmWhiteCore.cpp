/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmWhiteCore.cpp											*/
/*  @brief		:	ホワイトコアの敵クラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "cEnmWhiteCore.h"
#include "..\..\..\..\cGame.h"
#include "..\..\Bullet\cBulletManager.h"
#include "..\..\Bullet\AngleBullet\cAngleBullet.h"
#include "..\..\Effect\cEffectManager.h"

//==========================================================================================
// 定数
//==========================================================================================
const float cEnmWhiteCore::HIT_RANGE = 24.0f;

const float cEnmWhiteCore::MOVE_SPEED = 2.0f;
const float cEnmWhiteCore::ROTATE_SPEED = 3.0f;

const float cEnmWhiteCore::BULLET_SPEED = 4.5f;
const float cEnmWhiteCore::BULLET_ANGLE_INTERVAL = 45.0f;

//==========================================================================================
// コンストラクタ
//==========================================================================================
cEnmWhiteCore::cEnmWhiteCore(IBaseObject * parent)
	: cEnemyBase(parent, "EnmWhiteCore", "data\\graphic\\enemy_01.png"),
	m_nBulletTimer ( 0 )
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cEnmWhiteCore::~cEnmWhiteCore(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cEnmWhiteCore::Initialize(void)
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
void cEnmWhiteCore::Update(void)
{
	m_fAngle += ROTATE_SPEED;
	m_vPos.y += MOVE_SPEED;


	m_nBulletTimer++;
	if (m_nBulletTimer >= SHOOT_INTERVAL)
	{
		// nWay弾生成
		if(m_nBulletTimer == SHOOT_INTERVAL + SHOOT_WAIT)
			cBulletManager::GetInstance().CreateNWayBullet(m_vPos,HIT_ENEMY,BULLET_SPEED,BULLET_NUM, BULLET_ANGLE_INTERVAL,0,BULLET_COLOR);

		if (m_nBulletTimer >= SHOOT_WAIT + SHOOT_INTERVAL)
		{
			m_nBulletTimer = 0;
		}
		// 停止させる
		m_vPos.y -= MOVE_SPEED;
	}

	// 下方向にエリアアウトしたら敵を消す
	AreaOutBottomProc();

	cEnemyBase::Update();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cEnmWhiteCore::Finalize(void)
{
	cEnemyBase::Finalize();

	return this;
}