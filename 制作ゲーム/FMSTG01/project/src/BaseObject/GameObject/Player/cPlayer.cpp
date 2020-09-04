/*==============================================================================*/
/*																				*/
/*	@file title	:	cPlayer.cpp													*/
/*  @brief		:	プレイヤークラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "cPlayer.h"
#include "..\..\..\Input\cControllerManager.h"
#include "..\..\..\cGame.h"
#include "..\..\..\SoundCtrl\cSoundCtrl.h"
#include "..\Bullet\cBulletManager.h"
#include "..\Bullet\AngleBullet\cAngleBullet.h"
#include "..\Bullet\HomingBullet\HomingLaserTale\cHomingLaserTale.h"
#include "..\Effect\cEffectManager.h"
#include "..\Effect\SmokeEffect\cSmokeEffect.h"

#include "..\SpEffect\cSpEffectManager.h"
#include "..\SpEffect\TargetEffect\cTargetEffect.h"

#include "..\..\..\SceneManager\cSceneManager.h"

//==========================================================================================
// コンストラクタ
//==========================================================================================
cPlayer::cPlayer(IBaseObject * parent)
	: cHitObject(parent, "Player", "data\\graphic\\player_01.png"),
	m_nFlashTimer( 0 ),
	m_nDeadTimer( 0 ),
	m_nSmokeTimer( 0 ),
	m_nLaserTimer( 0 ),
	m_nShotCoolTime( 0 ),
	m_nBomNum( DEFAULT_BOM_NUM ),
	m_vPosUp(0.0f,0.0f),
	m_bAppear(true)
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cPlayer::~cPlayer(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cPlayer::Initialize(void)
{
	m_vPos = { START_POS_X,START_POS_Y };
	SetPriority(PRIORITY);
	SetAnimation(0,0, SIZE_X, SIZE_Y, ANIM_NUM, ANIM_TIME);
	m_eHitCate = HIT_PLAYER;
	m_fHitRange = HIT_RANGE;
	m_nFlashTimer = 0;
	m_nLaserTimer = 0;
	m_nShotCoolTime = 0;
	m_nBomNum = DEFAULT_BOM_NUM;
	m_nHp = MAX_HP;
	m_nMaxHp = MAX_HP;
	m_vPosUp.y = -6.0f;

	cHitObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cPlayer::Update(void)
{
	if(m_nShotCoolTime > 0 ) m_nShotCoolTime--;

	if (m_bAppear)
	{
		// 出現演出時
		m_vPosUp.y *= 0.97f;
		m_vPos.y += m_vPosUp.y;
		if (m_vPosUp.y > -0.08f)
		{
			m_bAppear = false;
		}
	}
	else
	{
		//. ゲームプレイ時

		switch (m_eState)
		{
		case STATE_NORMAL:
			Normal();
			break;
		case STATE_HIT:
			Hit();
			break;
		case STATE_FLASH:
			Flash();
			break;
		case STATE_DEAD:
			Dead();
			break;
		}
		// 範囲外処理
		ProcAreaOut();
	}


	cHitObject::Update();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cPlayer::Finalize(void)
{
	cHitObject::Finalize();

	return this;
}
//==========================================================================================
// 通常状態の処理
//==========================================================================================
void cPlayer::Normal(void)
{
	OperationKey();
	AppeaSmoke();
	ShootLaser();
}

//==========================================================================================
// 攻撃があたった状態の処理
//==========================================================================================
void cPlayer::Hit(void)
{
	OperationKey();
	ShootLaser();

	if (m_nHp <= 0)
	{
		// キャラクターを死亡状態にする
		m_eState = STATE_DEAD;
		cEffectManager::GetInstance().Create(EFFECT_BOM,m_vPos);
		m_bVisible = false;
		m_nDeadTimer = DEAD_WAIT_TIME;
		m_nHp = 0;
	}
	else
	{
		// 点滅状態に移行する
		m_nFlashTimer = FLASH_MAX_TIME;
		m_eState = STATE_FLASH;
		// 画面を点滅させる
		cSpEffectManager::GetInstance().Create(SPEFFECT_SCREENFLASH,cGame::GetInstance().GetPlayAreaCenter());
		cSoundCtrl::GetInstance().Play(SOUND_BOM);
	}
}
//==========================================================================================
// フラッシュ状態時の処理
//==========================================================================================
void cPlayer::Flash(void)
{
	OperationKey();
	AppeaSmoke();
	ShootLaser();

	// 点滅処理
	if (m_nFlashTimer % (FLASH_INTERVAL*2) <= FLASH_INTERVAL) {
		SetBlendMode(DX_BLENDMODE_ADD);
	} else
	{
		SetBlendMode(DX_BLENDMODE_ALPHA);
	}

	// 無敵状態の解除
	if (--m_nFlashTimer <= 0)
	{
		SetBlendMode(DX_BLENDMODE_ALPHA);
		m_eState = STATE_NORMAL;
	}
}

//==========================================================================================
// 死んだ状態の処理
//==========================================================================================
void cPlayer::Dead(void)
{
	m_nDeadTimer--;
	if (m_nDeadTimer <= 0)
	{
		cSceneManager::GetInstance().ChangeScene(SCENE_ID_TITLE);
	}
}
//==========================================================================================
// キー操作処理
//==========================================================================================
void cPlayer::OperationKey(void)
{
	if (cControllerManager::GetInstance().CheckButton(cControllerManager::KEY_RIGHT))
	{
		m_vPos.x += MOVE_SPEED;
	}
	if (cControllerManager::GetInstance().CheckButton(cControllerManager::KEY_LEFT))
	{
		m_vPos.x -= MOVE_SPEED;
	}
	if (cControllerManager::GetInstance().CheckButton(cControllerManager::KEY_UP))
	{
		m_vPos.y -= MOVE_SPEED;
	}
	if (cControllerManager::GetInstance().CheckButton(cControllerManager::KEY_DOWN))
	{
		m_vPos.y += MOVE_SPEED;
	}

	if (cControllerManager::GetInstance().CheckButton(cControllerManager::KEY_1))
	{
		// ショットが発射可能か
		if (m_nShotCoolTime <= 0)
		{
			for (int i = 0; i < BULLET_NUM; i++)
			{
				cVector2 vPos = m_vPos;
				vPos += SHOT_START_POS[i];
				cAngleBullet* bul = (cAngleBullet*)cBulletManager::GetInstance().Create(BT_ANGLE, vPos, HIT_PLAYER, BULLET_SPEED,BULLET_COLOR, "data\\graphic\\Bullet_03.png");
				// 真上に弾を打つ
				bul->SetShootAngle(180.0f);
			}
			// 左右にNway弾を出す
			cBulletManager::GetInstance().CreateNWayBullet(m_vPos, HIT_PLAYER, BULLET_SPEED, NWAY_BULLET_NUM,
				NWAY_BULLET_ANGLE_INTERVAL, 180.0f + NWAY_BULLET_START_ANGLE, BULLET_COLOR, BT_ANGLE, "data\\graphic\\Bullet_03.png");
			cBulletManager::GetInstance().CreateNWayBullet(m_vPos, HIT_PLAYER, BULLET_SPEED, NWAY_BULLET_NUM,
				NWAY_BULLET_ANGLE_INTERVAL, 180.0f - NWAY_BULLET_START_ANGLE, BULLET_COLOR, BT_ANGLE, "data\\graphic\\Bullet_03.png");
			m_nShotCoolTime = SHOT_INTERVAL;
			cSoundCtrl::GetInstance().Play(SOUND_SHOT);
		}
	}
	if (cControllerManager::GetInstance().CheckTriger(cControllerManager::KEY_2))
	{
		// ボムが使用可能かどうか
		if( m_nLaserTimer <= 0 && m_nBomNum > 0)
		{
			// レーザーを発射状態にする
			m_nLaserTimer = LASER_STATE_TIME;
			m_nBomNum --;
		}
	}
}

//==========================================================================================
// 範囲外処理
//==========================================================================================
void cPlayer::ProcAreaOut(void)
{
	if (m_vPos.x - SIZE_X / 2 < (float)cGame::GetInstance().GetPlayArea().left)
	{
		m_vPos.x = (float)SIZE_X / 2;
	}
	if (m_vPos.y - SIZE_Y / 2 < (float)cGame::GetInstance().GetPlayArea().top)
	{
		m_vPos.y = (float)SIZE_Y / 2;
	}
	if (m_vPos.x + SIZE_X / 2 >= (float)cGame::GetInstance().GetPlayArea().right)
	{
		m_vPos.x = (float)cGame::GetInstance().GetPlayArea().right - SIZE_X /2;
	}
	if (m_vPos.y + SIZE_Y / 2 >= (float)cGame::GetInstance().GetPlayArea().bottom)
	{
		m_vPos.y = (float)cGame::GetInstance().GetPlayArea().bottom - SIZE_Y / 2;
	}
}

//==========================================================================================
// 煙出現処理
//==========================================================================================
void cPlayer::AppeaSmoke(void)
{
	if (MAX_HP * SMOKE_START_RATE >= m_nHp)
	{
		m_nSmokeTimer--;
		if (m_nSmokeTimer <= 0)
		{
			m_nSmokeTimer = SMOKE_START_INTERVAL;
			cSmokeEffect* obj = (cSmokeEffect*)cEffectManager::GetInstance().Create(EFFECT_SMOKE, m_vPos);
			obj->SetDrawColor(SMOKE_COLOR);
			obj->SetFollowingObj(this);
		}
	}
}
//==========================================================================================
// レーザー発射処理
//==========================================================================================
void cPlayer::ShootLaser(void)
{
	if (m_nLaserTimer > 0)
	{
		if (m_nLaserTimer % LASER_SHOOT_INTERVAL == 0)
		{
			cVector2 vPos = m_vPos;
			cHomingLaserTale* bul = (cHomingLaserTale*)cBulletManager::GetInstance().Create(BT_HOMING_LASER_TALE, vPos, HIT_PLAYER, HOMING_BULLET_SPEED);

			cSoundCtrl::GetInstance().Play(SOUND_LASER);
			
			bul->SetDrawColor(HOMING_COLOR);
			bul->SetShootAngle((float)cGame::GetInstance().Random(-LASER_ANGLE_RANGE/2, LASER_ANGLE_RANGE/2));
			bul->SetRotLimit(HOMING_ROTATE);
			bul->SetLaserNum(HOMING_MAX_NUM);
			bul->SetNextPopTime(HOMING_NEXT_POPTIME);
			bul->SetAlwaysSearch(false);
			bul->SetAreaOutAdjust(LASER_AREAOUT_ADJUST);
			bul->SetAtk(LASER_ATK);
			cSpriteObject* obj = bul->SetRandomTarget();

			if (obj != nullptr && !cTargetEffect::CheckDupulication(obj))
			{
				// ターゲットサイトを出す
				cTargetEffect* pObj = (cTargetEffect*)cSpEffectManager::GetInstance().Create(SPEFFECT_TARGET, obj->GetPos());
				pObj->SetTargetObject( obj );
			}
		}
		m_nLaserTimer --;
	}
}
