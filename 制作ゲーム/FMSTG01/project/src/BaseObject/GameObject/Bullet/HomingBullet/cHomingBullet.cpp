/*==============================================================================*/
/*																				*/
/*	@file title	:	cHomingBullet.cpp											*/
/*  @brief		:	ホーミング弾クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/21													*/
/*																				*/
/*==============================================================================*/

#include "cHomingBullet.h"
#include "..\..\..\..\cGame.h"
#include "..\..\..\..\Utility\utility.h"
#include "..\..\Player\cPlayer.h"
#include "..\..\Enemy\cEnemyManager.h"

const float cHomingBullet::HIT_RANGE = 6.0f;	// 当たり判定大きさ
const int	cHomingBullet::PRIORITY = 300;		// 表示優先度
const float cHomingBullet::ROT_LIMIT = 1.5f;	// 旋回上限角度初期値
const int   cHomingBullet::LIFE_TIME = 360;		// 弾の生存時間デフォルト値
const int	cHomingBullet::DEFAULT_ATK = 50;	// デフォルト攻撃力

//==========================================================================================
// コンストラクタ
//==========================================================================================
cHomingBullet::cHomingBullet(IBaseObject * parent)
	: cBulletBase(parent, "HomingBullet", "data\\graphic\\Bullet_01.png"),
	m_fRotLimit(ROT_LIMIT),
	m_bAlwaysSearch( true ),
	m_pTargettingObj( nullptr),
	m_nLifeTime( LIFE_TIME )
{
}

