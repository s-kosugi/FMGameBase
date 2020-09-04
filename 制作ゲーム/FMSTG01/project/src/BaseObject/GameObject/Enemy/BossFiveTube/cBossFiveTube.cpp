/*==============================================================================*/
/*																				*/
/*	@file title	:	cBossFiveTube.cpp											*/
/*  @brief		:	ボス戦艦の敵クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/19													*/
/*																				*/
/*==============================================================================*/

#include "cBossFiveTube.h"
#include "..\..\Bullet\cBulletManager.h"
#include "..\..\Bullet\AngleBullet\cAngleBullet.h"
#include "..\..\Bullet\BossLaserBullet\cBossLaserBullet.h"
#include "..\..\Effect\cEffectManager.h"
#include "BossLeftBattery\cBossLeftBattery.h"
#include "BossRightBattery\cBossRightBattery.h"
#include "..\cEnemyManager.h"
#include "..\..\..\..\cGame.h"
#include "..\..\..\..\SoundCtrl\cSoundCtrl.h"
#include "..\..\UI\cUIManager.h"
#include "..\..\..\..\ScoreManager\cScoreManager.h"

#include "..\..\..\..\Utility\utility.h"

//==========================================================================================
// コンストラクタ
//==========================================================================================
cBossFiveTube::cBossFiveTube(IBaseObject * parent)
	: cEnemyBase(parent, "BossFiveTube", "data\\graphic\\boss_01.png"),
	m_eActionState(STATE_APPEA),
	m_nActionTimer( 0 ),
	m_nBulletTimer ( 0 ),
	m_nMoveTimer( 0 ),
	m_nDeadTimer( 0 ),
	m_nTimeBonusCount( 0 ),
	m_nMoveUpDownTimer( 0 ),
	m_nAttackType(0)
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cBossFiveTube::~cBossFiveTube(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cBossFiveTube::Initialize(void)
{

	m_eHitCate = HIT_ENEMY;
	m_fHitRange = HIT_RANGE;
	m_nHp = DEF_HP;
	m_nAtk = DEF_ATK;
	m_nScore = DEF_SCORE;

	m_vPosUp.y = APPEA_INIT_SPEED;

	cBossRightBattery* rBat = (cBossRightBattery*)cEnemyManager::GetInstance().Create(ENM_ID_BOSS_FIVETUBE_RIGHTBAT);
	if (rBat != nullptr)	rBat->SetFollowObject(this);
	cBossLeftBattery* lBat = (cBossLeftBattery*)cEnemyManager::GetInstance().Create(ENM_ID_BOSS_FIVETUBE_LEFTBAT);
	if (lBat != nullptr)	lBat->SetFollowObject(this);

	
	SetPriority(PRIORITY);

	cEnemyBase::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cBossFiveTube::Update(void)
{

	// 状態別行動
	switch (m_eActionState)
	{
	case STATE_APPEA:
		Appea();
		break;

	case STATE_MOVE:
		Move();
		break;

	case STATE_WAIT:
		Wait();
		break;

	case STATE_ATTACK:
		Attack();
		break;

	case STATE_SIDEATTACK:
		SideAttack();
		break;

	case STATE_AREAOUT:
		AreaOut();
		break;

	case STATE_AREAOUTATTACK:
		AreaOutAttack();
		break;

	case STATE_AREAOUTAPPEAR:
		AreaOutAppear();
		break;

	case STATE_MOVEATTACK:
		MoveAttack();
		break;

	case STATE_CHARGE:
		Charge();
		break;

	case STATE_LASER:
		Laser();
		break;
	}

	// タイムボーナス処理
	ProcTimeBonus();

	cEnemyBase::Update();

	// 死亡時の演出
	Dead();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cBossFiveTube::Finalize(void)
{
	cEnemyBase::Finalize();

	return this;
}

//==========================================================================================
// 出現時
//==========================================================================================
void cBossFiveTube::Appea(void)
{
	m_vPosUp.y += AREAIN_BREAK;
	if (m_vPosUp.y <= APPEA_BREAK_SPEED_LIMIT) m_vPosUp.y = APPEA_BREAK_SPEED_LIMIT;


	if (m_vPos.y <= APPEA_NEXTACT_LINE && m_vPosUp.y < 0)
	{
		m_nActionTimer = 0;
		m_vPosUp.x = 0.0f;
		m_vPosUp.y = 0.0f;
		m_eActionState = STATE_MOVE;
	}

}
//==========================================================================================
// 移動
//==========================================================================================
void cBossFiveTube::Move(void)
{
	m_vPosUp.x = cos( DEG_TO_RAD(m_nMoveTimer*MOVE_TIMER_RATE) ) * MOVE_SPEED_RATE;
	m_vPosUp.y = cos(DEG_TO_RAD(m_nMoveUpDownTimer*MOVE_UPDOWNTIMER_RATE)) * MOVE_UPDOWNSPEED_RATE;
	m_nMoveTimer++;
	m_nMoveUpDownTimer++;

	m_nActionTimer++;
	if(m_nActionTimer >= MOVE_NEXTACT_TIME)
	{
		m_vPosUp.x = 0;
		m_vPosUp.y = 0;
		//m_eActionState = STATE_MOVEATTACK;
		// 行動選択
		AttackChoice();
		m_nActionTimer = 0;
	}
}
//==========================================================================================
// 待機
//==========================================================================================
void cBossFiveTube::Wait(void)
{
	m_nActionTimer++;
	if( m_nActionTimer >= WAIT_NEXTACT_TIME)
	{
		m_eActionState = STATE_ATTACK;
		m_nActionTimer = 0;
	}
}
//==========================================================================================
// 攻撃
//==========================================================================================
void cBossFiveTube::Attack(void)
{

	m_nBulletTimer++;
	if (m_nBulletTimer >= SHOOT_INTERVAL)
	{
		// nWay弾生成
		cBulletManager::GetInstance().CreateNWayBullet(m_vPos,HIT_ENEMY,BULLET_SPEED,BULLET_NUM, BULLET_ANGLE_INTERVAL,0,BULLET_COLOR);
		m_nBulletTimer = 0;
	}

	m_nActionTimer++;
	if( m_nActionTimer >= ATTACK_NEXTACT_TIME)
	{
		m_eActionState = STATE_MOVE;
		m_nActionTimer = 0;
	}
}
//==========================================================================================
// サイド攻撃
//==========================================================================================
void cBossFiveTube::SideAttack(void)
{
	m_nBulletTimer++;
	if (m_nBulletTimer >= SHOOT_INTERVAL)
	{
		// nWay弾生成
		cVector2 bulpos = m_vPos;
		bulpos.x += MIS_POS_X;
		bulpos.y += MIS_POS_Y;
		cBulletManager::GetInstance().CreateNWayBullet(bulpos, HIT_ENEMY, BULLET_SPEED, SIDEATTACK_BULLET_NUM, SIDEATTACK_BULLET_ANGLE_INTERVAL, 0, SIDEATTACK_BULLET_COLOR);

		bulpos = m_vPos;
		bulpos.x += -MIS_POS_X;
		bulpos.y += MIS_POS_Y;
		cBulletManager::GetInstance().CreateNWayBullet(bulpos, HIT_ENEMY, BULLET_SPEED, SIDEATTACK_BULLET_NUM, SIDEATTACK_BULLET_ANGLE_INTERVAL, 0, SIDEATTACK_BULLET_COLOR);
		m_nBulletTimer = 0;
	}

	m_nActionTimer++;
	if (m_nActionTimer >= ATTACK_NEXTACT_TIME)
	{
		m_eActionState = STATE_MOVE;
		m_nActionTimer = 0;
	}
}
//==========================================================================================
// エリアアウト
//==========================================================================================
void cBossFiveTube::AreaOut(void)
{
	m_nActionTimer++;

	m_vPosUp.x = cos(DEG_TO_RAD(m_nMoveTimer*MOVE_TIMER_RATE)) * MOVE_SPEED_RATE;
	m_vPosUp.y -= AREAOUT_SPEED;

	m_nMoveTimer++;
	if (m_vPos.y <= AREAOUT_LINE)
	{
		m_vPosUp.x = m_vPosUp.y = 0.0f;
		m_nActionTimer = 0;
		m_eActionState = STATE_AREAOUTATTACK;
	}
}
//==========================================================================================
// エリアアウト時攻撃
//==========================================================================================
void cBossFiveTube::AreaOutAttack(void)
{
	m_nActionTimer++;

	if (m_nActionTimer % AREAOUT_ATTACK_INTERVAL == 0)
	{
		for (int i = 0; i < AREAOUT_BULLET_NUM; i++)
		{
			cVector2 pos = { (float)cGame::GetInstance().Random(5, cGame::GetInstance().GetPlayAreaWidth() - 5),-5.0f};

			cAngleBullet* bul = (cAngleBullet*)cBulletManager::GetInstance().Create(BT_ANGLE, pos, HIT_ENEMY, AREAOUT_BULLET_SPEED, COLOR_PURPLE, "data\\graphic\\Bullet_03.png");
			bul->SetShootAngle(0.0f);
		}
		cSoundCtrl::GetInstance().Play(SOUND_SHOOT);
	}

	if (m_nActionTimer >= AREAOUT_ACTION_TIME)
	{
		m_nActionTimer = 0;
		m_eActionState = STATE_AREAOUTAPPEAR;
		m_vPosUp.y = AREAIN_SPEED;
	}
}
//==========================================================================================
// エリアアウトから出現
//==========================================================================================
void cBossFiveTube::AreaOutAppear(void)
{
	m_nActionTimer++;

	m_vPosUp.x = cos(DEG_TO_RAD(m_nMoveTimer*MOVE_TIMER_RATE)) * MOVE_SPEED_RATE;
	m_vPosUp.y += AREAIN_BREAK;
	if (m_vPosUp.y <= AREAIN_BACKSPEED_LIMIT) m_vPosUp.y = AREAIN_BACKSPEED_LIMIT;

	m_nMoveTimer++;

	if (m_vPos.y <= APPEA_NEXTACT_LINE && m_vPosUp.y < 0)
	{
		m_nActionTimer = 0;
		m_vPosUp.x = 0.0f;
		m_nMoveUpDownTimer = 0;
		m_eActionState = STATE_MOVE;
	}
}
//==========================================================================================
// 移動攻撃
//==========================================================================================
void cBossFiveTube::MoveAttack(void)
{
	m_nActionTimer++;

	m_vPosUp.x = cos(DEG_TO_RAD(m_nMoveTimer*MOVE_TIMER_RATE)) * MOVE_SPEED_RATE;
	m_nMoveTimer++;

	if (m_nActionTimer % MOVEATTACK_BUL_INTERVAL == 0)
	{
		// nWay弾生成
		cVector2 bulpos = m_vPos;
		bulpos.x += MIS_POS_X;
		bulpos.y += MIS_POS_Y;
		cBulletManager::GetInstance().CreateNWayBullet(bulpos, HIT_ENEMY, BULLET_SPEED, MOVEATTACK_BUL_NUM, MOVEATTACK_BUL_ANGLE, 0, SIDEATTACK_BULLET_COLOR);

		bulpos = m_vPos;
		bulpos.x += -MIS_POS_X;
		bulpos.y += MIS_POS_Y;
		cBulletManager::GetInstance().CreateNWayBullet(bulpos, HIT_ENEMY, BULLET_SPEED, MOVEATTACK_BUL_NUM, MOVEATTACK_BUL_ANGLE, 0, SIDEATTACK_BULLET_COLOR);
		m_nBulletTimer = 0;
	}

	if (m_nActionTimer >= MOVEATTACK_TIME)
	{
		m_vPosUp.x = 0;
		m_nActionTimer = 0;
		m_eActionState = STATE_MOVE;
	}
}
//==========================================================================================
// チャージ
//==========================================================================================
void cBossFiveTube::Charge(void)
{

	if (m_nActionTimer == 0)
	{
		cSoundCtrl::GetInstance().Play(SOUND_BOSSCHARGE);
	}

	m_nActionTimer++;

	if( m_nActionTimer % 3 == 0 )
	{
		cEffectObject* ef = cEffectManager::GetInstance().Create(EFFECT_CHARGE,m_vPos);
		ef->SetDrawColor(0xffff7777);
	}

	if (m_nActionTimer >= CHARGE_TIME)
	{
		m_eActionState = STATE_LASER;
		m_nActionTimer = 0;
	}
}
//==========================================================================================
// レーザー攻撃
//==========================================================================================
void cBossFiveTube::Laser(void)
{
	if(m_nActionTimer == 0 )
	{
		cVector2 pos = m_vPos;

		// １本目レーザー
		pos.x += 45.0f;
		cBossLaserBullet* bul = (cBossLaserBullet*)cBulletManager::GetInstance().Create(BT_BOSS_LASER, pos,HIT_ENEMY,0.0f);
		bul->StartConfig(0.0f);

		// 2本目レーザー
		bul = (cBossLaserBullet*)cBulletManager::GetInstance().Create(BT_BOSS_LASER, pos, HIT_ENEMY, 0.0f);
		bul->StartConfig(-15.0f);

		// 3本目レーザー
		pos = m_vPos;
		pos.x -= 45.0f;
		bul = (cBossLaserBullet*)cBulletManager::GetInstance().Create(BT_BOSS_LASER, pos, HIT_ENEMY, 0.0f);
		bul->StartConfig(0.0f);

		// 4本目レーザー
		bul = (cBossLaserBullet*)cBulletManager::GetInstance().Create(BT_BOSS_LASER, pos, HIT_ENEMY, 0.0f);
		bul->StartConfig(15.0f);

		cSoundCtrl::GetInstance().Play(SOUND_BOSSBEAM);
	}

	m_nActionTimer++;
	
	if (m_nActionTimer >= LASER_TIME)
	{
		m_eActionState = STATE_MOVE;
		m_nActionTimer = 0;
	}
}
//==========================================================================================
// 攻撃選択処理
//==========================================================================================
void cBossFiveTube::AttackChoice(void)
{
	// 基本的には順繰りで行動させる
	if (m_nHp >= PATTERN_CHANGE_BORDER)
	{
		if (m_nAttackType == 0)
		{
			m_eActionState = STATE_WAIT;
			m_nAttackType++;
		}
		else
		{
			m_eActionState = STATE_SIDEATTACK;
			m_nAttackType= 0;
		}
	}
	else
	{
		// HPが少ないときは強い攻撃パターンになる
		if( m_nAttackType == 0)
		{
			m_eActionState = STATE_AREAOUT;
			m_nAttackType++;
		}
		else if( m_nAttackType == 1)
		{
			m_eActionState = STATE_MOVEATTACK;
			m_nAttackType++;
		}
		else
		{
			m_eActionState = STATE_CHARGE;
			m_nAttackType=0;
		}
	}
}
//==========================================================================================
// タイムボーナス処理
//==========================================================================================
void cBossFiveTube::ProcTimeBonus(void)
{
	if (m_eState != STATE_DEAD)
	{
		m_nTimeBonusCount++;
		if (m_nTimeBonusCount >= TIME_BONUS_LOWER_LIMIT) m_nTimeBonusCount = TIME_BONUS_LOWER_LIMIT;
	}
}
//==========================================================================================
// 死亡時処理
//==========================================================================================
void cBossFiveTube::Dead(void)
{
	if (m_eState == STATE_DEAD)
	{
		m_vPosUp.x = m_vPosUp.y = 0;
		m_eActionState = STATE_STOP;
		// Updateで死んだ状態を一旦もとに戻してエフェクト再生
		m_eObjectState = OBJECT_STATE_ACTIVE;

		if (m_nDeadTimer % BOM_INTERVAL == 0)
		{
			cVector2 vec = m_vPos;
			vec.x += cGame::Random(-GetSpriteSize().x / 2, GetSpriteSize().x / 2);
			vec.y += cGame::Random(-GetSpriteSize().y / 2, GetSpriteSize().y / 2);
			cEffectManager::GetInstance().Create(EFFECT_BOM, vec);
		}
		if (m_nDeadTimer == BIG_BOM_TIME)
		{
			cEffectManager::GetInstance().Create(EFFECT_BIGBOM, m_vPos);
		}
		m_nDeadTimer++;
		if (DEAD_TIME <= m_nDeadTimer)
		{
			cSoundCtrl::GetInstance().Play(SOUND_BIGBOM);
			m_eObjectState = OBJECT_STATE_DEAD;

			// ゲームクリア文字の表示
			cUIManager::GetInstance().Create(UI_GAMECLEAR_FONT, cVector2( 0.0f,0.0f ));


			// タイムボーナスの計算
			int bonus = 0;
			if (m_nTimeBonusCount <= TIME_BONUS_HIGHER_LIMIT)
			{
				bonus = TIME_BONUS_MAXSCORE;
			}
			else if (m_nTimeBonusCount >= TIME_BONUS_LOWER_LIMIT)
			{
				bonus = 0;
			}
			else
			{
				bonus = (int)(((float)m_nTimeBonusCount) / (TIME_BONUS_LOWER_LIMIT - TIME_BONUS_HIGHER_LIMIT) * TIME_BONUS_MAXSCORE);
			}
			cScoreManager::GetInstance().SetTimeBonus(bonus);
		}
	}
}
