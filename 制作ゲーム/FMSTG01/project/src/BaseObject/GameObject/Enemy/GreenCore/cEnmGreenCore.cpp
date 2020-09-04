/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmGreenCore.cpp											*/
/*  @brief		:	グリーンコアの敵クラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/31													*/
/*																				*/
/*==============================================================================*/

#include "cEnmGreenCore.h"
#include "..\..\..\..\cGame.h"
#include "..\..\Bullet\cBulletManager.h"
#include "..\..\Bullet\AngleBullet\cAngleBullet.h"
#include "..\..\Effect\cEffectManager.h"
#include "..\..\..\..\Utility\utility.h"

//==========================================================================================
// 定数
//==========================================================================================
const float cEnmGreenCore::HIT_RANGE = 24.0f;

const float cEnmGreenCore::MOVE_SPEED = 4.0f;
const float cEnmGreenCore::ROTATE_SPEED = 3.0f;

const float cEnmGreenCore::BULLET_SPEED = 7.0f;
const float cEnmGreenCore::BULLET_ANGLE_INTERVAL = 15.0f;

//==========================================================================================
// コンストラクタ
//==========================================================================================
cEnmGreenCore::cEnmGreenCore(IBaseObject * parent)
	: cEnemyBase(parent, "EnmGreenCore", "data\\graphic\\enemy_05.png"),
	m_nBulletTimer(0),
	m_vPosUp(0.0f,0.0f),
	m_nMoveTimer(0),
	m_eAiNo(AI_LEFT_APPER)
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cEnmGreenCore::~cEnmGreenCore(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cEnmGreenCore::Initialize(void)
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
void cEnmGreenCore::Update(void)
{
	m_fAngle += ROTATE_SPEED;

	m_nMoveTimer++;

	if (m_eAiNo == AI_LEFT_APPER)
	{
		m_vPosUp.x = abs(sin(DEG_TO_RAD(m_nMoveTimer))* MOVE_SPEED);
		m_vPosUp.y = abs(cos(DEG_TO_RAD(m_nMoveTimer))* MOVE_SPEED);
	} else
	{
		m_vPosUp.x = -abs(sin(DEG_TO_RAD(m_nMoveTimer))* MOVE_SPEED);
		m_vPosUp.y = abs(cos(DEG_TO_RAD(m_nMoveTimer))* MOVE_SPEED);
	}
	m_vPos.x += m_vPosUp.x;
	m_vPos.y += m_vPosUp.y;


	m_nBulletTimer++;
	if (m_nBulletTimer >= SHOOT_INTERVAL)
	{
		// nWay弾生成
		cBulletManager::GetInstance().CreateNWayBullet(m_vPos, HIT_ENEMY, BULLET_SPEED, BULLET_NUM, BULLET_ANGLE_INTERVAL, 0, BULLET_COLOR);
		m_nBulletTimer = 0;
	}

	// 下方向にエリアアウトしたら敵を消す
	AreaOutBottomProc();

	cEnemyBase::Update();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cEnmGreenCore::Finalize(void)
{
	cEnemyBase::Finalize();

	return this;
}