cHomingBullet::cHomingBullet(IBaseObject * parent, const std::string & name, const std::string & filename)
	: cBulletBase(parent, "HomingBullet", filename),
	m_fRotLimit(ROT_LIMIT),
	m_bAlwaysSearch( true ),
	m_pTargettingObj(nullptr),
	m_nLifeTime( LIFE_TIME )
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cHomingBullet::~cHomingBullet(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cHomingBullet::Initialize(void)
{
	m_fHitRange = HIT_RANGE;

	m_nHp = 0;
	m_nAtk = DEFAULT_ATK;

	m_vPosUp.x = 0;
	m_vPosUp.y = 0;

	m_fRotLimit = ROT_LIMIT;
	m_bAlwaysSearch = true;
	m_nLifeTime = LIFE_TIME;
	m_pTargettingObj = nullptr;

	SetPriority(PRIORITY);

	cBulletBase::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cHomingBullet::Update(void)
{
	// 弾が当たった時の共通処理
	HitProc();

	// ターゲットを探す
	// 常時サーチをしない場合はターゲットが生きているかを確認する
	if( m_bAlwaysSearch ) m_pTargettingObj = SearchTargettingObject( );
	else if( m_pTargettingObj != nullptr && !IsSearchTargetAlive() ) m_pTargettingObj = nullptr;

	if (m_pTargettingObj != nullptr)
	{
		// ホーミング後の移動ベクトルを求める
		CalcHomingMove(m_vPosUp, m_pTargettingObj->GetPos());
	} else
	{
		if (m_vPosUp.x == 0 && m_vPosUp.y == 0)
		{
			// 何も追従しない場合は直線に動く
			if (m_eHitCate == HIT_ENEMY) m_vPosUp.y = m_fSpeed;
			if (m_eHitCate == HIT_PLAYER) m_vPosUp.y = -m_fSpeed;
		}
	}

	// 一定時間経ったら消える
	m_nLifeTime--;
	if( m_nLifeTime <= 0 ) m_eObjectState = OBJECT_STATE_DEAD;

	cBulletBase::Update();

	// エリアアウトをしたら弾を消す
	AreaOutAllProc();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* cHomingBullet::Finalize(void)
{
	cBulletBase::Finalize();

	return this;
}

//==========================================================================================
// ホーミングの移動ベクトルを求める
// hVec : ホーミング後の移動ベクトルを返す
// trgPos : ホーミング対象の座標
//==========================================================================================
void cHomingBullet::CalcHomingMove(cVector2 & hVec, const cVector2& trgPos)
{
	cVector2 tPos = trgPos;	// 対象の座標
	cVector2 srVec = m_vPosUp;	// 元の移動ベクトル
	cVector2 trVec;			// 追尾対象への移動ベクトル

											// 追尾対象への移動ベクトルを求める
	CalcTargetVector(tPos, trVec);

	// 旋回角度上限のベクトルを求める
	CalcRotateLimit(hVec, srVec, trVec, tPos);
}
//==========================================================================================
// 追尾対象へ移動するベクトルを求める
// tPos : 追尾対象の座標
// tVec : 移動ベクトル
//==========================================================================================
void cHomingBullet::CalcTargetVector(const cVector2 & tPos, cVector2& tVec)
{
	float dist = m_vPos.CalsTwoPointDist(tPos);
	if (dist)
	{
		// 距離から自分の移動速度倍率を掛ける
		tVec.x = (tPos.x - m_vPos.x) / dist * m_fSpeed;
		tVec.y = (tPos.y - m_vPos.y) / dist * m_fSpeed;
	} else
	{
		// 重なっているときは真下へ移動する
		tVec.x = 0;
		tVec.y = m_fSpeed;
	}
}
//==========================================================================================
// 旋回上限角度を加味した移動ベクトルを求める
// rVec : 旋回上限の加味した移動ベクトルを返す
// srcVec : 現在の移動ベクトル
// trgVec : 追尾対象への移動ベクトル
// trgPos : 追尾対象の座標
//==========================================================================================
void cHomingBullet::CalcRotateLimit(cVector2 & rVec, const cVector2& srcVec, const cVector2& trgVec, const cVector2& trgPos)
{
	// 旋回角度上限の速度ベクトル
	cVector2 vLimit,vComp;
	float limAngle = DEG_TO_RAD(m_fRotLimit);
	vLimit.x = cos(limAngle) * srcVec.x - sin(limAngle) * srcVec.y;
	vLimit.y = sin(limAngle) * srcVec.x + cos(limAngle) * srcVec.y;

	// 追尾対象方向と旋回角度上限のどちらにまがるかを決める
	if (vComp.DotProduct(srcVec,trgVec) >= vComp.DotProduct(srcVec,vLimit))
	{
		// 旋回範囲内なので追尾対象方向へそのまま移動
		rVec = trgVec;
	} else
	{
		//旋回範囲外の場合は左回り旋回角度のベクトルを求める
		cVector2 vRevLimit;
		vRevLimit.x = cos(limAngle) * srcVec.x + sin(limAngle) * srcVec.y;
		vRevLimit.y = -sin(limAngle) * srcVec.x + cos(limAngle) * srcVec.y;

		// 弾から自機への相対ベクトル
		cVector2 sVec;
		sVec.x = trgPos.x - m_vPos.x;
		sVec.y = trgPos.y - m_vPos.y;

		// 右回りか左回りを決める
		if (sVec.DotProduct(vLimit) >= sVec.DotProduct(vRevLimit))
		{
			// 右回り
			rVec = vLimit;
		} else
		{
			// 左回り
			rVec = vRevLimit;
		}
	}
}
//==========================================================================================
// 追尾対象のオブジェクトを探す
//==========================================================================================
cSpriteObject * cHomingBullet::SearchTargettingObject(void)
{
	cSpriteObject* obj = nullptr;
	// 敵弾の場合はプレイヤーをターゲットにする
	if (m_eHitCate == HIT_ENEMY) obj = (cSpriteObject*)m_pParentObject->FindSibling("Player");
	// 自弾の場合は一番近い敵を探す
	if (m_eHitCate == HIT_PLAYER) obj = SearchTargettingEnemy();

	return obj;
}

//==========================================================================================
// 追尾対象の敵を探す
//==========================================================================================
cSpriteObject* cHomingBullet::SearchTargettingEnemy(void)
{
	cSpriteObject* min = nullptr;
	float dist = 3000.0f;

	for (auto it = cEnemyManager::GetInstance().GetChildList()->begin(); it != cEnemyManager::GetInstance().GetChildList()->end(); it++)
	{
		// 一番近い敵を探す
		float temp = m_vPos.CalsTwoPointDist(((cSpriteObject*)(*it))->GetPos());
		if (dist > temp)
		{
			dist = temp;
			min = (cSpriteObject*)(*it);
		}
	}
	return min;
}
//==========================================================================================
// 追尾対象が生きているかどうか
//==========================================================================================
bool cHomingBullet::IsSearchTargetAlive(void)
{
	if (m_eHitCate == HIT_PLAYER)
	{
		for (auto it = cEnemyManager::GetInstance().GetChildList()->begin(); it != cEnemyManager::GetInstance().GetChildList()->end(); it++)
		{
			if (m_pTargettingObj == (cSpriteObject*)*it) return true;
		}
	}
	if (m_eHitCate == HIT_ENEMY)
	{
		if ((cSpriteObject*)m_pParentObject->FindSibling("Player") != nullptr) return true;
	}

	return false;
}
//==========================================================================================
// ランダムターゲット設定
//==========================================================================================
cSpriteObject* cHomingBullet::SetRandomTarget(void)
{
	// 敵弾の場合はプレイヤーをターゲットにする
	if (m_eHitCate == HIT_ENEMY)
	{
		m_pTargettingObj = (cSpriteObject*)m_pParentObject->FindSibling("Player");
	}
	// 自弾の場合はランダムなターゲットを設定する
	if (m_eHitCate == HIT_PLAYER)
	{
		int random = cGame::Random(0,cEnemyManager::GetInstance().GetChildList()->size()-1);
		int i = 0;
		for (auto it = cEnemyManager::GetInstance().GetChildList()->begin(); it != cEnemyManager::GetInstance().GetChildList()->end(); it++,i++)
		{
			if (i == random)
			{
				m_pTargettingObj = (cSpriteObject*)(*it);
			}
		}
	}
	return m_pTargettingObj;
}

//==========================================================================================
// 発射角度のセット
// angle : 度数法の角度,0度が真下
//==========================================================================================
void cHomingBullet::SetShootAngle(float angle)
{
	angle += 90.0f;
	m_vPosUp.x = m_fSpeed * cos(DEG_TO_RAD(angle));
	m_vPosUp.y = m_fSpeed * sin(DEG_TO_RAD(angle));
}