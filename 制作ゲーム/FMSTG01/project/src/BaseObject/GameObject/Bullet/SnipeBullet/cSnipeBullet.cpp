/*==============================================================================*/
/*																				*/
/*	@file title	:	cSnipeBullet.cpp											*/
/*  @brief		:	ホーミング弾クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/21													*/
/*																				*/
/*==============================================================================*/

#include "cSnipeBullet.h"
#include "..\..\..\..\cGame.h"
#include "..\..\..\..\Utility\utility.h"
#include "..\..\Player\cPlayer.h"
#include "..\..\Enemy\cEnemyManager.h"

//==========================================================================================
// 定数
//==========================================================================================
const float cSnipeBullet::HIT_RANGE = 6.0f;		// 当たり判定の大きさ
const int	cSnipeBullet::PRIORITY = 300;		// 表示優先度
const int	cSnipeBullet::DEFAULT_ATK = 50;		// デフォルト攻撃力

//==========================================================================================
// コンストラクタ
//==========================================================================================
cSnipeBullet::cSnipeBullet(IBaseObject * parent)
	: cBulletBase(parent, "SnipeBullet", "data\\graphic\\Bullet_01.png")
{
}

cSnipeBullet::cSnipeBullet(IBaseObject * parent, const std::string & name, const std::string & filename)
	: cBulletBase(parent, "SnipeBullet", filename)
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cSnipeBullet::~cSnipeBullet(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cSnipeBullet::Initialize(void)
{
	m_fHitRange = HIT_RANGE;

	m_nHp = 0;
	m_nAtk = DEFAULT_ATK;

	m_vPosUp.x = 0;
	m_vPosUp.y = 0;

	if (m_eHitCate == HIT_ENEMY)
	{
		cSpriteObject* obj = nullptr;
		// 敵弾の場合はプレイヤーをターゲットにする
		if (m_eHitCate == HIT_ENEMY) obj = (cSpriteObject*)m_pParentObject->FindSibling("Player");

		if( obj != nullptr ) CalcTargetVector(obj->GetPos());
	}

	SetPriority(PRIORITY);

	cBulletBase::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cSnipeBullet::Update(void)
{
	// 弾が当たった時の共通処理
	HitProc();

	cBulletBase::Update();

	// エリアアウトをしたら弾を消す
	AreaOutAllProc();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cSnipeBullet::Finalize(void)
{
	cBulletBase::Finalize();

	return this;
}
//==========================================================================================
// 追尾対象へ移動するベクトルを求める
// tPos : 追尾対象の座標
//==========================================================================================
void cSnipeBullet::CalcTargetVector(const cVector2 & tPos)
{
	float dist = m_vPos.CalsTwoPointDist(tPos);
	if (dist)
	{
		// 距離から自分の移動速度倍率を掛ける
		m_vPosUp.x = (tPos.x - m_vPos.x) / dist * m_fSpeed;
		m_vPosUp.y = (tPos.y - m_vPos.y) / dist * m_fSpeed;
	} else
	{
		// 重なっているときは真下へ移動する
		m_vPosUp.x = 0;
		m_vPosUp.y = m_fSpeed;
	}
}

//==========================================================================================
// 発射角度のセット
// angle : 度数法の角度,0度が真下
//==========================================================================================
void cSnipeBullet::SetShootAngle(float angle)
{
	angle += 90.0f;
	m_vPosUp.x = m_fSpeed * cos(DEG_TO_RAD(angle));
	m_vPosUp.y = m_fSpeed * sin(DEG_TO_RAD(angle));
}