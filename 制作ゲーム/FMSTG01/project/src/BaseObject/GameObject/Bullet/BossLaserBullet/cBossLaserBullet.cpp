/*==============================================================================*/
/*																				*/
/*	@file title	:	cBossLaserBullet.cpp										*/
/*  @brief		:	ボスレーザークラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/01/24													*/
/*																				*/
/*==============================================================================*/

#include "cBossLaserBullet.h"
#include "..\..\..\..\cGame.h"
#include "..\..\..\..\Utility\utility.h"
#include "..\..\Effect\cEffectManager.h"
#include "..\..\Effect\cEffectObject.h"
#include "..\cBulletManager.h"

//==========================================================================================
// 定数
//==========================================================================================
const float cBossLaserBullet::HIT_RANGE = 60.0f;	// 当たり判定
const int	cBossLaserBullet::DEFAULT_ATK = 400;	// 標準攻撃力
const int	cBossLaserBullet::PRIORITY = 300;		// 表示優先
const short cBossLaserBullet::DEFAULT_LIFETIME = 200; // 標準生存時間

//==========================================================================================
// コンストラクタ
//==========================================================================================
cBossLaserBullet::cBossLaserBullet(IBaseObject * parent)
	: cBulletBase(parent, "BossLaserBullet", "data\\graphic\\Bullet_01.png"),
	m_nLifeCounter(DEFAULT_LIFETIME)
{
}

cBossLaserBullet::cBossLaserBullet(IBaseObject * parent, const std::string & name, const std::string & filename)
	: cBulletBase(parent, "BossLaserBullet", filename),
	m_nLifeCounter(DEFAULT_LIFETIME)
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cBossLaserBullet::~cBossLaserBullet(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cBossLaserBullet::Initialize(void)
{
	cGame game = cGame::GetInstance();

	m_fHitRange = HIT_RANGE;

	m_nHp = 0;
	m_nAtk = DEFAULT_ATK;

	// ボスレーザーはエフェクトとして描画するためスプライトは表示しない
	m_bVisible = false;

	SetPriority(PRIORITY);

	cBulletBase::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cBossLaserBullet::Update(void)
{
	// 当たった弾は消えずに当たり判定を残す
	m_eState = STATE_NORMAL;

	// エリアアウトをしたら弾を消す
	//AreaOutAllProc();

	m_nLifeCounter--;

	if (m_nLifeCounter <= 0)
	{
		DeleteObject();
	}

	cBulletBase::Update();
}
//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cBossLaserBullet::Finalize(void)
{
	cBulletBase::Finalize();

	return this;
}

//==========================================================================================
// 発射角度のセット
// angle : 度数法の角度,0度が真下
//==========================================================================================
void cBossLaserBullet::SetShootAngle(float angle)
{
	angle += 90.0f;
	//m_vPosUp.x = m_fSpeed * cos(DEG_TO_RAD(angle));
	//m_vPosUp.y = m_fSpeed * sin(DEG_TO_RAD(angle));
}
//==========================================================================================
// レーザー配置の開始
// vAngle : レーザーの進行方向
//==========================================================================================
void cBossLaserBullet::StartConfig(float fAngle)
{
	cEffectObject* ef = cEffectManager::GetInstance().Create(EFFECT_BOSSLASER, m_vPos);
	ef->SetAngle({ 0.0f,0.0f,DEG_TO_RAD(fAngle) });

	cVector2 pos = m_vPos;
	fAngle += 90.0f;
	while (1)
	{
		pos.x += HIT_RANGE * cos(DEG_TO_RAD(fAngle));
		pos.y += HIT_RANGE * sin(DEG_TO_RAD(fAngle));


		// 当たり判定が画面範囲内ならレーザーを作り続ける
		if (pos.x + HIT_RANGE / 2 > cGame::GetInstance().GetPlayArea().left &&
			pos.y + HIT_RANGE / 2 > cGame::GetInstance().GetPlayArea().top &&
			pos.x - HIT_RANGE / 2 < cGame::GetInstance().GetPlayArea().right &&
			pos.y - HIT_RANGE / 2 < cGame::GetInstance().GetPlayArea().bottom)
		{
			cBulletManager::GetInstance().Create(BT_BOSS_LASER, pos, HIT_ENEMY, 0.0f, m_nColor, this->m_sFileName);
		} else
		{
			break;
		}
	}
}